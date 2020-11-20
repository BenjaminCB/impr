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
    Weekday day;
    Date date;
    Time time;
    char home_team[3];
    int home_team_goals;
    char away_team[3];
    int away_team_goals;
    int attendes;
} Match;

int main(void) {

    return 0;
}
