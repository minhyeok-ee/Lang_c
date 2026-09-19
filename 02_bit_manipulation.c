/*
 * 02. 비트 연산 (임베디드 C의 기본기)
 *
 * 각 함수의 TODO 부분을 구현하세요. 모든 비트 위치 n은 0~31 입니다.
 * 채점: .\check.ps1 02   (자세한 방법은 README.md 참고)
 */
#include "02_bit_manipulation.h"

/* 문제 1. value의 n번째 비트를 1로 만든 값을 반환
 * 예) set_bit(0x00, 3) -> 0x08
 * 힌트: n = 31일 때 (1 << 31)은 안전할까?
 */
uint32_t set_bit(uint32_t value, int n)
{
    /* TODO */
    return 0;
}

/* 문제 2. value의 n번째 비트를 0으로 만든 값을 반환
 * 예) clear_bit(0xFF, 0) -> 0xFE
 */
uint32_t clear_bit(uint32_t value, int n)
{
    /* TODO */
    return 0;
}

/* 문제 3. value의 n번째 비트를 반전한 값을 반환
 * 예) toggle_bit(0x0F, 0) -> 0x0E, toggle_bit(0x0F, 4) -> 0x1F
 */
uint32_t toggle_bit(uint32_t value, int n)
{
    /* TODO */
    return 0;
}

/* 문제 4. value의 n번째 비트가 1이면 1, 0이면 0을 반환 (정확히 0 또는 1)
 */
int is_bit_set(uint32_t value, int n)
{
    /* TODO */
    return 0;
}

/* 문제 5. 1인 비트의 개수를 반환
 * 예) count_ones(0xA5) -> 4
 * 도전: 루프를 32번 돌지 않고 "1인 비트 수만큼만" 도는 방법은?
 */
int count_ones(uint32_t value)
{
    /* TODO */
    return 0;
}

/* 문제 6. value가 2의 거듭제곱이면 1, 아니면 0을 반환 (0은 거듭제곱이 아님)
 * 조건: 반복문 없이 한 줄로 작성해보기
 */
int is_power_of_two(uint32_t value)
{
    /* TODO */
    return 0;
}

/* 문제 7. 32비트 값의 바이트 순서를 뒤집기 (엔디안 변환)
 * 예) 0x12345678 -> 0x78563412
 */
uint32_t swap_endian32(uint32_t value)
{
    /* TODO */
    return 0;
}

/* 문제 8. 8비트 값의 비트 순서를 뒤집기
 * 예) 0x01 (00000001) -> 0x80 (10000000)
 *     0xB0 (10110000) -> 0x0D (00001101)
 */
uint8_t reverse_bits8(uint8_t value)
{
    /* TODO */
    return 0;
}

/* 문제 9. 레지스터 필드 쓰기
 * reg의 [pos, pos + width) 구간 비트를 val로 바꾼 값을 반환 (나머지 비트는 유지)
 * val이 width보다 크면 넘치는 비트는 버린다. width는 1~31, pos + width <= 32.
 * 예) set_field(0xFFFFFFFF, 4, 4, 0x5) -> 0xFFFFFF5F
 */
uint32_t set_field(uint32_t reg, int pos, int width, uint32_t val)
{
    /* TODO */
    return 0;
}

/* 문제 10. 레지스터 필드 읽기
 * reg의 [pos, pos + width) 구간 값을 반환. width는 1~31.
 * 예) get_field(0x12345678, 8, 8) -> 0x56
 */
uint32_t get_field(uint32_t reg, int pos, int width)
{
    /* TODO */
    return 0;
}

/* 문제 11. 1인 비트 중 가장 낮은 위치를 반환. value가 0이면 -1
 * 예) 0x18 (00011000) -> 3
 */
int lowest_set_bit_pos(uint32_t value)
{
    /* TODO */
    return 0;
}

/* 문제 12. x를 align의 배수로 올림 (align은 2의 거듭제곱)
 * 예) align_up(5, 8) -> 8, align_up(16, 8) -> 16
 * 조건: 나눗셈이나 나머지 연산 없이 비트 연산만 사용
 */
uint32_t align_up(uint32_t x, uint32_t align)
{
    /* TODO */
    return 0;
}
