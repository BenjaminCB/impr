#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* end_str(char* str);

int main(void) {
    char str[] = "dairy";

    char* new_str = end_str(str);

    printf("%s\n", new_str);

    return 0;
}

char* end_str(char* str) {
    char* end = (char*) malloc(strlen(str) + 4);
    char* last = (end + strlen(end) - 1);
    strcpy(end, str);

    if (last == strrchr(end, 'y')) {
        *(end + strlen(end) - 1) = 'i';
        strcat(end, "es");
    } else if (last == strrchr(end, 's') || last == strrchr(end, 'h')) {
        strcat(end, "es");
    } else {
        strcat(end, "s");
    }

    return end;
}

