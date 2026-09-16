/*
 * test.h - 연습 문제 채점용 간단한 테스트 도구 (수정할 필요 없음)
 */
#ifndef TEST_H
#define TEST_H

#include <stdio.h>

static int g_fail = 0;
static int g_case_fail_start = 0;
static int g_case_total = 0;
static int g_case_pass = 0;
static const char *g_case_name = "";

#define CHECK(cond)                                                   \
    do {                                                              \
        if (!(cond)) {                                                \
            g_fail++;                                                 \
            printf("    - fail (line %d): %s\n", __LINE__, #cond);    \
        }                                                             \
    } while (0)

#define CHECK_EQ(actual, expected)                                               \
    do {                                                                         \
        long a_ = (long)(actual);                                                \
        long e_ = (long)(expected);                                              \
        if (a_ != e_) {                                                          \
            g_fail++;                                                            \
            printf("    - fail (line %d): %s\n", __LINE__, #actual);             \
            printf("      expected %ld (0x%lX), got %ld (0x%lX)\n",              \
                   e_, (unsigned long)e_, a_, (unsigned long)a_);                \
        }                                                                        \
    } while (0)

static void case_begin(const char *name)
{
    g_case_name = name;
    g_case_fail_start = g_fail;
    printf("\n[%s]\n", name);
}

static void case_end(void)
{
    g_case_total++;
    if (g_fail == g_case_fail_start) {
        g_case_pass++;
        printf("  -> PASS\n");
    } else {
        printf("  -> FAIL (%s)\n", g_case_name);
    }
}

static int test_summary(void)
{
    printf("\n==============================\n");
    printf(" Result: %d / %d passed\n", g_case_pass, g_case_total);
    printf("==============================\n");
    return g_case_pass == g_case_total ? 0 : 1;
}

#endif /* TEST_H */
