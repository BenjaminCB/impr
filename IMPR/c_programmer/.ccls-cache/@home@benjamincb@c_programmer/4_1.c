#include <stdio.h>
int main(void){
   int i, power = 1;

   for(i = 0; i <= 10; i++)
      printf("%5d", power *= 2);
   printf("\n");

   return 0;
}
