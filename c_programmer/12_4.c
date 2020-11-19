struct card {
    int col, val, joker;
};
typedef struct card card;

int cmpfunc(const void* a, const void* b);

int main(void) {
    card cards[55];
    int i, j, h = 0;
    for (i = 1; i <= 13; i++) {
        for (j = 1; j <= 4; j++) {
            cards[h] = {i, j, 0};
            h++;
        }
    }

    return 0;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
