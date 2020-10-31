#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime(int i);
int proof(int n);
int multi_proof(int n, int m);

int main(void) {
    printf("%d\n", multi_proof(7,100)); 
    return 0;
}

/* Return if i is a prime number. 
   It is assumed as a precondition that the parameter i is non-negative */
int is_prime(int i){
   assert(i >= 0);

   if (i == 1) 
     return 0;
   else if (i == 2) 
     return 1;
   else if (i % 2 == 0)
     return 0;
   else{
     int k, limit;
     limit = (int)(ceil(sqrt(i)));
     for (k = 3; k <= limit; k += 2)
        if (i % k == 0)
           return 0;
     return 1;
   }
}

int proof(int n) {
    int res = 0;
    int i = 1;
    while (n - i > 0) {
        if (is_prime(n - i) && is_prime(i) && (n - i) + i == n) {
            res = 1;
        }
        i++;
    }
    return res;
}

int multi_proof(int n, int m) {
    int res = 1;
    for (int i = n; i <= m; i++) {
        if(!proof(i)) {
            res = 0;
        }
    }
    return res;
}
