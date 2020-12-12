/* Navn: Benjamin Clausen Bennetzen 
 * Mail: bbenne20@student.aau.dk
 * Gruppe: A306
 * Studieretning: Datalogi */

/*the program follows this scoreboard https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fimages1.fanpop.com%2Fimages%2Fphotos%2F1300000%2FYahtzee-board-games-1319734-825-955.jpg&f=1&nofb=1 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* main yatzy function prototype */
void yatzy(void);
int response(void);
void empty_stdin(void);

/* basic function prototypes */
int roll_die(void);
void roll_multiple_dice(int* dice, int n_dice);
void print_arr(int* dice, int n_dice);
void empty_scoreboard(int* scoreboard, int size);
void print_scoreboard(int* scoreboard, int upper_score, int lower_score);
void count_dice(int* dice, int n_dice, int* dice_counter);
void roll_print_count(int* dice, int n_dice, int* dice_counter);

/* specific roll prototypes */
int upper_section(int* dice, int n_dice, int* dice_counter, int* scoreboard);
int lower_section(int* dice, int n_dice, int* dice_counter, int* scoreboard);
int n_of_a_kind(int* dice, int n_dice, int* dice_counter, int n_kind);
int full_house(int* dice, int n_dice, int* dice_counter);
int straight(int* dice, int n_dice, int* dice_coutner, int seq_size);
int check_straight(int* dice_counter, int index, int seq_size);
int highest_5(int* dice, int n_dice, int* dice_counter);

enum rolls{ones, twos, threes, fours, fives, sixes, bonus,
            three_of_a_kind, four_of_a_kind, house, sm_straight, lg_straight, five_of_a_kind, chance};

int main(void) {
    time_t t;
    srand((unsigned) time(&t)); /*get a seed based on time*/
    do {
        yatzy(); /*start a game of yatzy*/
    } while (response());
    return 0;
}

/* get a response from the user and return 1 for yes and 0 for no */
int response(void) {
    int res,            /*result of the function this a boolean*/
        answer;         /*this is the user input*/
    
    /*get user input and throw away the rest*/
    printf("Do you want to play again (y/n); ");
    answer = getc(stdin); 
    empty_stdin();
    
    /*check the answer and act accordingly*/
    switch (answer) {
        case 'y':
            res = 1; break;
        case 'n':
            res = 0; break;
        case EOF:
            res = 0; printf("Reached EOF. Exiting program\n"); break;
        default:
            res = 0; printf("You didn't enter (y/n) i'll assume you want to exit\n"); break;
            
    }

    return res;
}

/* empties stdin for extra characters that can affect the next user inputs */
void empty_stdin(void) {
    while(getc(stdin) != '\n');
}

