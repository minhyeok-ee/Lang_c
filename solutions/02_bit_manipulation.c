/*
 * 02. 비트 연산 - 모범 답안
 */
#include "02_bit_manipulation.h"

/* 1U를 써야 하는 이유: 1은 signed int라서 1 << 31은 부호 비트를 건드리는
 * 정의되지 않은 동작(UB)이다. 고정 폭 타입이면 UINT32_C(1)이 가장 안전하다. */
uint32_t set_bit(uint32_t value, int n)
{
    return value | (UINT32_C(1) << n);
}

uint32_t clear_bit(uint32_t value, int n)
{
    return value & ~(UINT32_C(1) << n);
}

uint32_t toggle_bit(uint32_t value, int n)
{
    return value ^ (UINT32_C(1) << n);
}

/* value & (1 << n)은 0 또는 (1 << n)이라 "정확히 1"이 아니다.
 * 오른쪽으로 먼저 시프트한 뒤 & 1 하면 0/1이 된다. */
int is_bit_set(uint32_t value, int n)
{
    return (int)((value >> n) & 1U);
}

/* Brian Kernighan 방법: v & (v - 1)은 가장 낮은 1 비트 하나를 지운다.
 * 1인 비트 수만큼만 반복한다. */
int count_ones(uint32_t value)
{
    int count = 0;
    while (value) {
        value &= value - 1;
        count++;
    }
    return count;
}

/* 2의 거듭제곱은 1인 비트가 딱 하나다. 0은 따로 제외해야 한다. */
int is_power_of_two(uint32_t value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

uint32_t swap_endian32(uint32_t value)
{
    return ((value >> 24) & 0x000000FFUL) |
           ((value >> 8)  & 0x0000FF00UL) |
           ((value << 8)  & 0x00FF0000UL) |
           ((value << 24) & 0xFF000000UL);
}

uint8_t reverse_bits8(uint8_t value)
{
    uint8_t result = 0;
    int i;
    for (i = 0; i < 8; i++) {
        result = (uint8_t)((result << 1) | (value & 1U));
        value >>= 1;
    }
    return result;
}

/* 레지스터 수정의 기본 패턴 = read -> clear -> set (read-modify-write) */
uint32_t set_field(uint32_t reg, int pos, int width, uint32_t val)
{
    uint32_t mask = ((UINT32_C(1) << width) - 1U) << pos;
    return (reg & ~mask) | ((val << pos) & mask);
}

uint32_t get_field(uint32_t reg, int pos, int width)
{
    return (reg >> pos) & ((UINT32_C(1) << width) - 1U);
}

int lowest_set_bit_pos(uint32_t value)
{
    int pos = 0;
    if (value == 0)
        return -1;
    while ((value & 1U) == 0) {
        value >>= 1;
        pos++;
    }
    return pos;
}

/* align이 2의 거듭제곱이면 align - 1은 하위 비트가 모두 1인 마스크다.
 * (x + align - 1)로 올린 뒤 하위 비트를 지우면 올림이 된다. */
uint32_t align_up(uint32_t x, uint32_t align)
{
    return (x + align - 1U) & ~(align - 1U);
}
