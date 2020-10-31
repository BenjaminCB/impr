#include <stdio.h>
#include <stdlib.h>

double newton(double intialGuess, double n, int *nCyclesLeft);

int main(void) {
    int n = 10;
    printf("sqrt(2) = %lf", newton(2.0, 2.0, &n));
    return 0;
}

double newton(double intialGuess,double n, int *nCyclesLeft) {
    double new_n;
    if (*nCyclesLeft == 0) {
        return n;
    }
    *nCyclesLeft--;
    new_n = n - (n * n - intialGuess) / (2 * n);
    newton(intialGuess, new_n, nCyclesLeft);
}
