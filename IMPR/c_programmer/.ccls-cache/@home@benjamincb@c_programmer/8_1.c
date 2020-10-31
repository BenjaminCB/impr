#include <stdlib.h>
#include <stdio.h>

enum forret{a, b, c};
enum hovedret{d, e, f};
enum desert{g, h, i};

int main(void) {
    srand(1);
    int i;
    for (i = 0; i < 25; i++) {
        enum forret one = rand() % 3;
        enum hovedret two = rand() % 3;
        enum desert three = rand() % 3;
        printf("%d, %d, %d\n", one, two, three);
    }
}
