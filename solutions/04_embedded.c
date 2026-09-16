/*
 * 04. 임베디드 / 모니터 펌웨어 - 모범 답안
 */
#include "04_embedded.h"

/* ----- 문제 2. 링 버퍼 -----
 * ISR에서 put, 메인 루프에서 get을 한다면:
 *  - count처럼 양쪽에서 함께 수정하는 변수는 경쟁 조건(race condition)이 생긴다.
 *    메인 쪽 접근 구간에서 인터럽트를 잠깐 끄거나(critical section),
 *    count 없이 head는 ISR만, tail은 메인만 수정하는 구조로 만든다.
 *  - ISR과 공유하는 변수는 volatile로 선언해 컴파일러 최적화로 값이 캐시되지 않게 한다.
 *  - 버퍼 크기를 2의 거듭제곱으로 하면 % 대신 & (SIZE - 1)로 빠르게 wrap할 수 있다. */
void rb_init(RingBuffer *rb)
{
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

int rb_put(RingBuffer *rb, uint8_t byte)
{
    if (rb->count >= RB_SIZE)
        return -1;
    rb->data[rb->head] = byte;
    rb->head = (uint16_t)((rb->head + 1) % RB_SIZE);
    rb->count++;
    return 0;
}

int rb_get(RingBuffer *rb, uint8_t *out)
{
    if (rb->count == 0)
        return -1;
    *out = rb->data[rb->tail];
    rb->tail = (uint16_t)((rb->tail + 1) % RB_SIZE);
    rb->count--;
    return 0;
}

uint16_t rb_count(const RingBuffer *rb)
{
    return rb->count;
}

/* ----- 문제 3. EDID 헤더 / 체크섬 ----- */
int edid_header_valid(const uint8_t *edid)
{
    static const uint8_t header[8] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00};
    int i;
    for (i = 0; i < 8; i++) {
        if (edid[i] != header[i])
            return 0;
    }
    return 1;
}

/* uint8_t에 더하면 자동으로 mod 256이 된다(unsigned 오버플로는 정의된 동작).
 * 체크섬 = 합계의 2의 보수 = (256 - sum) mod 256 = (uint8_t)(0 - sum) */
uint8_t edid_calc_checksum(const uint8_t *edid)
{
    uint8_t sum = 0;
    int i;
    for (i = 0; i < EDID_BLOCK_SIZE - 1; i++)
        sum = (uint8_t)(sum + edid[i]);
    return (uint8_t)(0U - sum);
}

int edid_checksum_valid(const uint8_t *edid)
{
    uint8_t sum = 0;
    int i;
    for (i = 0; i < EDID_BLOCK_SIZE; i++)
        sum = (uint8_t)(sum + edid[i]);
    return sum == 0;
}

/* ----- 문제 4. 제조사 ID(빅 엔디안) / 제품 코드(리틀 엔디안) ----- */
void edid_get_manufacturer(const uint8_t *edid, char out[4])
{
    uint16_t id = (uint16_t)((edid[8] << 8) | edid[9]);
    out[0] = (char)('A' - 1 + ((id >> 10) & 0x1F));
    out[1] = (char)('A' - 1 + ((id >> 5) & 0x1F));
    out[2] = (char)('A' - 1 + (id & 0x1F));
    out[3] = '\0';
}

uint16_t edid_get_product_code(const uint8_t *edid)
{
    return (uint16_t)(edid[10] | (edid[11] << 8));
}

/* ----- 문제 5. CRC-8 -----
 * 실제 펌웨어에서는 속도를 위해 256개짜리 룩업 테이블을 미리 만들어 쓰기도 한다. */
uint8_t crc8(const uint8_t *data, size_t len)
{
    uint8_t crc = 0x00;
    size_t i;
    int bit;

    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (bit = 0; bit < 8; bit++) {
            if (crc & 0x80)
                crc = (uint8_t)((crc << 1) ^ 0x07);
            else
                crc = (uint8_t)(crc << 1);
        }
    }
    return crc;
}

/* ----- 문제 6. 디바운스 -----
 * 파일 범위 static 변수: 호출 사이에 값이 유지되고, 다른 파일에서는 보이지 않는다. */
static uint8_t s_state = 0;
static uint8_t s_count = 0;

void debounce_reset(void)
{
    s_state = 0;
    s_count = 0;
}

uint8_t debounce_update(uint8_t raw)
{
    if (raw != s_state) {
        s_count++;
        if (s_count >= DEBOUNCE_COUNT) {
            s_state = raw;
            s_count = 0;
        }
    } else {
        s_count = 0;
    }
    return s_state;
}

/* ----- 문제 7. 픽셀 클럭 -----
 * uint16_t 끼리 곱하면 int로 승격되어 계산된다. 12000 * 5000 * 60은 int 범위를
 * 넘으므로(UB) 첫 피연산자를 64비트로 캐스팅해 전체 식을 64비트로 계산한다. */
uint32_t calc_pixel_clock_khz(uint16_t h_total, uint16_t v_total, uint8_t refresh_hz)
{
    uint64_t hz = (uint64_t)h_total * v_total * refresh_hz;
    return (uint32_t)(hz / 1000U);
}

/* ----- 문제 8. 밝기 -> PWM -----
 * 16비트 int 환경에서는 65535 * 100이 int 범위를 넘으므로 32비트로 캐스팅한다.
 * 곱셈을 먼저 하고 나눗셈을 나중에 해야 정밀도를 잃지 않는다. */
uint16_t brightness_to_pwm(uint8_t percent, uint16_t pwm_max)
{
    if (percent > 100)
        percent = 100;
    return (uint16_t)((uint32_t)percent * pwm_max / 100U);
}
