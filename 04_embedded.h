#ifndef EMBEDDED_H
#define EMBEDDED_H

#include <stdint.h>
#include <stddef.h>

/* ============================================================
 * 문제 1. 레지스터 조작 매크로 (이 파일에서 직접 완성하세요)
 * ============================================================
 * BIT(n)            : n번째 비트만 1인 unsigned 값      예) BIT(3) -> 0x08
 * REG_SET(reg, mask): reg에서 mask의 비트들을 1로
 * REG_CLR(reg, mask): reg에서 mask의 비트들을 0으로
 * REG_TEST(reg, mask): mask의 비트 중 하나라도 1이면 1, 아니면 0
 * ARRAY_SIZE(arr)   : 배열의 원소 개수
 * MIN(a, b)         : 둘 중 작은 값
 *
 * 테스트는 BIT(2) * 3, REG_CLR(r, BIT(1) | BIT(2)), 10 - MIN(3, 5) 처럼
 * 다른 연산자와 섞어서 사용합니다. 괄호에 주의하세요!
 */
#define BIT(n)              (0)       /* TODO */
#define REG_SET(reg, mask)  ((void)0) /* TODO */
#define REG_CLR(reg, mask)  ((void)0) /* TODO */
#define REG_TEST(reg, mask) (0)       /* TODO */
#define ARRAY_SIZE(arr)     (0)       /* TODO */
#define MIN(a, b)           (0)       /* TODO */

/* 문제 2. 링 버퍼 (UART 수신 버퍼 등에 사용) */
#define RB_SIZE 8

typedef struct {
    uint8_t data[RB_SIZE];
    uint16_t head;   /* 다음에 쓸 위치 */
    uint16_t tail;   /* 다음에 읽을 위치 */
    uint16_t count;  /* 저장된 개수 */
} RingBuffer;

void rb_init(RingBuffer *rb);
int rb_put(RingBuffer *rb, uint8_t byte);
int rb_get(RingBuffer *rb, uint8_t *out);
uint16_t rb_count(const RingBuffer *rb);

/* 문제 3~4. EDID */
#define EDID_BLOCK_SIZE 128

int edid_header_valid(const uint8_t *edid);
uint8_t edid_calc_checksum(const uint8_t *edid);
int edid_checksum_valid(const uint8_t *edid);
void edid_get_manufacturer(const uint8_t *edid, char out[4]);
uint16_t edid_get_product_code(const uint8_t *edid);

/* 문제 5. CRC-8 */
uint8_t crc8(const uint8_t *data, size_t len);

/* 문제 6. 버튼 디바운스 */
#define DEBOUNCE_COUNT 3

void debounce_reset(void);
uint8_t debounce_update(uint8_t raw);

/* 문제 7~8. 디스플레이 계산 */
uint32_t calc_pixel_clock_khz(uint16_t h_total, uint16_t v_total, uint8_t refresh_hz);
uint16_t brightness_to_pwm(uint8_t percent, uint16_t pwm_max);

#endif /* EMBEDDED_H */
