#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[20],
         buffer[1000];
    int i = 0;
    FILE* file = fopen("./13_5.txt", "r");
    printf("%d\n", argc);
    while (argv[1][i] != '\0') {
        str[i] = argv[1][i];
        i++;
    }
    str[i] = '\0';
    printf("%s\n", str);

    for (i = 0; i < 11; i++) {
        fgets(buffer, 1000, file);
        if (strstr(buffer, str) != NULL) {
            printf("%s\n", buffer);
        }
    }

    return 0;
}