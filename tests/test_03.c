#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "03_pointer_string.h"

static void free_list(Node *head)
{
    while (head) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    printf("=== 03. Pointer / String ===\n");

    case_begin("1. my_strlen");
    CHECK_EQ(my_strlen(""), 0);
    CHECK_EQ(my_strlen("a"), 1);
    CHECK_EQ(my_strlen("hello"), 5);
    CHECK_EQ(my_strlen("hello\0world"), 5);
    case_end();

    case_begin("2. my_strcpy");
    {
        char buf[16] = {0};
        CHECK(my_strcpy(buf, "firmware") == buf);
        CHECK(strcmp(buf, "firmware") == 0);
        memset(buf, 'x', sizeof(buf));
        my_strcpy(buf, "");
        CHECK(buf[0] == '\0');
    }
    case_end();

    case_begin("3. my_strcmp");
    CHECK(my_strcmp("abc", "abc") == 0);
    CHECK(my_strcmp("", "") == 0);
    CHECK(my_strcmp("abc", "abd") < 0);
    CHECK(my_strcmp("b", "a") > 0);
    CHECK(my_strcmp("ab", "abc") < 0);
    CHECK(my_strcmp("abc", "ab") > 0);
    CHECK(my_strcmp("\x80", "a") > 0);
    case_end();

    case_begin("4. my_memcpy");
    {
        char buf[16] = {0};
        int src[3] = {1, 2, 3};
        int dst[3] = {0, 0, 0};
        CHECK(my_memcpy(buf, "hello", 6) == buf);
        CHECK(strcmp(buf, "hello") == 0);
        my_memcpy(dst, src, sizeof(src));
        CHECK(dst[0] == 1 && dst[1] == 2 && dst[2] == 3);
    }
    case_end();

    case_begin("5. my_memmove");
    {
        char s[16] = "abcdefgh";
        char t[16] = "abcdefgh";
        CHECK(my_memmove(s + 2, s, 5) == s + 2);
        CHECK(strcmp(s, "ababcdeh") == 0);
        my_memmove(t, t + 2, 5);
        CHECK(strcmp(t, "cdefgfgh") == 0);
    }
    case_end();

    case_begin("6. reverse_string");
    {
        char a[] = "hello";
        char b[] = "";
        char c[] = "a";
        char d[] = "ab";
        reverse_string(a);
        reverse_string(b);
        reverse_string(c);
        reverse_string(d);
        CHECK(strcmp(a, "olleh") == 0);
        CHECK(strcmp(b, "") == 0);
        CHECK(strcmp(c, "a") == 0);
        CHECK(strcmp(d, "ba") == 0);
    }
    case_end();

    case_begin("7. my_atoi");
    CHECK_EQ(my_atoi("123"), 123);
    CHECK_EQ(my_atoi("-42"), -42);
    CHECK_EQ(my_atoi("   +7"), 7);
    CHECK_EQ(my_atoi("12abc"), 12);
    CHECK_EQ(my_atoi("abc"), 0);
    CHECK_EQ(my_atoi("-0"), 0);
    CHECK_EQ(my_atoi("2147483647"), 2147483647L);
    case_end();

    case_begin("8. my_itoa");
    {
        char buf[16];
        memset(buf, 0, sizeof(buf));
        CHECK(my_itoa(0, buf) == buf);
        CHECK(strcmp(buf, "0") == 0);
        memset(buf, 0, sizeof(buf));
        my_itoa(123, buf);
        CHECK(strcmp(buf, "123") == 0);
        memset(buf, 0, sizeof(buf));
        my_itoa(-456, buf);
        CHECK(strcmp(buf, "-456") == 0);
        memset(buf, 0, sizeof(buf));
        my_itoa(2147483647, buf);
        CHECK(strcmp(buf, "2147483647") == 0);
    }
    case_end();

    case_begin("8b. my_itoa INT_MIN (bonus)");
    {
        char buf[16];
        memset(buf, 0, sizeof(buf));
        my_itoa(-2147483647 - 1, buf);
        CHECK(strcmp(buf, "-2147483648") == 0);
    }
    case_end();

    case_begin("9. swap_int");
    {
        int x = 1, y = 2;
        swap_int(&x, &y);
        CHECK(x == 2 && y == 1);
    }
    case_end();

    case_begin("10. find_max");
    {
        int a[] = {3, 9, 2, 9, 1};
        int b[] = {-5, -2, -8};
        int idx = 99;
        CHECK_EQ(find_max(a, 5, &idx), 9);
        CHECK_EQ(idx, 1);
        idx = 99;
        CHECK_EQ(find_max(b, 3, &idx), -2);
        CHECK_EQ(idx, 1);
        CHECK_EQ(find_max(b, 3, NULL), -2);
        idx = 99;
        CHECK_EQ(find_max(a, 0, &idx), 0);
        CHECK_EQ(idx, -1);
    }
    case_end();

    case_begin("11. list_push_front");
    {
        Node *head = NULL;
        CHECK_EQ(list_push_front(&head, 1), 0);
        CHECK_EQ(list_push_front(&head, 2), 0);
        CHECK_EQ(list_push_front(&head, 3), 0);
        CHECK(head != NULL && head->data == 3);
        CHECK(head != NULL && head->next != NULL && head->next->data == 2);
        CHECK(head != NULL && head->next != NULL && head->next->next != NULL &&
              head->next->next->data == 1 && head->next->next->next == NULL);
        free_list(head);
    }
    case_end();

    case_begin("12. list_reverse");
    {
        Node n3 = {3, NULL};
        Node n2 = {2, &n3};
        Node n1 = {1, &n2};
        Node single = {7, NULL};
        Node *r = list_reverse(&n1);
        CHECK(r == &n3);
        CHECK(n3.next == &n2 && n2.next == &n1 && n1.next == NULL);
        CHECK(list_reverse(NULL) == NULL);
        CHECK(list_reverse(&single) == &single && single.next == NULL);
    }
    case_end();

    return test_summary();
}
