/*Dette program tager it input (int) som er antallet af sekunder
som brugeren gerne vil have omregnet. Programmet har et output som or antallet i sekinder
fordelt paa uger, dage, time, minutter og sekunder.*/

#include <stdio.h>

/*konstanter defineres*/
#define SEK_PER_MIN 60
#define SEK_PER_TIME (60 * 60)

/* Variabler intialiseres*/
int timer, min, sek, rest;

int main(void) {
    /*start instruktioner printes*/
    printf("Skriv dit oenskede antal sekunder \n");

    /*scanner intastning af en integer*/
    scanf("%d", &sek);

    /*tjekker special cases hvor sekunder er under 60 sek, hvis en af disse er sande springes restan af programmet over*/
    if (sek == 1) {
        printf("%d sekund svarer til %d sekund", sek, sek);
        return 0;
    } else if (!sek) {
        return 0;
    } else if (sek < 0) {
        printf("Du har indtastet et negativt tal");
        return 0;
    } else if (sek < SEK_PER_MIN) {
        printf("%d sekunder svarer til %d sekunder", sek, sek);
        return 0;
    }

    /*foerste del printes*/
    printf("%d sekunder svarer til: ", sek);

    rest = sek;

    /*timer fordeles og printes*/
    timer = rest / SEK_PER_TIME;
    rest %= SEK_PER_TIME;

    if (timer > 1) {
        printf("%d timer, ", timer);
    } else if (timer == 1) {
        printf("%d time, ", timer);
    }


    /*minutter fordeles og printes*/
    min = rest / SEK_PER_MIN;
    rest %= SEK_PER_MIN;
    char comma[] = (rest > 0 ? ", ":" ");
    if (min > 1) {
        printf("%d minutter%s", min, comma);
    } else if (min == 1) {
        printf("%d minut, ", min);
    }

    /*de resterende sekunder printes*/
    if (rest > 1) {
        printf("og %d sekunder.", rest);
    } else if (rest == 1) {
        printf("og %d sekund.", rest);
    }

    return 0;
}
