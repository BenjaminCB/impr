/* Navn: Benjamin Clausen Bennetzen 
 * Mail: bbenne20@student.aau.dk
 * Gruppe: A306
 * Studieretning: Datalogi */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_OF_MATCHES 182
#define NUMBER_OF_TEAMS 14

typedef struct date {
    int day, month;
} Date;

typedef struct time {
    int hours, minutes;
} Time;

/* match struct which contains the following
 * Shortened version for the day of the week
 * struct for day, month and year
 * struct for hours and minutes
 * shortened name for the home team
 * the amount of goals that the home team got in the match
 * shortened name for the away team
 * the amount of goals that the away team got in the match
 * the amount of attendees at the match */
typedef struct match {
    char day[3];
    Date date;
    Time time;
    char home_team[3];
    int home_team_goals;
    char away_team[3];
    int away_team_goals;
    int attendees;
} Match;

/* team struct which has the following
 * shortened name for the team
 * total amount of points for the season
 * total amount of goals for the season
 * total amount of goals scored against them for the season */
typedef struct team {
    char name[3];
    int points, goals_scored, goals_scored_against;
} Team;

/* Singlylinked list struct which contains a pointer to a team struct and a pointer to the next node
 * This is used to chain collisions in my hash table*/
typedef struct list {
    Team* team;
    struct list* next;
} List;

/*prototype declarations*/
void read_stats(Match* matches, List* teams);
void print_team(Team* team);
void evaluate_match(Match* match, List* teams);
int hash(char* str);
Team* lookup(List* teams, char* team_name);
List* insert(List* last, char* team_name);
void print_results(List* teams); 
Team* hash_table_to_array(List* teams);
int compare_teams(const void* team1, const void* team2);

int main(void) {
    Match matches[NUMBER_OF_MATCHES];
    List teams[NUMBER_OF_TEAMS];
    int i;

    /*assign all the pointers for the next nodes to NULL
     * this is the indicator that there isn't a team in that node yet*/
    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        teams[i].next = NULL;
        /*teams[i].name[0] = '\0';*/
    }

    /*parse the input into my array of matches as well as teams into my hash table of teams*/
    read_stats(matches, teams);

    /*print the sorted results*/
    print_results(teams);

    return 0;
}

/* reads the input file and parses each line to a mactch struct in the array of matches
 * it also evaluates each match and fills out the hash table with teams */
void read_stats(Match* matches, List* teams) {
    /*open the file with data*/
    FILE* match_stats = fopen("kampe-2019-2020.txt", "r");
    int i;

    /*for every line in the data file parse the data to a match in the match array and then evaluete the newly parsed match*/
    for (i = 0; i < NUMBER_OF_MATCHES; i++) {
        fscanf(match_stats, "%s %d/%d %d.%d %s - %s %d - %d %d",
                (matches + i)->day,
                &(matches + i)->date.day, &(matches + i)->date.month,
                &(matches + i)->time.hours, &(matches + i)->time.minutes,
                (matches + i)->home_team, (matches + i)->away_team,
                &(matches + i)->home_team_goals, &(matches + i)->away_team_goals, 
                &(matches + i)->attendees); 
        evaluate_match((matches + i), teams);
    }
}

/* this function takes a team and prints the values in itwith padding and | in between each value
 * to simulate coloumns when printed ane after another */
void print_team(Team* team) {
    printf("%-7s|%7d|%7d|%7d|\n",
            team->name,
            team->points,
            team->goals_scored,
            team->goals_scored_against);
}

/* this function evaluates a match. Meaning it takes a the results from the match and adds them to the appropriate team
 * To do this at takes a pointer to the match and the hash table of teams */
void evaluate_match(Match* match, List* teams) {
    /*look up the teams from the match in the hash table*/
    Team* home_team = lookup(teams, match->home_team);
    Team* away_team = lookup(teams, match->away_team);

    /*add the goal values to the home- and away_team*/
    home_team->goals_scored += match->home_team_goals;
    home_team->goals_scored_against += match->away_team_goals;
    
    away_team->goals_scored += match->away_team_goals;
    away_team->goals_scored_against += match->home_team_goals;

    /* compare goals from the match, and give the wining team 3 points
     * or both teams 1 point if they each scored an equal amount of goals */
    if (match->home_team_goals < match->away_team_goals) {
        away_team->points += 3;
    } else if (match->home_team_goals > match->away_team_goals) {
        home_team->points += 3;
    } else {
        away_team->points++;
        home_team->points++;
    }
}

