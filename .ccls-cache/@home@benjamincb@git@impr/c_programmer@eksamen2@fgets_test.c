#include <stdlib.h>
#include <stdio.h>

int response(void);

int main(void) {
    char answer;
    do {
        answer = response();
        printf("typed: %c\n", answer);
    } while (answer == 'y'); 

    return 0;
}

int response(void) {
    int c,
        answer;

    c = getchar();
    answer = c;

    while (c != '\n' && c != EOF) {
        c = getchar();
    }

    return answer;
}
