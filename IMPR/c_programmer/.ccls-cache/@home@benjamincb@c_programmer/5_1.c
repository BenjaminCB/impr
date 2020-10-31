/* this is a small program that takes coefficients for a quadratic equation and prints the solution(s) if there are any */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* prototype declarations */
void solveQuadraticEquation(double a, double b, double c);
double discriminant(double a, double b, double c);
double root(int sign, double a, double b, double c, double d);

void quadraticInput(double *pa, double *pb, double *pc);
int checkInput(double *pa, double *pb, double *pc);
void checkExit(double a, double b, double c); 

int main(void) {
    double a, b, c;

    /* loop through until user exits program */
    quadraticInput(&a, &b, &c);
    while (1) {
        solveQuadraticEquation(a, b, c);
        quadraticInput(&a, &b, &c);
    }

    return 0;
}

/* prompts the user for an input and checks for spacial cases */
void quadraticInput(double *pa, double *pb, double *pc) {
    /* take an input until we have a valid input */
    do {
        printf("Type your three coefficients a, b and c. Make sure that a != 0.\n");
        scanf(" %lf %lf %lf", pa, pb, pc);	

    } while (!checkInput(pa, pb, pc));
}

/* checks input */
int checkInput(double *pa, double *pb, double *pc) {
    checkExit(*pa, *pb, *pc);

    /* if a is zero this return is false */
    return *pa;
}

/* checks exit condition */
void checkExit(double a, double b, double c) {    
    if (a == 0 && b == 0 && c == 0) {
        printf("Goodbye\n");
        exit(0);
    }
}

/* Prints roots of the quadratic equation a * x*x + b * x + c = 0 */
void solveQuadraticEquation(double a, double b, double c){
    double d, root1, root2;

    d = discriminant(a, b, c);

    /* calculate roots if there are any */
    if (d < 0) {
        printf("No roots\n");
    } else if (d == 0){
        root1 = -b/(2*a);
        printf("One root: %f\n", root1);
    } else {
        root1 = root(1, a, b, c, d);
        root2 = root(-1, a, b, c, d);
        printf("Two roots: %f and %f\n", root1, root2);
    }
}   

/* calculate discriminant */
double discriminant (double a, double b, double c) {
    return b * b - 4 * a * c;
}

/* calculate one af the roots based on the sign value */
double root (int sign, double a, double b, double c, double d) {
    return (-b + sign * sqrt(d)) / (2 * a);
}
