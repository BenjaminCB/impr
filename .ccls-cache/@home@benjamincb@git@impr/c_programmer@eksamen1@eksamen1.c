/* Navn: Benjamin Clausen Bennetzen 
 * Mail: bbenne20@student.aau.dk
 * Gruppe: A306
 * Studieretning: Datalogi */

/* in the assignment description it is stated that you have to make the operand equal to 0.0 if a uniary operation has been sent. In my program that doesn't make a difference, so i have choosen not to do it */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* define names far the mathematical operations */
#define RECIPROCAL 33      /* ! */
#define SQRT 35            /* # */
#define SWITCH_SIGN 37     /* % */ 
#define MULTIPLICATE 42    /* * */ 
#define ADD 43             /* + */ 
#define SUB 45             /* - */ 
#define DIVIDE 47          /* / */ 
#define POWER 94           /* ^ */ 
#define QUIT 113           /* q */ 

/* prototype declarations */
void scan_data(char *pOperator, double *p_operand);
void do_next_op(double *p_accumulator, char operator, double operand);
double run_calculator(void);
int validate_data(char c, int n);
double reciprocal(double a);

int main(void) {
    run_calculator();
    return 0;
}

/* function that runs the calculator. It takes user operators and operand to calculate a number. It prints partial and final results. The function returns the final value */
double run_calculator() {
    double accumulator = 0.0,
           operand = 0.0;
    char operator = 0; /* NULL */
    
    /* do calculations until the user quits */
    while(operator != QUIT) { 
        printf("Enter operator, and an optional operand: ");
        scan_data(&operator, &operand);
        do_next_op(&accumulator,operator, operand);
    }

    printf("Final result is: %f\n", accumulator);

    return accumulator;
}

/* prompts the user for inputs until its a valid input */
void scan_data(char *p_operator, double *p_operand) {
    int valid = 0;
    int input_size = 100; /* assumption that input < 100 */
    while(!valid) {
        char* input= (char*) malloc(sizeof(char) * input_size);
        int n_inputs;
        fgets(input, input_size, stdin);
        n_inputs = sscanf(input, " %c %lf", p_operator, p_operand);
        valid = validate_data(*p_operator, n_inputs);
        free(input);
    }
}

/* checks the operator to see if it is valid. If not it returns -' */
int validate_data(char c, int n) {
    int res = 0;
    /* if there is a succesful uniary input return 1. if the is a succesful binary input check if there where two succesful inputs */
    switch(c) {
        case RECIPROCAL:
        case SQRT:
        case SWITCH_SIGN:
        case QUIT:
            res = 1;
            break;
        case MULTIPLICATE: 
        case ADD:
        case SUB: 
        case DIVIDE: 
        case POWER: 
            if (n == 2) {
                res = 1;
                break;
            }
        default: 
            printf("Not a valid operator or operand, try again: "); 
    }
    return res;
}

/* checks the operand type and makes the corrosponding calculation */
void do_next_op(double *p_accumulator, char operator, double operand) {
    switch(operator) {
        case RECIPROCAL:
            *p_accumulator = reciprocal(*p_accumulator); break;
        case SQRT:
            *p_accumulator = *p_accumulator >= 0 ? sqrt(*p_accumulator) : *p_accumulator; break;
        case SWITCH_SIGN:
            *p_accumulator *= -1; break;
        case MULTIPLICATE: 
            *p_accumulator *= operand; break;
        case ADD:
            *p_accumulator += operand; break;
        case SUB: 
            *p_accumulator -= operand; break;
        case DIVIDE: 
            *p_accumulator /= operand != 0 ? operand : 1; break;
        case POWER: 
            *p_accumulator = pow(*p_accumulator, operand); break;
        case QUIT: 
            return;
        default: 
            printf("error\n"); 
            return; 
    }
    printf("Partial result: %f\n", *p_accumulator);
}

/* return the recprocal of a so long as a is not equal to zero */
double reciprocal(double a) {
    return a != 0 ? 1 / a : a;
}

