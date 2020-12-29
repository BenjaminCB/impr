#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return ( *(double*)a - *(double*)b );
}

int main (void) {
    double* dp = (double*) malloc(100 * sizeof(double));
    int i;

    for (i = 0; i < 100; i++) {
        dp[i] = i % 10;
    }

    qsort(dp, 100, sizeof(double), compare);


    for (i = 0; i < 100; i++) {
        printf("%f\n", dp[i]);
    }

    free(dp);
    return 0;
}