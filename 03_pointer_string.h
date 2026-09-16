#ifndef POINTER_STRING_H
#define POINTER_STRING_H

#include <stddef.h>

size_t my_strlen(const char *s);
char *my_strcpy(char *dst, const char *src);
int my_strcmp(const char *a, const char *b);
void *my_memcpy(void *dst, const void *src, size_t n);
void *my_memmove(void *dst, const void *src, size_t n);
void reverse_string(char *s);
int my_atoi(const char *s);
char *my_itoa(int value, char *buf);
void swap_int(int *a, int *b);
int find_max(const int *arr, int n, int *out_index);

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int list_push_front(Node **head, int value);
Node *list_reverse(Node *head);

#endif /* POINTER_STRING_H */