/* main function for the yatzy program */
void yatzy(void) {
    int n_dice = 0,                     /*number of dice*/
        upper_score,                    /*total score for the upper section*/ 
        lower_score;                    /*total score for the lower section*/
    int scoreboard[chance + 1],         /*array for all the scores on the scoreboard*/
        dice_counter[6],                /*array that keeps track of how many there are of each die*/
        *dice;                          /*array with dice rolls*/
    
    /* get an input greater than or equal to 5 */
    do {
        printf("number of dice\n");
        scanf(" %d", &n_dice);
    } while (n_dice < 5);

    empty_stdin();

    /*allocate memory for the dice array*/
    dice = (int*) malloc(sizeof(int) * n_dice);
    

    /*do calculate all the rolls and scores*/
    upper_score = upper_section(dice, n_dice, dice_counter, scoreboard);
    lower_score = lower_section(dice, n_dice, dice_counter, scoreboard);

    /*print the scoreboard*/
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

/*counts how many of each die roll there is and saves it in the dice_counter array*/
void count_dice(int* dice, int n_dice, int* dice_counter) {
    /*reset the dice_counter array*/
    int i;
    for (i = 0; i <= 5; i++) {
        *(dice_counter + i) = 0;
    }

    /*for each roll in dice up the appropriate value in dice_counter by one*/
    for (i = 0; i < n_dice; i++) {
        switch (*(dice + i)) {
            case 1:
                (*(dice_counter + ones))++; break;
            case 2:
                (*(dice_counter + twos))++; break;
            case 3:
                (*(dice_counter + threes))++; break;
            case 4:
                (*(dice_counter + fours))++; break;
            case 5:
                (*(dice_counter + fives))++; break;
            case 6:
                (*(dice_counter + sixes))++; break;
            default:
                printf("error in switch\n");
        }
    }
}

/*rolls all the dice, prints the values of those dice and counts them*/
void roll_print_count(int* dice, int n_dice, int* dice_counter) {
    roll_multiple_dice(dice, n_dice); 
    printf("Rolled ");
    print_arr(dice, n_dice);  
    count_dice(dice, n_dice, dice_counter);
}

/* prints the scoreboard */
void print_scoreboard(int* scoreboard, int upper_score, int lower_score) {
    /*calculate missing scores*/
    int upper_score_before_bonus = upper_score - *(scoreboard + bonus),
        grand_total = upper_score + lower_score;

    printf("Upper Section|  Score\n");
    printf("Aces         |  %d   \n", *(scoreboard + ones));
    printf("Twos         |  %d   \n", *(scoreboard + twos));
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
    printf("Full House   |  %d   \n", *(scoreboard + house));
    printf("Sm Straight  |  %d   \n", *(scoreboard + sm_straight));
    printf("Lg Straight  |  %d   \n", *(scoreboard + lg_straight));
    printf("Yahtzee      |  %d   \n", *(scoreboard + five_of_a_kind));
    printf("Chance       |  %d   \n", *(scoreboard + chance));
    printf("Total Lower  |  %d   \n", lower_score);
    printf("Grand Total  |  %d   \n", grand_total);
}

/* rolls all singles and prints the rolls and results, and return the sum total */
int upper_section(int* dice, int n_dice, int* dice_counter, int* scoreboard) {
    int sum = 0;

    int i;
    for (i = ones; i <= sixes; i++) {
        roll_print_count(dice, n_dice, dice_counter);
        *(scoreboard + i) = (i + 1) * *(dice_counter + i);      /* set the value at scoreboard[i] equal to the number that we are counting times how many there are of that number */
        sum += (i + 1) * *(dice_counter + i);                   /*add that sum number the the total of the upper section*/
        printf("Score: %d\n", *(scoreboard + i));               /*print the score for that roll*/ 
    }

    if (sum >= 63) {
        *(scoreboard + bonus) = 35;
        sum += 35;
    } else {
        *(scoreboard + bonus) = 0;
    }

    return sum;
}

/*calculate all the rolls for the bottem section and return the sum*/
int lower_section(int* dice, int n_dice, int* dice_counter, int* scoreboard) {
    int sum = 0;

    /*set scoreboard [three_of_a_kind] equal to the number of three in the roll also add that number to the total*/
    *(scoreboard + three_of_a_kind) = n_of_a_kind(dice, n_dice, dice_counter, 3);
    sum += *(scoreboard + three_of_a_kind);

    /*same as before but this there needs to be atleast four of a kind*/ 
    *(scoreboard + four_of_a_kind) = n_of_a_kind(dice, n_dice, dice_counter, 4);
    sum += *(scoreboard + four_of_a_kind);

    /*same as before but this time we check for a full house*/
    *(scoreboard + house) =  full_house(dice, n_dice, dice_counter);

    /*check for a small straight*/
    *(scoreboard + sm_straight) = straight(dice, n_dice, dice_counter, 4);
    sum += *(scoreboard + sm_straight);

    /*check for a large straight*/
    *(scoreboard + lg_straight) = straight(dice, n_dice, dice_counter, 5);
    sum += *(scoreboard + lg_straight);

    /*check for 5 of a kind if we have that set the scoreboard value to 50 since yatzy has a fixed score*/
    if (n_of_a_kind(dice, n_dice, dice_counter, 5)) {
        *(scoreboard + five_of_a_kind) = 50;
    } else {
        *(scoreboard + five_of_a_kind) = 0;
    }
    sum += *(scoreboard + five_of_a_kind);

    /*calculate the chance score*/
    *(scoreboard + chance) = highest_5(dice, n_dice, dice_counter);
    sum += *(scoreboard + chance);

    return sum;
}

/*check that we at least n numbers of any roll i.e 1, 2,.. or 6 and return the highest score*/
int n_of_a_kind(int* dice, int n_dice, int* dice_counter, int n) {
    int res = 0,
        i;

    roll_print_count(dice, n_dice, dice_counter);

    /*check starting from sixes since that will give the highest score and down to one*/
    for (i = sixes; i >= ones; i--) {
        if (n <= *(dice_counter + i)) {
            res = n * (i + 1);          /*if we have n numbers of that roll set the result equal to the score */
            break;
        }
    }

    printf("Score; %d\n", res);

    return res;
}

/*check for a full 3 of a kind and 2 of a kind, if there is one return 25*/
int full_house(int* dice, int n_dice, int* dice_counter) {
    int res = 0,
        triple_taken = 0,           /*have we had a three of a kind yet*/ 
        double_taken = 0,           /*have we had a twe of a kind yet*/
        i;

    roll_print_count(dice, n_dice, dice_counter);

    for (i = ones; i <= sixes; i++) {
        /*check if the have three of more of that roll and that we don't already have a three of a kind if false do the same for two*/
        if (*(dice_counter + i) >= 3 && !triple_taken) {
           triple_taken++; 
        } else if ((*dice_counter + i) >= 2 && !double_taken) {
            double_taken++;
        }

        /*if we have a triple and a pair it's a full house*/
        if (triple_taken && double_taken) {
            res = 25;
            break;
        }
    }

    printf("Score: %d\n", res);

    return res;
}

/*check for a straight of a specific size seq_size and return the score*/
int straight(int* dice, int n_dice, int* dice_counter, int seq_size) {
    int res = 0,
        i;

    roll_print_count(dice, n_dice, dice_counter);

    /*for all possible sequences check if we have that sequence*/
    for (i = 0; i <= 6 - seq_size; i++) {
        if (check_straight(dice_counter, i, seq_size)) {
            res = (seq_size - 1) * 10;
            break;
        }
    }

    printf("Score; %d\n", res);

    return res;
}

/*check a single sequence to see if it is a straight, return 1 if it is and 0 otherwise*/
int check_straight(int* dice_counter, int index, int seq_size) {
    int res = 1;

    /*check that we have atleast one of each roll in the sequence, if we don't res = 0 and break*/
    int i;
    for (i = index; i < index + seq_size - 1; i++) {
        if (!*(dice_counter + i)) {
            res = 0;
            break;
        }
    }

    return res;
}

/*sum the highest 5 rolls and return the sum*/
int highest_5(int* dice, int n_dice, int* dice_counter) {
    int res = 0,
        dice_left = 5,                              /*how many of the five spots have been filled*/
        i;
     
    roll_print_count(dice, n_dice, dice_counter);

    for (i = sixes; i >= ones; i--) {               /*go from six to one since that give the highest score*/
        if (*(dice_counter + i) >= dice_left) {     /*if we have more dice than spots left add the spots left times the dice roll to the result and break*/
            res += (i + 1) * dice_left;
            break;
        } else {                                    /*if we do not add all the dice of that roll to the result subtract the number of dice of that roll from the number of spots left*/
            res += (i + 1) * *(dice_counter + i);
            dice_left -= *(dice_counter + i);
        }
    }

    printf("Score; %d\n", res);

    return res;
}
