/* Navn: Benjamin Clausen Bennetzen 
 * Mail: bbenne20@student.aau.dk
 * Gruppe: A306
 * Studieretning: Datalogi */

/*+    for addition af akkumulatoren med operanden
  -    for subtraktion af akkumulatoren med operanden
  *    for multiplikation af akkumulatoren med operanden
  /    for division af akkumulatoren med operanden
  ^    for potensopløftning af akkumulatoren med operanden

  #    for kvadratroden af akkumulatoren
  %    for at vende fortegnet af akkumulatoren
  !    for at dividere 1 med akkumulatoren
  q    for at afslutte regnemaskinen med slutresultatet */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void scan_data(char *p_operator, double *p_operand);
void do_next_op(double *p_accumulator, char operator, double operand);
double run_calculator(void);
int check_operator(char c);
double power(double a, double b);
double reciprocal(double a);

int main(void) {
    printf("Enter operator, and an optional operand:\n");
    printf("Final result is: %lf", run_calculator());
    return 0;
}

double run_calculator() {
    double accumulator = 0.0,
           operand = 0.0;
    char operator;
    
    scan_data(&operator, &operand);
    do_next_op(&accumulator,operator, operand);

    return accumulator;
}


void scan_data(char *p_operator, double *p_operand) {
    scanf(" %c %lf ", p_operator, p_operand);
    
}

void do_next_op(double *p_accumulator, char operator, double operand) {
    switch(operator) {
        case 33:        /* ! */
            *p_accumulator = reciprocal(*p_accumulator); break;
        case 35:        /* # */
            *p_accumulator = sqrt(*p_accumulator); break;
        case 37:        /* % */
            *p_accumulator *= -1; break;
        case 42:        /* * */ 
            *p_accumulator *= operand; break;
        case 43:        /* + */
            *p_accumulator += operand; break;
        case 45:        /* - */ 
            *p_accumulator -= operand; break;
        case 47:        /* / */ 
            *p_accumulator /= operand; break;
        case 94:        /* ^ */ 
            *p_accumulator = power(*p_accumulator, operand); break;
        case 113:       /* q */ 

        default:  /* err */ 
           printf("error"); 
    }
}
/* checks the operator to see if it is valid. If not it returns -' */
int check_operator(char c) {
    switch(c) {
        case 33:    return 0;        /* ! */
        case 35:    return 1;        /* # */
        case 37:    return 2;        /* % */
        case 42:    return 3;        /* * */ 
        case 43:    return 4;        /* + */
        case 45:    return 5;        /* - */ 
        case 47:    return 6;        /* / */ 
        case 94:    return 7;        /* ^ */ 
        case 113:   return 8;        /* q */ 
        default:    return -1;       /* err */ 
    }
}

double power(double a, double b) {
    double res = a;
    
    if (a == 0) {
        return 0;
    }

    if (b == 0) {
        return 1;
    }

    for (int i = 1; i <= b; i++) {
        res *= a;
    }

    return res;
}
