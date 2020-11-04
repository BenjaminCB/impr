/* Navn: Benjamin Clausen Bennetzen 
 * Mail: bbenne20@student.aau.dk
 * Gruppe: A306
 * Studieretning: Datalogi */

#include <stdlib.h>
#include <stdio.h>

void yatzy(void);

int roll_die(void);
void roll_multiple_dice(int* dice, int n_dice);
void print_arr(int* dice, int n_dice);

int singles(int* dice, int n_dice, int num);
void roll_all_singles(int* dice, int n_dice, int* p_total);
int n_of_a_kind(int* dice, int n_dice, int n_kind);
int straight(int* dice, int n_dice, int start_num);
int highest_5(int* dice, int n_dice);

int compare(const void* a, const void* b);

int main(void) {
    srand((unsigned) time(0));
    yatzy(); 
    return 0;
}

void yatzy(void) {
    int n_dice = 0,
        total = 0;

    /* get an input greater than or equal to 5 */
    do {
        printf("number of dice\n");
        scanf(" %d", &n_dice);
    } while (n_dice < 5);

    /* array with dice rolls */
    int dice[n_dice];
    
    roll_all_singles(dice, n_dice, &total);
}

int roll_die(void) {
    return rand() % 6 + 1;
}

void roll_multiple_dice(int* dice, int n_dice) {
    int i;
    for (i = 0; i < n_dice; i++) {
        *(dice + i) = roll_die();
    }
}

void print_arr(int* dice, int n_dice) {
    int i;
    for (i = 0; i < n_dice; i++) {
        printf("%d ", *(dice + i));
    }
    printf("\n");
}

int singles(int* dice, int n_dice, int num) {
    int res = 0; 

    qsort(dice, n_dice, sizeof(int), compare);

    int i = 0;
    while (*(dice + i) != num && i < n_dice) {
        i++;
    }
    
    while (*(dice + i) == num && i < n_dice) {
        res += num;
        i++;
    }

    return res;
}

void roll_all_singles(int* dice, int n_dice, int* p_total) {
    int i;
    for (i = 1; i <= 6; i++) {
        roll_multiple_dice(dice, n_dice);
        printf("Rolled ");
        print_arr(dice, n_dice);
        *p_total += singles(dice, n_dice, i);
        printf("total: %d\n", *p_total);        
    }
}

/* compare function from tutorialspoint.com. 
 * takes a void pointer a and b
 * typecasts the pointer to integer pointers
 * derefrences the pointers and finds the difference
 * return a positive number if a > b, a negative if b > a and a 0 if they are equal */
int compare (const void* a, const void* b) {
   return ( *(int*)a - *(int*)b );
}
