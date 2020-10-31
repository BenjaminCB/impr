#include <stdio.h>
#include <stdlib.h>

int sum_iter(int n) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
       res += n; 
    }
    return res;
}

int sum_formular(int n) {
    return (n + 1) * n / 2;
}

int population_projection (double p, int n, int m) {
    int res = 0;
    while (n < m) {
        n *= (1 + p);
        res++;
    }
    return res;
}

int main(void){
    if (sum_iter(10) == sum_formular(10)) {
        printf("true");
    } else {
        printf("false");
    }
    return 0;
}