/* this function looks for a specific team in the hash table and if it isn't in the table it will put it in
 * the function returns a pointer to the team that being looked up */
Team* lookup(List* teams, char* team_name) {
    /* get the index that by hashing the team name. 
     * Then create a list pointer to the first node at that index in the hash table */
    int index = hash(team_name);
    List* node = (teams + index);

    /*go throuh the linked list until we reach the last node*/
    while (node->next != NULL) {
        /*if the team at this node is the team that is being looked for return it. Otherwise go to the next node.*/
        if (!strcmp(node->team->name, team_name)) {
            return node->team;
        } else {
            node = node->next;
        }
    }

    /*if the team is not in the list it must be a new team therefore the team is inserted at the tail and a new tail is created*/
    node->next = insert(node, team_name);
    return node->team;
}

/* This function takes a string as an input and sum the ascii values for all the chars in the string
 * it then modulos with number of teams and return that value */
int hash(char* str) {
    int sum = 0,
        i = 0;
    while (str[i] != '\0') {
        sum += (int) str[i];
        i++;
    }
    return sum % NUMBER_OF_TEAMS;
}

/* this function creates a team at the tail of a linked list and then creates a new tail
 * takes a pointer to the tail and a team name as the parameters
 * return a pointer to the now tail */
List* insert(List* last, char* team_name) {
    /* allocate memory to new node 
     * allocate memory to the team that the tail is pointing at */
    last->next = (List*) malloc(sizeof(List));
    last->team = (Team*) malloc(sizeof(Team));

    /*fill in default team values along with the team name*/
    strcpy(last->team->name, team_name);
    last->team->goals_scored = 0;
    last->team->goals_scored_against = 0;
    last->team->points = 0;

    /*the new tails next value should point to NULL so that we know it does not have a team*/
    last->next->next = NULL;

    return last->next;
}

/*prints the ordered results of all the teams*/
void print_results(List* teams) {
    int i;
    /*convert the hash table to an array*/
    Team* team_array = hash_table_to_array(teams);

    /*sort the now array teams*/
    qsort(team_array, NUMBER_OF_TEAMS, sizeof(Team), compare_teams);

    /*print a header*/
    printf("%-8s%-8s%-8s%-8s\n", "Team", "Points", "Goals", "Against");
    for (i = 0; i < 32; i++) {
        printf("-");
    }
    printf("\n");

    /*print all the teams*/
    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        print_team(team_array + i);
    }

    /*free the team array*/
    free(team_array);
}

/*takes the hash table as a parameter and return a pointer to an array with all the teams*/
Team* hash_table_to_array(List* teams) {
    /*allocate memory to the array of teams*/
    Team* team_array = (Team*) malloc(sizeof(Team) * NUMBER_OF_TEAMS);
    int j = 0,
        i;

    /*go throuh all indencies of the hash table*/
    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        List* node = teams + i;
        /*if there are teams in this list go through it and add every team to the array*/
        while(node->next != NULL) {
            team_array[j] = *(node->team);
            j++;
            node = node->next;
        }
    }

    return team_array;
}

/* this function compares two teams and return -1 if the first parameter should come first and 1 if the socend parameter sholud come first
 * it takes two constant void pointers as inputs */
int compare_teams(const void* team1, const void* team2) {
    /*type cast t1 an t2 to constant team pointers */
    const Team* t1 = (const Team*) team1;
    const Team* t2 = (const Team*) team2;
    
    /* first compare points if they are equal compare goal difference */
    if (t1->points < t2->points) {
        return 1; 
    } else if (t1->points > t2->points) {
        return -1;
    } else if (t1->goals_scored - t1->goals_scored_against < t2->goals_scored - t2->goals_scored_against) {
        return 1;
    } else {
        return -1;
    }
}
