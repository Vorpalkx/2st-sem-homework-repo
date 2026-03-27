#include "parcer.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int columnWidth(int **maxColumns, int *currentCapacity, FILE *file) {
    int numColumn = 0;
    char *line = NULL;
    size_t len_buf = 0;

    while (getline(&line, &len_buf, file) != -1) {
        line[strcspn(line, "\n")] = 0;

        char *running = line;
        char *token;
        for (int i = 0; (token = strsep(&running, ",")) != NULL; i++) {

            if (i >= *currentCapacity) {
                int newCapacity = *currentCapacity * 2;
                int *temp = realloc(*maxColumns, newCapacity * sizeof(int));
                memset(temp + *currentCapacity, 0, (*currentCapacity) * sizeof(int));

                *maxColumns = temp;
                *currentCapacity = newCapacity;
            }
            int len = strlen(token);
            if (len > (*maxColumns)[i]) {
                (*maxColumns)[i] = len;
            }
            if (i > numColumn) {
                numColumn++;
            }
        }
    }
    free(line);
    rewind(file);
    return numColumn;
}
