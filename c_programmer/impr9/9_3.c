#include <stdlib.h>
#include <stdio.h>

double combine_right (double a[], int n, double (*combiner) (double, double));
double max(double, double);
double min(double, double);
double plus(double, double);
double minus(double, double);

int main(void) {
    double arr[100];
    int i;
    for (i = 0; i < 100; i++) {
        arr[i] = (double) i;
    }

    printf("%f\n", combine_right(arr, 100, &max));
    printf("%f\n", combine_right(arr, 100, &min));
    printf("%f\n", combine_right(arr, 100, &plus));
    printf("%f\n", combine_right(arr, 100, &minus));

    return 0;
}

double combine_right (double a[], int n, double (*combiner) (double, double)) {
    double res = a[0];
    int i;
    for (i = 1; i < n; i++) {
        res = combiner(res, a[i]);
    }
    return res;
}

double max (double a, double b){
  return a > b ? a : b;
}

double min (double a, double b){
  return a > b ? b : a;
}

double plus(double a, double b){
  return a + b;
}

double minus(double a, double b){
  return a - b;
}