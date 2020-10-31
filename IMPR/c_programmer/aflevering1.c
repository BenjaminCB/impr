/* Skriv et C program, som indlæser et helt antal 
sekunder og som omregner dette tal til uger, dage, timer, 
minutter og sekunder på sædvanlig vis. Programmet skal udskrive 
antallet af uger, dage, timer, minutter og sekunder på skærmen.

Mere præcist skal de omregnede sekunder være i intervallet 0..59, 
de omregnede minutter skal være i intervallet 0..59, de omregnede timer
skal være i intervallet 0..23, og de omregnede dage i intervallet 0..6. 
Ugetallet kan være vilkårligt stort.

Målet med opgaven er primært at træne dig i brugen af heltalsdivision / 
og rest operatoren ved heltalsdivision %. Sekundært sætter opgaven fokus 
på symbolske konstanter og simpel brug af scanf og printf. */

/*Dette program tager it input (int) som er antallet af sekunder
som brugeren gerne vil have omregnet. Programmet har et output som or antallet i sekinder
fordelt paa uger, dage, time, minutter og sekunder.*/

#include <stdio.h>

/*konstanter defineres*/
#define SEK_PER_MIN 60
#define SEK_PER_TIME (60 * 60)
#define SEK_PER_DAG (60 * 60 * 24)
#define SEK_PER_UGE (60 * 60 * 24 * 7)

/* Variabler intialiseres*/
int uger, dage, timer, min, sek;

int main(void) {
    /*start instruktioner printes*/
    printf("Skriv dit oenskede antal sekunder \n");

    /*scanner intastning af en integer*/
    scanf("%d", &sek);
    

    /*sekunder fordeles og sekunders vaerdi aendres 
      saa den har en vaerdi svarende til resten*/
    uger = sek / SEK_PER_UGE;
    sek %= SEK_PER_UGE;

    dage = sek / SEK_PER_DAG;
    sek %= SEK_PER_DAG;

    timer = sek / SEK_PER_TIME;
    sek %= SEK_PER_TIME;

    min = sek / SEK_PER_MIN;
    sek %= SEK_PER_MIN;

    /*resultatet printes*/
    printf("%d uger, %d dage, %d timer, %d minutter og %d sekunder", uger, dage, timer, min, sek);

    return 0;
}


