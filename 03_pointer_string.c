/*
 * 03. 포인터, 문자열, 메모리 함수 직접 구현
 *
 * 규칙: <string.h>, <stdlib.h>의 문자열/메모리 함수(strlen, memcpy, atoi 등)는
 *       사용하지 말고 직접 구현하세요. (list_push_front의 malloc은 사용 가능)
 * 채점: .\check.ps1 03
 */
#include <stdlib.h>
#include "03_pointer_string.h"

/* 문제 1. 문자열 길이 반환 ('\0' 제외) */
size_t my_strlen(const char *s)
{
    /* TODO */
    return 0;
}

/* 문제 2. src를 dst에 '\0'까지 복사하고 dst를 반환 */
char *my_strcpy(char *dst, const char *src)
{
    /* TODO */
    return NULL;
}

/* 문제 3. 두 문자열 비교
 * a < b이면 음수, 같으면 0, a > b이면 양수
 * 표준 strcmp처럼 문자를 unsigned char로 비교할 것 (예: "\x80" > "a")
 */
int my_strcmp(const char *a, const char *b)
{
    /* TODO */
    return 0;
}

/* 문제 4. src에서 dst로 n바이트 복사하고 dst를 반환 (영역이 겹치지 않는다고 가정)
 * 힌트: void *는 바로 역참조할 수 없다.
 */
void *my_memcpy(void *dst, const void *src, size_t n)
{
    /* TODO */
    return NULL;
}

/* 문제 5. memmove: src와 dst 영역이 겹쳐도 올바르게 복사하고 dst를 반환
 * 예) s = "abcdefgh"; my_memmove(s + 2, s, 5); -> "ababcdeh"
 * 생각해보기: memcpy와 memmove의 차이는?
 */
void *my_memmove(void *dst, const void *src, size_t n)
{
    /* TODO */
    return NULL;
}

/* 문제 6. 문자열을 제자리에서(in-place) 뒤집기
 * 예) "hello" -> "olleh"
 */
void reverse_string(char *s)
{
    /* TODO */
}

/* 문제 7. 문자열을 정수로 변환
 * - 앞쪽 공백(' ')은 건너뛴다
 * - '+' 또는 '-' 부호 하나를 처리한다
 * - 숫자가 아닌 문자가 나오면 거기서 멈춘다 (예: "12abc" -> 12, "abc" -> 0)
 * - 오버플로는 고려하지 않아도 된다
 */
int my_atoi(const char *s)
{
    /* TODO */
    return 0;
}

/* 문제 8. 정수를 10진수 문자열로 변환해 buf에 저장하고 buf를 반환
 * buf는 충분히 크다고 가정 (12바이트 이상)
 * 예) 0 -> "0", -456 -> "-456"
 * 보너스: INT_MIN(-2147483648)도 올바르게 처리하기
 */
char *my_itoa(int value, char *buf)
{
    /* TODO */
    return buf;
}

/* 문제 9. 두 정수의 값을 교환 */
void swap_int(int *a, int *b)
{
    /* TODO */
}

/* 문제 10. 배열에서 최댓값을 찾아 반환하고, 그 인덱스를 *out_index에 저장
 * - 최댓값이 여러 개면 가장 앞의 인덱스
 * - n <= 0이면 0을 반환하고 인덱스는 -1
 * - out_index가 NULL이면 인덱스는 저장하지 않는다
 */
int find_max(const int *arr, int n, int *out_index)
{
    /* TODO */
    return 0;
}

/* 문제 11. 연결 리스트 맨 앞에 노드 추가 (malloc 사용)
 * 성공 시 0, 메모리 할당 실패 시 -1 반환
 * 생각해보기: 왜 Node *head가 아니라 Node **head를 받을까?
 */
int list_push_front(Node **head, int value)
{
    /* TODO */
    return -1;
}

/* 문제 12. 연결 리스트를 뒤집고 새 head를 반환 (새 노드 할당 없이)
 * 예) 1 -> 2 -> 3 -> NULL  ==>  3 -> 2 -> 1 -> NULL
 */
Node *list_reverse(Node *head)
{
    /* TODO */
    return head;
}
