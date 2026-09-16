#include "test.h"
#include "02_bit_manipulation.h"

int main(void)
{
    printf("=== 02. Bit manipulation ===\n");

    case_begin("1. set_bit");
    CHECK_EQ(set_bit(0x00, 0), 0x01);
    CHECK_EQ(set_bit(0x00, 3), 0x08);
    CHECK_EQ(set_bit(0xF0, 4), 0xF0);
    CHECK_EQ(set_bit(0x00, 31), 0x80000000UL);
    case_end();

    case_begin("2. clear_bit");
    CHECK_EQ(clear_bit(0xFF, 0), 0xFE);
    CHECK_EQ(clear_bit(0xF0, 0), 0xF0);
    CHECK_EQ(clear_bit(0xFFFFFFFFUL, 31), 0x7FFFFFFFUL);
    case_end();

    case_begin("3. toggle_bit");
    CHECK_EQ(toggle_bit(0x0F, 0), 0x0E);
    CHECK_EQ(toggle_bit(0x0F, 4), 0x1F);
    CHECK_EQ(toggle_bit(0x80000000UL, 31), 0x00);
    case_end();

    case_begin("4. is_bit_set");
    CHECK_EQ(is_bit_set(0x08, 3), 1);
    CHECK_EQ(is_bit_set(0x08, 2), 0);
    CHECK_EQ(is_bit_set(0x80000000UL, 31), 1);
    CHECK_EQ(is_bit_set(0xFFFFFFFFUL, 16), 1);
    case_end();

    case_begin("5. count_ones");
    CHECK_EQ(count_ones(0x00), 0);
    CHECK_EQ(count_ones(0xA5), 4);
    CHECK_EQ(count_ones(0x80000001UL), 2);
    CHECK_EQ(count_ones(0xFFFFFFFFUL), 32);
    case_end();

    case_begin("6. is_power_of_two");
    CHECK_EQ(is_power_of_two(0), 0);
    CHECK_EQ(is_power_of_two(1), 1);
    CHECK_EQ(is_power_of_two(2), 1);
    CHECK_EQ(is_power_of_two(3), 0);
    CHECK_EQ(is_power_of_two(1024), 1);
    CHECK_EQ(is_power_of_two(0x80000000UL), 1);
    CHECK_EQ(is_power_of_two(0x80000001UL), 0);
    case_end();

    case_begin("7. swap_endian32");
    CHECK_EQ(swap_endian32(0x12345678UL), 0x78563412UL);
    CHECK_EQ(swap_endian32(0xFF000000UL), 0x000000FFUL);
    CHECK_EQ(swap_endian32(0x000000ABUL), 0xAB000000UL);
    case_end();

    case_begin("8. reverse_bits8");
    CHECK_EQ(reverse_bits8(0x01), 0x80);
    CHECK_EQ(reverse_bits8(0xB0), 0x0D);
    CHECK_EQ(reverse_bits8(0xFF), 0xFF);
    CHECK_EQ(reverse_bits8(0x00), 0x00);
    case_end();

    case_begin("9. set_field");
    CHECK_EQ(set_field(0xFFFFFFFFUL, 4, 4, 0x5), 0xFFFFFF5FUL);
    CHECK_EQ(set_field(0x00000000UL, 8, 8, 0xAB), 0x0000AB00UL);
    CHECK_EQ(set_field(0x00000000UL, 0, 4, 0x1F), 0x0000000FUL);
    CHECK_EQ(set_field(0x0000FF00UL, 12, 1, 0), 0x0000EF00UL);
    case_end();

    case_begin("10. get_field");
    CHECK_EQ(get_field(0x12345678UL, 8, 8), 0x56);
    CHECK_EQ(get_field(0x0000ABCDUL, 12, 4), 0xA);
    CHECK_EQ(get_field(0x000000F0UL, 4, 1), 1);
    CHECK_EQ(get_field(0xF0000000UL, 28, 4), 0xF);
    case_end();

    case_begin("11. lowest_set_bit_pos");
    CHECK_EQ(lowest_set_bit_pos(0), -1);
    CHECK_EQ(lowest_set_bit_pos(1), 0);
    CHECK_EQ(lowest_set_bit_pos(0x18), 3);
    CHECK_EQ(lowest_set_bit_pos(0x80000000UL), 31);
    case_end();

    case_begin("12. align_up");
    CHECK_EQ(align_up(0, 4), 0);
    CHECK_EQ(align_up(1, 4), 4);
    CHECK_EQ(align_up(4, 4), 4);
    CHECK_EQ(align_up(5, 8), 8);
    CHECK_EQ(align_up(0x1001, 0x1000), 0x2000);
    case_end();

    return test_summary();
}
