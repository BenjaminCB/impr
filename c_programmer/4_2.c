#include <stdio.h>

int main(void){
    int n, m, k,
	sum = 0;
    scanf("%d %d %d", &n, &m, &k);

    int i;
    for(i = n; i <= m; i++){
	if (i % k == 0) {
	   sum += i; 
	}
    }
    printf("%d", sum);
    return 0;
}
