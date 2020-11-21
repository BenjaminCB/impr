/*De generelle regler for udarbejdelse og aflevering af opgaven er beskrevet i Rammer for eksamensopgaver i Imperativ Programmering.

Denne opgave er baseret på en fil med resultaterne fra de første 26 runder af den danske superliga fra 2019-2020. Navnet på din inputfil skal være kampe-2019-2020.txt. Hver linje i filen er et kampresultat, eksempelvis

      Fre     12/07 19.00     FCM - EFB     1 - 0     7310

Denne linje betyder at FCM (FC Midtjylland) har spillet på hjemmebane mod EFB (Esbjerg FB) fredag 12. juli kl. 19.00, kampen blev overværet af 7310 tilskuere, FCM scorede et mål og EFB scorede ikke i kampen.

I opgaven skal samtlige kampe indlæses i et array af structs (kamp-arrayet). Hvis du ønsker det kan du antage at der netop er 182 kampe i turneringen. Det benyttede struct skal opbevare oplysninger om kampens ugedag, dato (uden årstal), klokkeslæt, de to hold, kampens resultat og tilskuertal.

Opgaven går nu ud på at gennemløbe alle kampresultater med henblik på at lave et array af hold (hold-arrayet), hvor et hold er en struct. Hold structen skal indholde holdnavn, point, antal mål scoret af holdet og antal mål score mod holdet. Hvis du ønsker det kan du antage at der netop er 14 hold som spiller i turneringen. Hold-arrayet kan opfattes som et associativt array, der associererer holdnavnet med et hold struct, og derfor kan dele af opgaven om associative arrays bruges i denne opgave. Hvis du ønsker det kan du placere holdene på faste, forudprogrammerede pladser i hold-arrayet.

Hold-arrayet skal nu sorteres, så vi kan finde stillingen i turneringen efter 26 runder. I denne opgave sorteres primært efter point og sekundært efter målforskel. En vundet kamp giver 3 point, en uafgjort kamp giver 1 point, og en tabt kamp giver ingen point. Udskriv stillingen af turneringen på standard output med én linje per hold i følgende format:

       Holdnavn Point Mål-af-hold Mål-mod-hold

Gør dig umage med at udskrive stillingen pænt, med fire lige brede søjler der er indrykket på en naturlig og overskuelig måde.*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUMBER_OF_MATCHES 182
#define NUMBER_OF_TEAMS 14

typedef enum weekday {
    Manday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
} Weekday;

typedef struct date {
    int day, month;
} Date;

typedef struct time {
    int hours, minutes;
} Time;

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

typedef struct team {
    char name[3];
    int points, goals_scored, goals_scored_against;
} Team;

typedef struct list {
    Team* team;
    struct list* next;
} List;

void read_stats(Match* matches, List* teams);
void print_match(Match* match);
void print_team(Team* team, int h);
void evaluate_match(Match* match, List* teams);
Team* lookup(List* teams, char* team_name);
int hash(char* str);
List* insert(List* last, char* team_name);

int main(void) {
    Match matches[NUMBER_OF_MATCHES];
    List teams[NUMBER_OF_TEAMS];
    int i;

    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        teams[i].next = NULL;
    }

    read_stats(matches, teams);

    for (i = 0; i < NUMBER_OF_TEAMS; i++) {
        int h = 0;
        List* j = (teams + i);
        if (j == NULL) printf("yep\n");
        while (j != NULL) {
            print_team(j->team, h);
            j = j->next;
            h++;
        }
        /*if (j->team != NULL) {
            print_team(j->team, h);
        }*/
    }

    /*int h = 0;
    while(teams[2] != NULL) {
        print_team(teams[2]->team, h);
        teams[2] = teams[2]->next;
        h++;
    }*/

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

void print_team(Team* team, int h) {
    printf("%s %d %d %d %d\n",
            team->name,
            team->points,
            team->goals_scored,
            team->goals_scored_against,
            h);
}

void evaluate_match(Match* match, List* teams) {
    Team* home_team = lookup(teams, match->home_team);
    Team* away_team = lookup(teams, match->away_team);

    home_team->goals_scored += match->home_team_goals;
    home_team->goals_scored_against += match->away_team_goals;
    
    away_team->goals_scored += match->away_team_goals;
    away_team->goals_scored_against += match->home_team_goals;

    if (home_team->goals_scored < away_team->goals_scored) {
        away_team->points += 3;
    } else if (home_team->goals_scored > away_team->goals_scored) {
        home_team->points += 3;
    } else {
        away_team->points++;
        home_team->points++;
    }
}

Team* lookup(List* teams, char* team_name) {
    int index = hash(team_name);
    List* chain = (teams + index);

    while (chain->next != NULL) {
        if (!strcmp((chain)->team->name, team_name)) {
            return (chain)->team;
        } else {
            (chain) = (chain)->next;
        }
    }

    chain->next = insert(chain, team_name);
    return chain->next->team;
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
    last = (List*) malloc(sizeof(List));
    (last)->team = (Team*) malloc(sizeof(Team));

    strcpy((last)->team->name, team_name);
    (last)->team->goals_scored = 0;
    (last)->team->goals_scored_against = 0;
    (last)->team->points = 0;
    (last)->next = NULL;

    /*next_node->next = NULL;
    next_node->team = NULL;*/

    return (last);
}
