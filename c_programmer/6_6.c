#include <stdlib.h>
#include <stdio.h>

#define euroRate 0.89
#define dkkRate 6.66
#define rubRate 66.43
#define yenRate 119.9

void conversion(double dollar, double *euro, double *dkk, double *rub, double *yen);

int main(void) {
    double euro,
           dkk,
           rub,
           yen;

    printf("  Dollar    Euro     DKK     Rub     Yen\n");
    for(double i = 1; i <= 10; i++) {
        conversion(i, &euro, &dkk, &rub, &yen);
        printf("  %4lf  %4lf  %4lf  %4lf  %4lf\n", i, euro, dkk, rub, yen); 
    }
    return 0;
}


void conversion(double dollar, double *euro, double *dkk, double *rub, double *yen) {
    *euro = dollar * euroRate;
    *dkk = dollar * dkkRate;
    *rub = dollar * rubRate;
    *yen = dollar * yenRate;
}
