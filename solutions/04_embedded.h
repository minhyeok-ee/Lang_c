#ifndef EMBEDDED_H
#define EMBEDDED_H

#include <stdint.h>
#include <stddef.h>

/* 문제 1. 레지스터 조작 매크로 - 모범 답안
 * 원칙 1) 인자는 사용할 때마다 괄호로 감싼다: (n), (mask)
 * 원칙 2) 식 전체를 괄호로 감싼다
 * 원칙 3) 1 대신 1UL: BIT(31)에서 signed int 오버플로(UB) 방지
 * 주의: MIN(i++, j)처럼 부작용이 있는 인자는 두 번 평가될 수 있다. */
#define BIT(n)              (1UL << (n))
#define REG_SET(reg, mask)  ((reg) |= (mask))
#define REG_CLR(reg, mask)  ((reg) &= ~(mask))
#define REG_TEST(reg, mask) (((reg) & (mask)) != 0)
#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))
#define MIN(a, b)           ((a) < (b) ? (a) : (b))

#define RB_SIZE 8

typedef struct {
    uint8_t data[RB_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} RingBuffer;

void rb_init(RingBuffer *rb);
int rb_put(RingBuffer *rb, uint8_t byte);
int rb_get(RingBuffer *rb, uint8_t *out);
uint16_t rb_count(const RingBuffer *rb);

#define EDID_BLOCK_SIZE 128

int edid_header_valid(const uint8_t *edid);
uint8_t edid_calc_checksum(const uint8_t *edid);
int edid_checksum_valid(const uint8_t *edid);
void edid_get_manufacturer(const uint8_t *edid, char out[4]);
uint16_t edid_get_product_code(const uint8_t *edid);

uint8_t crc8(const uint8_t *data, size_t len);

#define DEBOUNCE_COUNT 3

void debounce_reset(void);
uint8_t debounce_update(uint8_t raw);

uint32_t calc_pixel_clock_khz(uint16_t h_total, uint16_t v_total, uint8_t refresh_hz);
uint16_t brightness_to_pwm(uint8_t percent, uint16_t pwm_max);

#endif /* EMBEDDED_H */
