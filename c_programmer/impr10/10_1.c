#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 

void strrev(char* str);

int main(void) {
    char str[] = "string";
    printf("%s\n", str);
    strrev(str);
    printf("%s\n", str);

    return 0;
}

void strrev(char* str) {
    int end = strlen(str) - 1,
        start = 0;


    while (start < end) {
        char temp = str[end];
        str[end] = str[start];
        str[start] = temp;
        start++;
        end--;
    }
}