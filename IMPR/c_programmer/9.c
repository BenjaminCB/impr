/* Write a program that takes the length and width of a rectangular yard and the 
length and width of a rectangular house situated in the yard. Your program 
should compute the time required to cut the grass at the rate of two square 
feet a second.*/

#include <stdio.h>
#include <stdlib.h>

#define CUTTING_RATE 2
int houseX, houseY, yardX, yardY;

int main(void) {
    scanf(" %d %d %d %d", &houseX, &houseY, &yardX, &yardY);
    printf("%d", (houseX * houseY - yardX * yardY) / CUTTING_RATE);

    return 0;
}