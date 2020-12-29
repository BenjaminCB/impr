#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void bsort(void *base, size_t n, size_t size, int(*compar)(const void *, const void *));

int main(void) {


    return 0;
}

void bsort(void *base, size_t n, size_t size, int(*compar)(const void *, const void *)) {
    int   i, j;

    for (i = base; i < size * (n - 1); i += size){
        for (j = size * (n - 1); j > i; j -= size)
            if (compar((base + j -1), (base + j))) {
                void* temp;
                memcpy(temp, base + j - 1, size);
                memcpy(base + j - 1, base + j, size);
                memcpy(base + j, temp, size);
            }
    }
}