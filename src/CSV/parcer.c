#include "parcer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int columnWidth(int** maxColumns, size_t* currentCapacity, FILE* file)
{
    int numColumn = 0;
    char* line = NULL;
    size_t lenBuf = 0;

    while (getline(&line, &lenBuf, file) != -1) {
        line[strcspn(line, "\n")] = 0;

        char* running = line;
        char* token;
        for (size_t i = 0; (token = strsep(&running, ",")) != NULL; i++) {

            if (i >= *currentCapacity) {
                size_t newCapacity = (*currentCapacity == 0) ? 50 : *currentCapacity * 2;

                int* temp = realloc(*maxColumns, newCapacity * sizeof(int));
                if (temp == NULL) {
                    perror("Memory reallocation error");
                    free(line);
                    return -1;
                }

                for (size_t j = *currentCapacity; j < newCapacity; j++) {
                    temp[j] = 0;
                }

                *maxColumns = temp;
                *currentCapacity = newCapacity;
            }
            int len = (int)strlen(token);
            if (len > (*maxColumns)[i]) {
                (*maxColumns)[i] = len;
            }
            if ((int)i > numColumn) {
                numColumn = (int)i;
            }
        }
    }
    free(line);
    rewind(file);
    return numColumn;
}
