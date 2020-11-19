#include <stdio.h>
#include <stdlib.h>

struct fraction {
    int numerator, denominator;
};
typedef struct fraction fraction;

void swap(int* a, int* b);
int gcd(int a, int b);
void shorten(fraction* frac);
void print_fraction(fraction* frac);
void multiply(fraction* frac, int val);
fraction multiply_frac(fraction* f1, fraction* f2);
fraction add_fraction(fraction* f1, fraction* f2);

int main(void) {

    return 0;
}

/* swap the values of a and b with pointers */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* find the gcd of a and b */
int gcd(int a, int b) {
    int remainder;

    /* if a is bigger than b then swap their values */
    if (a > b) {
	swap(&a, &b);
    }

    /* run the algorithm to find gcd */
    while (a > 0){
	remainder = b % a;
	b = a;
	a = remainder;
    }
    
    /* return gcd */
    return b;
}

void shorten(fraction* frac) {
    int divisor = gcd(frac->numerator, frac->denominator);
    frac->numerator /= divisor;
    frac->denominator /= divisor;
}

void print_fraction(fraction* frac) {
    printf("%d / %d\n", frac->numerator, frac->denominator);
}

void multiply(fraction* frac, int val) {
    frac->numerator *= val;
    shorten(frac);
}

fraction multiply_frac(fraction* f1, fraction* f2) {
    fraction frac = {f1->numerator * f2->numerator,
                        f1->denominator * f2->denominator};
    shorten(&frac);
    return frac;
}

fraction add_fraction(fraction* f1, fraction* f2) {
    fraction frac = {f1->numerator * f2->denominator + f2->numerator * f1->denominator,
                        f1->denominator * f2->denominator};
    shorten(&frac);
    return frac;
}
