#include <stdio.h>

/* declare prototypes */
void swap(int *a, int *b);
int gcd(int a, int b);

int main(void) {
    /* intialize variables */
    int a = 1,
	b = 1;

    /* run loop until one or both of the inputs are negative */
    while(a >= 0 && b >= 0) {
        printf("type two integers:\n");
        scanf("%d %d", &a, &b);
        printf("gcd(%d, %d) = %d\n", a, b, gcd(a, b));
    }

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
