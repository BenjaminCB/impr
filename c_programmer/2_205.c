#include <stdio.h>
#include <stdlib.h>

int n, k, between, divisor, digit, sum, lowercase;
char ch;

int main(void) {
    scanf(" %d %d", &n, &k);

    between = (n < k && n > -k) ? 1 : 0;

    divisor = (sum % digit == 0) ? 1 : 0;

    lowercase = (ch >= 'a' && ch <= 'z') ? 1 : 0;

    return 0;
}