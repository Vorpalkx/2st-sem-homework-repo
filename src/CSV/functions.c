#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printChars(char c, int n, FILE* out)
{
    while (n-- > 0)
        fputc(c, out);
}

void frameTitle(int* maxColumns, int numColumn, FILE* out)
{
    fputc('+', out);

    for (int i = 0; i < numColumn; i++) {
        printChars('=', maxColumns[i] + 2, out);
        fputc('+', out);
    }

    fputc('\n', out);
}

void frameRegular(int* maxColumns, int numColumn, FILE* out)
{
    fputc('+', out);

    for (int i = 0; i < numColumn; i++) {
        printChars('-', maxColumns[i] + 2, out);
        fputc('+', out);
    }

    fputc('\n', out);
}

void fprintField(int* maxColumns, FILE* out, char* line, int numLine, int numColumn)
{
    fputc('|', out);

    char* token;
    char* running = line;
    for (int i = 0; i < numColumn; i++) {
        token = strsep(&running, ",");
        if (token != NULL) {
            char* endfield;
            (void)strtod(token, &endfield);

            if (*endfield != '\0' || numLine == 0) {
                fprintf(out, " %-*s |", maxColumns[i], token);
            } else {
                fprintf(out, " %*s |", maxColumns[i], token);
            }
        } else {
            printChars(' ', maxColumns[i] + 2, out);
            fputc('|', out);
        }
    }
    fputc('\n', out);
}

int fprintTable(int* maxColumns, int numColumn, FILE* file, const char* filename)
{
    FILE* out = fopen(filename, "w");
    if (out == NULL) {
        perror("Opening the output file");
        return 1;
    }

    frameTitle(maxColumns, numColumn, out);

    char* line = NULL;
    size_t lenBuf = 0;
    for (int i = 0; getline(&line, &lenBuf, file) != -1; i++) {
        line[strcspn(line, "\n")] = 0;
        fprintField(maxColumns, out, line, i, numColumn);

        if (i == 0) {
            frameTitle(maxColumns, numColumn, out);
        } else {
            frameRegular(maxColumns, numColumn, out);
        }
    }

    free(line);
    fclose(out);
    return 0;
}
