#include <stdio.h>

int main () {
   char str[50];
   char a;
   double b;
   int c;

   printf("Enter a string : ");
   gets(str);
   c = sscanf(str, " %c %lf", &a, &b);

   if (c == 2) {
       printf("two input %c, %lf", a, b);
   } else if (c == 1) {
       printf("one input");
   } else {
       printf("no inputs");
   }

   return(0);
}
