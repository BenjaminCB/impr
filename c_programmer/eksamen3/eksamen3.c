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

typedef struct match {
    char day[3];                /*Shortened version for the day of the week*/
    Date date;                  /*struct for day, month and year*/
    Time time;                  /*struct for hours and minutes*/
    char home_team[3];          /*shortened name for the home team*/
    int home_team_goals;        /*the amount of goals that the home team got in the match*/
    char away_team[3];          /*shortened name for the away team*/
    int away_team_goals;        /*the amount of goals that the away team got in the match*/
    int attendees;              /*the amount of attendees at the match*/
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
void print_match(Match* match);
void print_team(Team* team);
void evaluate_match(Match* match, List* teams);
/*Team* lookup(Team* teams, char* team_name);*/
int hash(char* str);
Team* lookup(List* teams, char* team_name);
List* insert(List* last, char* team_name);
void print_results(List* teams); 
Team* hash_table_to_array(List* teams);
int compare_teams(const void* team1, const void* team2);

int main(void) {
    Match matches[NUMBER_OF_MATCHES];
    /*Team teams[NUMBER_OF_TEAMS];*/
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

    /*for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        [>int h = 0;
        List* j = (teams + i);
        if (j == NULL) printf("yep\n");
        while (j != NULL) {
            print_team(j->team, h);
            j = j->next;
            h++;
        }
        [>if (j->team != NULL) {
            print_team(j->team, h);
        }<]<]
        print_team((teams + i));
    }*/

    /*print the sorted results*/
    print_results(teams);

    return 0;
}

void read_stats(Match* matches, List* teams) {
    FILE* match_stats = fopen("kampe-2019-2020.txt", "r");
    int i;
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

void print_match(Match* match) {
    printf("%s %d/%d %d.%d %s - %s %d - %d %d\n",
            match->day,
            match->date.day, match->date.month,
            match->time.hours, match->time.minutes,
            match->home_team, match->away_team,
            match->home_team_goals, match->away_team_goals, 
            match->attendees);
}

void print_team(Team* team) {
    printf("%-7s|%7d|%7d|%7d|\n",
            team->name,
            team->points,
            team->goals_scored,
            team->goals_scored_against);
}

void evaluate_match(Match* match, List* teams) {
    Team* home_team = lookup(teams, match->home_team);
    Team* away_team = lookup(teams, match->away_team);

    home_team->goals_scored += match->home_team_goals;
    home_team->goals_scored_against += match->away_team_goals;
    
    away_team->goals_scored += match->away_team_goals;
    away_team->goals_scored_against += match->home_team_goals;

    if (match->home_team_goals < match->away_team_goals) {
        away_team->points += 3;
    } else if (match->home_team_goals > match->away_team_goals) {
        home_team->points += 3;
    } else {
        away_team->points++;
        home_team->points++;
    }
}

/*Team* lookup(Team* teams, char* team_name) {
    int index = hash(team_name);

    while (*((teams + index)->name) != '\0') {
        if (!strcmp((teams + index)->name, team_name)) {
            return (teams + index);
        } else {
            index = (index + 1) % NUMBER_OF_TEAMS;
        }
    }

    strcpy((teams + index)->name, team_name);
    (teams + index)->goals_scored = 0;
    (teams + index)->goals_scored_against = 0;
    (teams + index)->points = 0;
    return (teams + index);
}*/

Team* lookup(List* teams, char* team_name) {
    int index = hash(team_name);
    List* chain = (teams + index);

    while (chain->next != NULL) {
        if (!strcmp(chain->team->name, team_name)) {
            return chain->team;
        } else {
            chain = chain->next;
        }
    }
    chain->next = insert(chain, team_name);
    return chain->team;
}

int hash(char* str) {
    int sum = 0,
        i = 0;
    while (str[i] != '\0') {
        sum += (int) str[i];
        i++;
    }
    return sum % NUMBER_OF_TEAMS;
}

List* insert(List* last, char* team_name) {
    /*List* next_node = (List*) malloc(sizeof(List));
    chain->next = next_node;*/
    last->next = (List*) malloc(sizeof(List));
    last->team = (Team*) malloc(sizeof(Team));

    strcpy(last->team->name, team_name);
    last->team->goals_scored = 0;
    last->team->goals_scored_against = 0;
    last->team->points = 0;
    last->next->next = NULL;

    /*next_node->next = NULL;
    next_node->team = NULL;*/

    return last->next;
}

void print_results(List* teams) {
    int i;
    Team* team_array = hash_table_to_array(teams);
    qsort(team_array, NUMBER_OF_TEAMS, sizeof(Team), compare_teams);
    printf("%-8s%-8s%-8s%-8s\n", "Team:", "Points;", "Goals:", "Against:");
    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        print_team(team_array + i);
    }

    free(team_array);
}

Team* hash_table_to_array(List* teams) {
    Team* team_array = (Team*) malloc(sizeof(Team) * NUMBER_OF_TEAMS);
    int j = 0,
        i;
    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        List* list_pointer = teams + i;
        while(list_pointer->next != NULL) {
            team_array[j] = *(list_pointer->team);
            j++;
            list_pointer = list_pointer->next;
        }
    }
    return team_array;
}

int compare_teams(const void* team1, const void* team2) {
    const Team* t1 = (const Team*) team1;
    const Team* t2 = (const Team*) team2;
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
