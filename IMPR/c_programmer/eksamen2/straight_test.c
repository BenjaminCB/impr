#include <stdlib.h>
#include <stdio.h>

int straight(int* dice, int n_dice, int seq_size);
int check_straight(int* dice, int index, int seq_size);

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int arr2[] = {2, 3, 4, 5, 6};
    int arr3[] = {1, 1, 1, 3, 1, 2, 3, 4, 4}; 
    straight(arr, 5, 4);
    straight(arr2, 5, 4);
    straight(arr, 5, 5);
    straight(arr2, 5, 5);
    straight(arr3, 9, 4);
    straight(arr3, 9, 5);
    return 0;
}

int straight(int* dice, int n_dice, int seq_size) {
    int res = 0;

    int i;
    for (i = 0; i <= n_dice - seq_size; i++) {
        if (check_straight(dice, i, seq_size)) {
            res = (seq_size - 1) * 10;
            break;
        }
    }

    printf("Score; %d\n", res);

    return res;
}

int check_straight(int* dice, int index, int seq_size) {
    int res = 1;

    int i;
    for (i = index; i < index + seq_size - 1; i++) {
        if (*(dice + i) != *(dice + i + 1) - 1) {
            res = 0;
            break;
        }
    }

    return res;
}
