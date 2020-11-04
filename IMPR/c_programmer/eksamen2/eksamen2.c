/* Navn: Benjamin Clausen Bennetzen 
 * Mail: bbenne20@student.aau.dk
 * Gruppe: A306
 * Studieretning: Datalogi */

/* the program uses a compare function from tutorialspoint.com to make use of qsort. The function is described in greater detail just above the definition of it */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* main yatzy function prototype */
void yatzy(void);

/* basic function prototypes */
int roll_die(void);
void roll_multiple_dice(int* dice, int n_dice);
void print_arr(int* dice, int n_dice);
void empty_scoreboard(int* scoreboard, int size);
void print_scoreboard(int* scoreboard, int size);

/* specific roll prototypes */
int singles(int* dice, int n_dice, int num);
void upper_section(int* dice, int n_dice, int* scoreboard);
int n_of_a_kind(int* dice, int n_dice, int n_kind);
int straight(int* dice, int n_dice, int start_num);
int highest_5(int* dice, int n_dice);

/* compare function prototype */
int compare(const void* a, const void* b);

enum rolls{ones, twes, threes, fours, fives, sixes, bonus,
            three_of_a_kind, four_of_a_kind, full_house, sm_straight, lg_straight, five_of_a_kind, chance};

int main(void) {
    time_t t;
    srand((unsigned) time(&t));
    yatzy(); 
    return 0;
}

/* main function for the yatzy program */
void yatzy(void) {
    int n_dice = 0,
        scoreboard_size = chance - 1;
    int scoreboard[scoreboard_size];
    
    empty_scoreboard(scoreboard, scoreboard_size);

    /* get an input greater than or equal to 5 */
    do {
        printf("number of dice\n");
        scanf(" %d", &n_dice);
    } while (n_dice < 5);

    /* array with dice rolls */
    int dice[n_dice];
    
    upper_section(dice, n_dice, scoreboard);

    print_scoreboard(scoreboard, scoreboard_size);
}

/* return a number from 1 to 6 */
int roll_die(void) {
    return rand() % 6 + 1;
}

/* rolls dice and replaces the numbers in the array of dice for all die in dice */
void roll_multiple_dice(int* dice, int n_dice) {
    int i;
    for (i = 0; i < n_dice; i++) {
        *(dice + i) = roll_die();
    }
}

/* prints all values in an array with each value followed by a space */
void print_arr(int* dice, int n_dice) {
    int i;
    for (i = 0; i < n_dice; i++) {
        printf("%d ", *(dice + i));
    }
    printf("\n");
}

/* sets all values of the scoreboard to 0 */
void empty_scoreboard(int* scoreboard, int size) {
    int i;
    for (i = 0; i < size; i++) {
        *(scoreboard + i) = 0;
    }
}

/* prints the scoreboard */
void print_scoreboard(int* scoreboard, int size) {
    int total_before_bonus = 0,
        i;

    for (i = ones; i <= sixes; i++) {
        total_before_bonus += *(scoreboard + i);
    }

    int total_upper = total_before_bonus + *(scoreboard + bonus);

    int total_lower = 0;
    for (i = three_of_a_kind; i <= chance; i++) {
        total_lower += *(scoreboard + i);
    }

    int grand_total = total_upper + total_lower;

    printf("Upper Section|  Score\n");
    printf("Aces         |  %d   \n", *(scoreboard + ones));
    printf("Twos         |  %d   \n", *(scoreboard + twes));
    printf("Threes       |  %d   \n", *(scoreboard + threes));
    printf("Fours        |  %d   \n", *(scoreboard + fours));       
    printf("Fives        |  %d   \n", *(scoreboard + fives));
    printf("Sixes        |  %d   \n", *(scoreboard + sixes));
    printf("Total        |  %d   \n", total_before_bonus);
    printf("Bonus        |  %d   \n", *(scoreboard + bonus));
    printf("Total Upper  |  %d   \n", total_upper);
    printf("Lower Section|       \n");
    printf("3 of a kind  |  %d   \n", *(scoreboard + three_of_a_kind));
    printf("4 of a kind  |  %d   \n", *(scoreboard + four_of_a_kind));
    printf("Full House   |  %d   \n", *(scoreboard + full_house));
    printf("Sm Straight  |  %d   \n", *(scoreboard + sm_straight));
    printf("Lg Straight  |  %d   \n", *(scoreboard + lg_straight));
    printf("Yahtzee      |  %d   \n", *(scoreboard + five_of_a_kind));
    printf("Chance       |  %d   \n", *(scoreboard + chance));
    printf("Total Lower  |  %d   \n", total_lower);
    printf("Grand Total  |  %d   \n", grand_total);
}

/* take an array, size of the array and a number to look for as input. it then finds all instances of that number and returns the sum */
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

/* rolls all singles and prints the rolls and results */
void upper_section(int* dice, int n_dice, int* scoreboard) {
    int sum = 0;

    int i;
    for (i = 0; i < 6; i++) {
        roll_multiple_dice(dice, n_dice);                   /* get new batch of rolls */
        printf("Rolled ");
        print_arr(dice, n_dice);                            /* print the rolls */
        *(scoreboard + i) = singles(dice, n_dice, i + 1);   /* calculate the score for a single i.e 1, 2,..,6 and add it to the total */
        sum += *(scoreboard + i);
        printf("Score: %d\n", *(scoreboard + i));        
    }

    if (sum >= 63) {
        *(scoreboard + bonus) = 35;
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
