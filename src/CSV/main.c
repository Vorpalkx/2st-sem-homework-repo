#include "functions.h"
#include "parcer.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments!\n");
        return 2;
    }
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Opening the source file");
        return 1;
    }

    size_t capacity = 50;
    int* maxColumns = calloc(capacity, sizeof(int));
    if (maxColumns == NULL) {
        fclose(file);
        perror("Memory allocation error");
        return 3;
    }

    int numColumn = columnWidth(&maxColumns, &capacity, file);
    if (numColumn <= 0) {
        free(maxColumns);
        fclose(file);
        if (numColumn == 0) {
            fprintf(stderr, "No columns found or file is empty.\n");
            return 4;
        }
        return 3;
    }

    if (fprintTable(maxColumns, numColumn, file, argv[2]) != 0) {
        free(maxColumns);
        fclose(file);
        return 1;
    }

    free(maxColumns);
    fclose(file);
    return 0;
}
