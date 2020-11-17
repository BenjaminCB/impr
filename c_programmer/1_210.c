#include <stdio.h>
#include <stdlib.h>

double item, product, x, y;
int zeroCount = 0,
    minusSum = 0,
    plusSum = 0;

int main(void) {
    scanf(" %lf %lf %lf %lf", &item, &product, &x, &y);

    if (item) {
        product *= item;
    }

    printf("%lf\n", product);

    y = (x - y) > (y - x) ? (x - y) : (y - x);

    printf("%lf\n", y);

    if (x < 0) {
        minusSum += x;
    } else if (x == 0) {
        zeroCount++;
    } else {
        plusSum += x;
    }

    printf("%d %d %d\n", minusSum, zeroCount, plusSum);

    return 0;
}