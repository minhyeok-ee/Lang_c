#include <string.h>
#include "test.h"
#include "04_embedded.h"

static void make_edid(uint8_t *edid)
{
    static const uint8_t header[8] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
    int i;

    memset(edid, 0, EDID_BLOCK_SIZE);
    memcpy(edid, header, sizeof(header));
    edid[8] = 0x10;   /* "DEL" */
    edid[9] = 0xAC;
    edid[10] = 0x34;  /* product code 0x1234 */
    edid[11] = 0x12;
    edid[18] = 0x01;  /* EDID 1.4 */
    edid[19] = 0x04;
    for (i = 54; i < 72; i++)
        edid[i] = (uint8_t)(i * 7);
}

static uint8_t reference_checksum(const uint8_t *edid)
{
    unsigned sum = 0;
    int i;
    for (i = 0; i < EDID_BLOCK_SIZE - 1; i++)
        sum += edid[i];
    return (uint8_t)((256U - (sum & 0xFFU)) & 0xFFU);
}

int main(void)
{
    printf("=== 04. Embedded / Monitor firmware ===\n");

    case_begin("1-a. BIT");
    CHECK_EQ(BIT(0), 1);
    CHECK_EQ(BIT(3), 8);
    CHECK_EQ(BIT(2) * 3, 12);
    CHECK_EQ(BIT(31), 0x80000000UL);
    case_end();

    case_begin("1-b. REG_SET / REG_CLR / REG_TEST");
    {
        uint32_t r = 0;
        REG_SET(r, BIT(3));
        CHECK_EQ(r, 0x08);
        REG_SET(r, BIT(0) | BIT(1));
        CHECK_EQ(r, 0x0B);
        r = 0xFF;
        REG_CLR(r, BIT(1) | BIT(2));
        CHECK_EQ(r, 0xF9);
        CHECK_EQ(REG_TEST(r, BIT(0) | BIT(1)), 1);
        CHECK_EQ(REG_TEST(r, BIT(1) | BIT(2)), 0);
        CHECK_EQ(REG_TEST(r, BIT(3)) + 1, 2);
    }
    case_end();

    case_begin("1-c. ARRAY_SIZE / MIN");
    {
        int a[10];
        uint8_t b[128];
        (void)a;
        (void)b;
        CHECK_EQ(ARRAY_SIZE(a), 10);
        CHECK_EQ(ARRAY_SIZE(b), 128);
        CHECK_EQ(MIN(3, 5), 3);
        CHECK_EQ(10 - MIN(3, 5), 7);
        CHECK_EQ(MIN(2 + 5, 1 + 4), 5);
    }
    case_end();

    case_begin("2. ring buffer");
    {
        RingBuffer rb;
        uint8_t v = 0;
        int ok = 1;
        int i;

        rb_init(&rb);
        CHECK_EQ(rb_count(&rb), 0);
        CHECK_EQ(rb_get(&rb, &v), -1);

        for (i = 1; i <= RB_SIZE; i++)
            if (rb_put(&rb, (uint8_t)i) != 0)
                ok = 0;
        CHECK(ok);  /* 8 puts should succeed */
        CHECK_EQ(rb_count(&rb), RB_SIZE);
        CHECK_EQ(rb_put(&rb, 99), -1);  /* full */

        CHECK_EQ(rb_get(&rb, &v), 0);
        CHECK_EQ(v, 1);
        CHECK_EQ(rb_put(&rb, 100), 0);  /* wrap around */

        ok = 1;
        for (i = 2; i <= RB_SIZE; i++)
            if (rb_get(&rb, &v) != 0 || v != i)
                ok = 0;
        CHECK(ok);  /* FIFO order 2..8 */
        CHECK_EQ(rb_get(&rb, &v), 0);
        CHECK_EQ(v, 100);
        CHECK_EQ(rb_get(&rb, &v), -1);
        CHECK_EQ(rb_count(&rb), 0);
    }
    case_end();

    case_begin("3. EDID header / checksum");
    {
        uint8_t edid[EDID_BLOCK_SIZE];
        uint8_t zero[EDID_BLOCK_SIZE];

        make_edid(edid);
        CHECK_EQ(edid_header_valid(edid), 1);
        CHECK_EQ(edid_calc_checksum(edid), reference_checksum(edid));
        edid[127] = reference_checksum(edid);
        CHECK_EQ(edid_checksum_valid(edid), 1);
        edid[100] ^= 0x01;
        CHECK_EQ(edid_checksum_valid(edid), 0);
        edid[0] = 0x01;
        CHECK_EQ(edid_header_valid(edid), 0);

        memset(zero, 0, sizeof(zero));
        CHECK_EQ(edid_calc_checksum(zero), 0);
        CHECK_EQ(edid_checksum_valid(zero), 1);
    }
    case_end();

    case_begin("4. EDID manufacturer / product code");
    {
        uint8_t edid[EDID_BLOCK_SIZE];
        char name[4] = {0};

        make_edid(edid);
        edid_get_manufacturer(edid, name);
        CHECK(strcmp(name, "DEL") == 0);
        CHECK_EQ(edid_get_product_code(edid), 0x1234);

        edid[8] = 0x4C;
        edid[9] = 0x2D;
        memset(name, 0, sizeof(name));
        edid_get_manufacturer(edid, name);
        CHECK(strcmp(name, "SAM") == 0);
    }
    case_end();

    case_begin("5. crc8");
    {
        static const uint8_t check[] = "123456789";
        static const uint8_t one[] = {0x01};
        CHECK_EQ(crc8(check, 9), 0xF4);
        CHECK_EQ(crc8(one, 1), 0x07);
        CHECK_EQ(crc8(check, 0), 0x00);
    }
    case_end();

    case_begin("6. debounce");
    {
        static const uint8_t input[]    = {1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1};
        static const uint8_t expected[] = {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
        int i;

        debounce_reset();
        for (i = 0; i < (int)sizeof(input); i++) {
            uint8_t got = debounce_update(input[i]);
            if (got != expected[i]) {
                g_fail++;
                printf("    - fail: step %d input %d -> expected %d, got %d\n",
                       i, input[i], expected[i], got);
            }
        }
        debounce_reset();
        CHECK_EQ(debounce_update(1), 0);  /* reset must clear counter */
    }
    case_end();

    case_begin("7. calc_pixel_clock_khz");
    CHECK_EQ(calc_pixel_clock_khz(2200, 1125, 60), 148500UL);
    CHECK_EQ(calc_pixel_clock_khz(4400, 2250, 60), 594000UL);
    CHECK_EQ(calc_pixel_clock_khz(800, 525, 60), 25200UL);
    CHECK_EQ(calc_pixel_clock_khz(12000, 5000, 60), 3600000UL);
    case_end();

    case_begin("8. brightness_to_pwm");
    CHECK_EQ(brightness_to_pwm(0, 1000), 0);
    CHECK_EQ(brightness_to_pwm(50, 1000), 500);
    CHECK_EQ(brightness_to_pwm(100, 1000), 1000);
    CHECK_EQ(brightness_to_pwm(150, 1000), 1000);
    CHECK_EQ(brightness_to_pwm(33, 65535), 21626);
    CHECK_EQ(brightness_to_pwm(100, 65535), 65535);
    case_end();

    return test_summary();
}
