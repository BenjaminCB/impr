#include <stdlib.h>
#include <stdio.h>

#define MAX_NAME_LEN 50

typedef struct person {
    char fornavn[MAX_NAME_LEN];
    char efternavn[MAX_NAME_LEN];
    char vejnavn[MAX_NAME_LEN];
    int vejnummer;
    int postnummer;
    char bynavn[MAX_NAME_LEN];
} Person;

int main(void) {
    FILE* file = fopen("./13_5.txt", "r");
    FILE* out = fopen("./13_5out.txt", "w");
    int i;
    Person persons[11];

    for (i = 0; i < 11; i++) {
        fscanf(file, "%[^\n]s%[^,]s %[^\n]s %d %d %[^.]s", persons[i].fornavn, persons[i].efternavn,
                                             persons[i].vejnavn, &persons[i].vejnummer,
                                             &persons[i].postnummer, persons[i].bynavn);
        fprintf(out, "%s: %s", persons[i].bynavn, persons[i].fornavn);
    }

    fclose(file);
    fclose(out);

    return 0;
}