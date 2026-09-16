/*
 * 04. 임베디드 / 모니터 펌웨어 실전 문제
 *
 * 문제 1(매크로)은 04_embedded.h 파일에서 완성하세요.
 * 채점: .\check.ps1 04
 */
#include "04_embedded.h"

/* ============================================================
 * 문제 2. 링 버퍼
 * ============================================================
 * - rb_init : 버퍼를 빈 상태로 초기화
 * - rb_put  : 1바이트 저장. 성공 0, 가득 차 있으면 -1 (기존 데이터를 덮어쓰지 않음)
 * - rb_get  : 가장 오래된 1바이트를 꺼내 *out에 저장. 성공 0, 비어 있으면 -1
 * - rb_count: 저장된 바이트 수
 * 인덱스가 RB_SIZE에 도달하면 0으로 돌아가야 한다.
 *
 * 면접 대비 생각해보기:
 *   UART 수신 인터럽트(ISR)에서 rb_put, 메인 루프에서 rb_get을 호출한다면
 *   어떤 문제가 생길 수 있고 어떻게 막을까?
 */
void rb_init(RingBuffer *rb)
{
    /* TODO */
}

int rb_put(RingBuffer *rb, uint8_t byte)
{
    /* TODO */
    return -1;
}

int rb_get(RingBuffer *rb, uint8_t *out)
{
    /* TODO */
    return -1;
}

uint16_t rb_count(const RingBuffer *rb)
{
    /* TODO */
    return 0;
}

/* ============================================================
 * 문제 3. EDID 헤더와 체크섬
 * ============================================================
 * EDID 기본 블록은 128바이트다.
 * - 0~7번 바이트 헤더: 00 FF FF FF FF FF FF 00
 * - 127번 바이트는 체크섬: 128바이트 전체를 더했을 때 하위 8비트가 0이 되도록 하는 값
 *
 * edid_header_valid  : 헤더가 맞으면 1, 아니면 0
 * edid_calc_checksum : 0~126번 바이트를 보고 127번에 들어가야 할 값을 계산
 * edid_checksum_valid: 128바이트 합의 하위 8비트가 0이면 1, 아니면 0
 */
int edid_header_valid(const uint8_t *edid)
{
    /* TODO */
    return 0;
}

uint8_t edid_calc_checksum(const uint8_t *edid)
{
    /* TODO */
    return 0;
}

int edid_checksum_valid(const uint8_t *edid)
{
    /* TODO */
    return 0;
}

/* ============================================================
 * 문제 4. EDID 제조사 ID와 제품 코드
 * ============================================================
 * 제조사 ID: 8~9번 바이트를 "빅 엔디안" 16비트로 읽는다.
 *   bit 15      : 항상 0
 *   bit 14~10   : 첫 번째 글자
 *   bit 9~5     : 두 번째 글자
 *   bit 4~0     : 세 번째 글자
 *   각 5비트 값은 1='A', 2='B', ... 26='Z'
 *   예) 바이트 0x10 0xAC -> "DEL",  0x4C 0x2D -> "SAM"
 *   out에는 3글자 + '\0'을 저장한다.
 *
 * 제품 코드: 10~11번 바이트를 "리틀 엔디안" 16비트로 읽는다.
 *   예) 바이트 0x34 0x12 -> 0x1234
 */
void edid_get_manufacturer(const uint8_t *edid, char out[4])
{
    /* TODO */
}

uint16_t edid_get_product_code(const uint8_t *edid)
{
    /* TODO */
    return 0;
}

/* ============================================================
 * 문제 5. CRC-8 (다항식 0x07, 초기값 0x00, 비트 반전 없음, 최종 XOR 없음)
 * ============================================================
 * 비트 단위 알고리즘:
 *   crc = 0
 *   각 바이트마다: crc ^= byte
 *     8번 반복: 최상위 비트가 1이면 crc = (crc << 1) ^ 0x07, 아니면 crc <<= 1
 * 검증값: "123456789" (9바이트) -> 0xF4
 */
uint8_t crc8(const uint8_t *data, size_t len)
{
    /* TODO */
    return 0;
}

/* ============================================================
 * 문제 6. 버튼 디바운스
 * ============================================================
 * 10ms마다 버튼 입력 raw(0 또는 1)를 넣어 debounce_update를 호출한다.
 * - 안정 상태(state)의 초기값은 0
 * - raw가 state와 다른 값으로 DEBOUNCE_COUNT(3)번 "연속" 들어오면 state를 raw로 바꾼다
 * - 중간에 raw가 state와 같은 값이 들어오면 연속 횟수를 0으로 되돌린다
 * - 반환값은 호출 후의 state
 * debounce_reset은 state와 카운터를 초기 상태로 되돌린다.
 *
 * 예) 입력 1,1,1 -> 반환 0,0,1
 *     이어서 0,1,0,0,0 -> 반환 1,1,1,1,0
 *
 * 힌트: 함수 호출 사이에 값을 유지하려면?
 */
void debounce_reset(void)
{
    /* TODO */
}

uint8_t debounce_update(uint8_t raw)
{
    /* TODO */
    return 0;
}

/* ============================================================
 * 문제 7. 픽셀 클럭 계산
 * ============================================================
 * pixel clock(Hz) = H total * V total * 주사율
 * 결과를 kHz 단위(소수점 버림)로 반환한다.
 * 예) 1920x1080@60 (H total 2200, V total 1125) -> 148500 kHz
 *
 * 함정: 매우 큰 타이밍(12000 x 5000 @ 60Hz = 3,600,000,000Hz)은
 *       중간 계산이 int 범위(약 21억)를 넘는다.
 */
uint32_t calc_pixel_clock_khz(uint16_t h_total, uint16_t v_total, uint8_t refresh_hz)
{
    /* TODO */
    return 0;
}

/* ============================================================
 * 문제 8. 밝기(%)를 백라이트 PWM 값으로 변환
 * ============================================================
 * - pwm = percent * pwm_max / 100 (소수점 버림)
 * - percent가 100을 넘으면 100으로 제한
 * 예) percent 50, pwm_max 1000 -> 500
 *
 * 생각해보기: int가 16비트인 8비트 MCU라면 65535 * 100 계산은 안전할까?
 */
uint16_t brightness_to_pwm(uint8_t percent, uint16_t pwm_max)
{
    /* TODO */
    return 0;
}
