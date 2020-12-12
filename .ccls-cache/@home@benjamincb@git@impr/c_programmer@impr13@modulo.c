#include <stdio.h>
int modulo(int a, int b);
int main(void) {
    for (int i = 1; i <= 10; i++) {
        printf("%d\n", modulo(i , 5));
    }
    return 0;
}

int modulo(int a, int b) {
    if (a - b < 0) {
        return a;
    } else {
        return modulo(a - b, b);
    }
}
