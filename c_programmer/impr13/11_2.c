#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_palindrome(char str[]);
int helper(char str[], int start, int end);

int main(void) {
    printf("%d\n%d\n", is_palindrome("regninger"), is_palindrome("hello"));
    return 0;
}

int is_palindrome(char str[]) {
    int end = 0;
    while (str[end] != '\0') end++;
    return helper(str, 0, end - 1);
}

int helper(char str[], int start, int end) {
    if (start >= end) {
        return 1;
    } else if (str[start] != str[end]) {
        return 0;
    } else {
        return helper(str, start + 1, end - 1);
    }
}