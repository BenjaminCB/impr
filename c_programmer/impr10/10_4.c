#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void suffix_count(char str1[], char str2[], char suffix[]);

int main(void) {
    char str1[] = "wormhole",
         str2[] = "pi-hole",
         suffix[16];
    suffix_count(str1, str2, suffix);
    printf("%s\n", suffix);

    return 0;
}

void suffix_count(char str1[], char str2[], char suffix[]) {
    int str1_len = strlen(str1),
        str2_len = strlen(str2),
        j = str2_len - str1_len >= 0 ? str2_len - str1_len : str1_len - str2_len,
        i = 0,
        counter = 0;

    if (str1_len >= str2_len) {
        while (str2[i] != '\0') {
            if (str1[j] == str2[i]) {
                suffix[counter] = str1[j];
                counter++;
            } else {
                counter = 0;
            }
            i++;
            j++;
        }
    } else {
        while (str1[i] != '\0') {
            if (str1[j] == str2[i]) {
                suffix[counter] = str1[j];
                counter++;
            } else {
                counter = 0;
            }
            i++;
            j++;
        }
    }

    suffix[counter] = '\0';
}