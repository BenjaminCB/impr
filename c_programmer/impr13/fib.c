#include <stdio.h>

int fib(int n, int a, int b);

int main(void) {
    for (int i = 0; i <= 20; i++) {
        printf("%d\n", fib(i, 0, 1));
    }
    return 0;
}

int fib(int n, int a, int b) {
    if (n == 0) {
        return a;
    } else {
        return fib(n - 1, b, a + b);
    }
}
