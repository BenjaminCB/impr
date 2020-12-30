#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct matrix {
    int col;
    int row;
    double num;
} Matrix;

int main(void) {
    FILE* input = fopen("./13_4.txt", "r");
    FILE* output = fopen("./13_4out.txt", "w");
    int cols, rows, i, j;
    Matrix* mp;

    fscanf(input, "%d %d\n", &rows, &cols);

    mp = (Matrix*) malloc(cols * rows * sizeof(Matrix));
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            char buffer[100];
            int h = 0;
            double num;
            for (;;) {
                char c = fgetc(input);
                if (c != ' ' && c != '\n' && !feof(input)) {
                    buffer[h++] = c;
                } else {
                    buffer[h] = '\0';
                    sscanf(buffer, "%lf", &num);
                    break;
                }
            } 

            (mp + cols * i + j)->col = j + 1;
            (mp + cols * i + j)->row = i + 1;
            (mp + cols * i + j)->num = num;
        }
    }

    fprintf(output, "%d %d\n", rows, cols);

    for (i = 0; i < cols * rows; i++) {
        fprintf(output, "%d %d %f\n", (mp + i)->row, (mp + i)->col, (mp + i)->num);
    }

    return 0;
}