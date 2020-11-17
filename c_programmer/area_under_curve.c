#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* prototype declarations */
double trap(double a, double b, int n, double (*fn)(double));
double g(double x);
double h(double x);

int main(void) {
    /* print different values of the estimates */
    int i;
    for (i = 2; i <= 128; i *= 2) {
        printf("g: %5lf     h: %5lf\n", trap(0, 3.14159, i, &g), trap(-2, 2, i, &h));
    }
    printf("\nAktuelle vaerdier:\ng: 5.8696       h: 2pi\n");

    return 0;
}

/* integral estimator function */
double trap(double a, double b, int n, double (*fn)(double)) {
    /* variables needed to calculate the area */
    double h = (b - a) / n,
           f_a = fn(a),
           f_b = fn(b),
           sigma = 0;

    /* calculation of the sigma value */
    int i;
    for (i = 1; i < n; i++) {
        sigma += fn(a + i * h);
    }
    sigma *= 2;

    /* return the result */
    return h / 2 * (f_a + f_b + sigma);
}

/* the function g(x) */
double g(double x) {
    return pow(x, 2) * sin(x);
}

/* the function h(x) */
double h(double x) {
    return sqrt(4 - pow(x, 2));
}
