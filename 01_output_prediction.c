/*
 * 01. 출력 결과 예측 문제 (필기시험에서 가장 흔한 유형)
 *
 * 풀이 방법
 *   1) 실행하기 전에 각 문제의 "내 답:" 주석에 예상 출력을 적는다.
 *      (시험처럼 종이에 먼저 써보는 것을 추천)
 *   2) 실행해서 결과를 확인한다.
 *        전체 실행:      .\q01.exe
 *        한 문제만 실행: .\q01.exe 5
 *   3) solutions/01_answers.md 에서 해설을 확인한다.
 *
 * 주의: 컴파일 경고가 힌트가 될 수 있으니 이 파일은 -Wall 없이 컴파일하세요.
 * 가정: int 4바이트, x86 리틀 엔디안. 포인터 크기는 32비트 4바이트, 64비트 8바이트.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Q1. 포인터 연산과 증감 연산자
 * 내 답: 10 30 31 40
 */
void q1(void) {
    int arr[] = {10, 20, 30, 40, 50};
    int *p = arr;

    printf("%d ", *p++);
    printf("%d ", *++p);
    printf("%d ", ++*p);
    printf("%d\n", *(p + 1));
}

/* Q2. static 지역 변수
 * 내 답: 11 21 31
 */
int counter(void) {
    static int n = 0;
    int m = 0;
    n++;
    m++;
    return n * 10 + m;
}

void q2(void) {
    int a = counter();
    int b = counter();
    int c = counter();
    printf("%d %d %d\n", a, b, c);
}

/* Q3. 구조체 크기 (메모리 정렬과 패딩)
 * 내 답: 12 8 6
 */
struct A {
    char c;
    int i;
    char d;
};
struct B {
    int i;
    char c;
    char d;
};
struct C {
    char c;
    short s;
    char d;
};

void q3(void) {
    printf("%d %d %d\n",
           (int)sizeof(struct A), (int)sizeof(struct B), (int)sizeof(struct C));
}

/* Q4. 매크로의 함정
 * 내 답: 
 */
#define SQUARE(x) x *x
#define MAX(a, b) ((a) > (b) ? (a) : (b))

void q4(void) {
    int a = 3;
    int i = 5, j = 3;
    int m;

    printf("%d ", SQUARE(a + 1));
    m = MAX(i++, j);
    printf("%d %d\n", m, i);
}

/* Q5. 부호 없는 정수와 정수 승격
 * 내 답:
 */
void q5(void) {
    unsigned int u = 1;
    int s = -1;
    unsigned char c = 255;
    unsigned char x = 0x80;

    if (s < u)
        printf("A ");
    else
        printf("B ");

    c++;
    printf("%d ", c);
    printf("%d\n", x << 1);
}

/* Q6. 배열과 포인터의 sizeof
 * 내 답 (본인 환경이 32비트인지 64비트인지 생각하고 적기):
 */
void print_param_size(int a[]) {
    printf("%d ", (int)sizeof(a));
}

void q6(void) {
    int arr[10];
    char *s = "hello";
    char t[] = "hello";

    printf("%d ", (int)sizeof(arr));
    print_param_size(arr);
    printf("%d %d %d\n", (int)sizeof(s), (int)sizeof(t), (int)strlen(t));
}

/* Q7. 연산자 우선순위
 * 내 답:
 */
void q7(void) {
    int x = 0x0F;
    int y = 1 << 2 + 1;

    if (x & 0x10 == 0)
        printf("Y ");
    else
        printf("N ");

    printf("%d\n", y);
}

/* Q8. 2차원 배열과 포인터
 * 내 답:
 */
void q8(void) {
    int m[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    printf("%d ", *(*(m + 1) + 2));
    printf("%d ", *(m[2] + 3));
    printf("%d\n", (int)(sizeof(m) / sizeof(m[0])));
}

/* Q9. 값 전달, 포인터 전달, 함수 포인터
 * 내 답:
 */
void swap_value(int a, int b) {
    int t = a;
    a = b;
    b = t;
}
void swap_pointer(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

void q9(void) {
    int x = 1, y = 2;
    int (*ops[2])(int, int) = {add, mul};

    swap_value(x, y);
    printf("%d %d / ", x, y);
    swap_pointer(&x, &y);
    printf("%d %d / ", x, y);
    printf("%d\n", ops[1](3, 4) + ops[0](1, 2));
}

/* Q10. switch fall-through
 * 내 답:
 */
void q10(void) {
    int k = 2;

    switch (k) {
    case 1:
        printf("1");
    case 2:
        printf("2");
    case 3:
        printf("3");
        break;
    default:
        printf("D");
    }
    printf("\n");
}

/* Q11. 단락 평가 (short-circuit evaluation)
 * 내 답:
 */
void q11(void) {
    int a = 0, b = 0;

    if (a++ && b++) {
    }
    printf("%d %d / ", a, b);

    if (a++ || b++) {
    }
    printf("%d %d\n", a, b);
}

/* Q12. union과 엔디안
 * 내 답:
 */
void q12(void) {
    union {
        unsigned int i;
        unsigned char c[4];
    } u;

    u.i = 0x12345678;
    printf("%02X %02X\n", u.c[0], u.c[3]);
}

/* Q13. sizeof 안의 식은 실행될까?
 * 내 답:
 */
void q13(void) {
    int n = 5;
    int s = sizeof(n++);
    printf("%d %d\n", n, s);
}

/* Q14. 문자열 배열과 인덱싱
 * 내 답:
 */
void q14(void) {
    char s[] = "abc";
    char *p = s;

    p[1] = 'X';
    printf("%s %c %c\n", s, *(s + 2), 2 [s]);
}

/* Q15. 정수 나눗셈과 나머지 (C99)
 * 내 답:
 */
void q15(void) {
    printf("%d %d %d\n", 7 / 2, -7 / 2, -7 % 2);
}

int main(int argc, char *argv[]) {
    void (*questions[])(void) = {
        q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15};
    int count = (int)(sizeof(questions) / sizeof(questions[0]));
    int i;

    if (argc > 1) {
        int n = atoi(argv[1]);
        if (n < 1 || n > count) {
            printf("Question number must be 1~%d\n", count);
            return 1;
        }
        printf("Q%d: ", n);
        questions[n - 1]();
        return 0;
    }

    for (i = 0; i < count; i++) {
        printf("Q%-2d: ", i + 1);
        questions[i]();
    }
    return 0;
}
