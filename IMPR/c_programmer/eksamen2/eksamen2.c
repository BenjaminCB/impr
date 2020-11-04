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
void print_scoreboard(int* scoreboard, int upper_score, int lower_score);
void roll_and_print(int* dice, int n_dice);

/* specific roll prototypes */
int upper_section(int* dice, int n_dice, int* scoreboard);
int singles(int* dice, int n_dice, int num);
int count_num_of_n(int* dice, int n_dice, int n);
int lower_section(int* dice, int n_dice, int* scoreboard);
int n_of_a_kind(int* dice, int n_dice, int n_kind);
int n_in_a_row(int* arr, int start_index, int n);
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
        scoreboard_size = chance - 1,
        upper_score,
        lower_score;
    int scoreboard[scoreboard_size];
    
    empty_scoreboard(scoreboard, scoreboard_size);

    /* get an input greater than or equal to 5 */
    do {
        printf("number of dice\n");
        scanf(" %d", &n_dice);
    } while (n_dice < 5);

    /* array with dice rolls */
    int dice[n_dice];
    
    upper_score = upper_section(dice, n_dice, scoreboard);
    lower_score = lower_section(dice, n_dice, scoreboard);

    print_scoreboard(scoreboard, upper_score, lower_score);
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

void roll_and_print(int* dice, int n_dice) {
    roll_multiple_dice(dice, n_dice); 
    printf("Rolled ");
    print_arr(dice, n_dice);  
}

/* sets all values of the scoreboard to 0 */
void empty_scoreboard(int* scoreboard, int size) {
    int i;
    for (i = 0; i < size; i++) {
        *(scoreboard + i) = 0;
    }
}

/* prints the scoreboard */
void print_scoreboard(int* scoreboard, int upper_score, int lower_score) {
    int upper_score_before_bonus = upper_score - *(scoreboard + bonus),
        grand_total = upper_score + lower_score;

    printf("Upper Section|  Score\n");
    printf("Aces         |  %d   \n", *(scoreboard + ones));
    printf("Twos         |  %d   \n", *(scoreboard + twes));
    printf("Threes       |  %d   \n", *(scoreboard + threes));
    printf("Fours        |  %d   \n", *(scoreboard + fours));       
    printf("Fives        |  %d   \n", *(scoreboard + fives));
    printf("Sixes        |  %d   \n", *(scoreboard + sixes));
    printf("Total        |  %d   \n", upper_score_before_bonus);
    printf("Bonus        |  %d   \n", *(scoreboard + bonus));
    printf("Total Upper  |  %d   \n", upper_score);
    printf("Lower Section|       \n");
    printf("3 of a kind  |  %d   \n", *(scoreboard + three_of_a_kind));
    printf("4 of a kind  |  %d   \n", *(scoreboard + four_of_a_kind));
    printf("Full House   |  %d   \n", *(scoreboard + full_house));
    printf("Sm Straight  |  %d   \n", *(scoreboard + sm_straight));
    printf("Lg Straight  |  %d   \n", *(scoreboard + lg_straight));
    printf("Yahtzee      |  %d   \n", *(scoreboard + five_of_a_kind));
    printf("Chance       |  %d   \n", *(scoreboard + chance));
    printf("Total Lower  |  %d   \n", lower_score);
    printf("Grand Total  |  %d   \n", grand_total);
}

/* rolls all singles and prints the rolls and results */
int upper_section(int* dice, int n_dice, int* scoreboard) {
    int sum = 0;

    int i;
    for (i = 0; i < 6; i++) {
        *(scoreboard + i) = singles(dice, n_dice, i + 1);   /* calculate the score for a single i.e 1, 2,..,6 and add it to the total */
        sum += *(scoreboard + i);
        printf("Score: %d\n", *(scoreboard + i));        
    }

    if (sum >= 63) {
        *(scoreboard + bonus) = 35;
        sum += 35;
    }

    return sum;
}

/* take an array, size of the array and a number to look for as input. it then finds all instances of that number and returns the sum */
int singles(int* dice, int n_dice, int num) {
    roll_and_print(dice, n_dice);
    
    qsort(dice, n_dice, sizeof(int), compare);

    return num * count_num_of_n(dice, n_dice, num);
}

int count_num_of_n(int* dice, int n_dice, int n) {
    int res = 0,
        i = 0;
    while (*(dice + i) != n && i < n_dice) {
        i++;
    }
    
    while (*(dice + i) == n && i < n_dice) {
        res++;
        i++;
    }
    
    return res;
}

int lower_section(int* dice, int n_dice, int* scoreboard) {
    int sum = 0;
    *(scoreboard + three_of_a_kind) = n_of_a_kind(dice, n_dice, 3);
    sum += *(scoreboard + three_of_a_kind);

    *(scoreboard + four_of_a_kind) = n_of_a_kind(dice, n_dice, 4);
    sum += *(scoreboard + four_of_a_kind);

    *(scoreboard + five_of_a_kind) = n_of_a_kind(dice, n_dice, 5);
    sum += *(scoreboard + five_of_a_kind);

    return sum;
}

int n_of_a_kind(int* dice, int n_dice, int n) {
    int res = 0;

    roll_and_print(dice, n_dice);

    qsort(dice, n_dice, sizeof(int), compare); 

    int i;
    for (i = 1; i <= 6; i++) {
        if (n <= count_num_of_n(dice, n_dice, i)) {
            res = n * i;
        }
    }

    return res;
}

/* compare function from tutorialspoint.com. 
 * takes a void pointer a and b
 * typecasts the pointer to integer pointers
 * derefrences the pointers and finds the difference
 * return a positive number if a > b, a negative if b > a and a 0 if they are equal */
int compare (const void* a, const void* b) {
   return ( *(int*)a - *(int*)b );
}
