#include "functions.h"
#include "parcer.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr,"Incorrect number of arguments!\n");
        return 2;
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Opening the source file");
        return 1;
    }

    int capacity = 50;
    int *maxColumns = calloc(capacity, sizeof(int));
    if (maxColumns == NULL) {
        fprintf(stderr, "Memory allocation error");
        return 3;
    }

    int numColumn = columnWidth(&maxColumns, &capacity, file);

    fprintTable(maxColumns, numColumn, file, argv[2]); 

    free(maxColumns);
    fclose(file);
    return 0;
}
