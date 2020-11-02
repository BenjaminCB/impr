/*Det er ofte nyttigt at kunne afgøre, om et punkt i et 
koordinatsystem er placeret inden i eller udenfor en bestemt cirkel.

Skriv et program med tre doubles r, x og y.   
r fortolkes som radius af en cirkel omkring punktet (0,0). 
x og y er koordinaterne (x, y) af et punkt.

Programmet skal afgøre om punktet (x, y) er placeret inden i cirklen, 
på cirkelperiferien, eller uden for cirklen. Der er altså tre tilfælde. 
I bedes have tre logiske udtryk, assignet til tre logiske variable, 
som afspejler de tre forskellige situationer.

Kan I lave én printf med brug af betingede udtryk (?:), der udskriver 
'inden i'/'uden for' og 'på' cirklen, baseret på de logiske udtryks værdi?

Hint: Det kan være svært at ramme periferien eksakt, fordi vi regner med doubles. 
Derfor kan I antage at punktet er 'på periferien' hvis det er ganske tæt på periferien. 
Indfør en symbolsk konstant DELTA, der fortæller hvor meget vi ønsker at 
kunne afvige fra et "perfect hit".*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DELTA 0.1

double x, y, r, l;

int main(void) {
    scanf(" %lf %lf %lf", &x, &y, &r);
    l = sqrt(x * x + y * y);
    
    if (l < r - DELTA) {
        printf("within circle\n");
    } else if (l > r + DELTA) {
        printf("outside circle\n");
    } else {
        printf("on circle\n");
    }

    return 0;
}