/*
 * 03. 포인터, 문자열, 메모리 함수 - 모범 답안
 */
#include <stdlib.h>
#include "03_pointer_string.h"

size_t my_strlen(const char *s)
{
    const char *p = s;
    while (*p)
        p++;
    return (size_t)(p - s);
}

/* 원본 dst 주소를 따로 저장해두지 않으면 반환할 수 없다. */
char *my_strcpy(char *dst, const char *src)
{
    char *d = dst;
    while ((*d++ = *src++) != '\0')
        ;
    return dst;
}

/* char가 signed인 환경에서 '\x80'은 음수가 되므로 unsigned char로 비교한다. */
int my_strcmp(const char *a, const char *b)
{
    const unsigned char *pa = (const unsigned char *)a;
    const unsigned char *pb = (const unsigned char *)b;
    while (*pa && *pa == *pb) {
        pa++;
        pb++;
    }
    return (int)*pa - (int)*pb;
}

/* void *는 가리키는 크기를 모르므로 바이트 단위(unsigned char *)로 변환해서 복사 */
void *my_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    while (n--)
        *d++ = *s++;
    return dst;
}

/* dst가 src보다 뒤에 있으면서 겹치면, 앞에서부터 복사할 때 아직 안 읽은
 * 원본을 덮어쓴다. 이 경우 뒤에서부터 복사한다. */
void *my_memmove(void *dst, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;

    if (d == s || n == 0)
        return dst;

    if (d < s) {
        while (n--)
            *d++ = *s++;
    } else {
        d += n;
        s += n;
        while (n--)
            *--d = *--s;
    }
    return dst;
}

void reverse_string(char *s)
{
    char *end = s;
    if (*s == '\0')
        return;
    while (*end)
        end++;
    end--;
    while (s < end) {
        char t = *s;
        *s++ = *end;
        *end-- = t;
    }
}

int my_atoi(const char *s)
{
    int sign = 1;
    int result = 0;

    while (*s == ' ')
        s++;
    if (*s == '+' || *s == '-') {
        if (*s == '-')
            sign = -1;
        s++;
    }
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return sign * result;
}

/* -INT_MIN은 int로 표현할 수 없어서(오버플로) unsigned로 절댓값을 구한다.
 * 뒤 자리부터 채운 뒤 뒤집는다. */
char *my_itoa(int value, char *buf)
{
    char *p = buf;
    unsigned int u;

    if (value < 0) {
        *p++ = '-';
        u = 0U - (unsigned int)value;
    } else {
        u = (unsigned int)value;
    }

    {
        char *start = p;
        do {
            *p++ = (char)('0' + u % 10U);
            u /= 10U;
        } while (u != 0);
        *p = '\0';
        reverse_string(start);
    }
    return buf;
}

void swap_int(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int find_max(const int *arr, int n, int *out_index)
{
    int i;
    int max_index = 0;

    if (n <= 0) {
        if (out_index)
            *out_index = -1;
        return 0;
    }
    for (i = 1; i < n; i++) {
        if (arr[i] > arr[max_index])
            max_index = i;
    }
    if (out_index)
        *out_index = max_index;
    return arr[max_index];
}

/* head 변수 자체(호출자의 포인터)를 바꿔야 하므로 포인터의 주소가 필요하다.
 * Node *head로 받으면 복사본만 바뀌고 호출자의 head는 그대로다. */
int list_push_front(Node **head, int value)
{
    Node *node = (Node *)malloc(sizeof(*node));
    if (node == NULL)
        return -1;
    node->data = value;
    node->next = *head;
    *head = node;
    return 0;
}

/* prev / curr / next 세 포인터로 링크 방향을 하나씩 바꾼다. */
Node *list_reverse(Node *head)
{
    Node *prev = NULL;
    Node *curr = head;
    while (curr) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
