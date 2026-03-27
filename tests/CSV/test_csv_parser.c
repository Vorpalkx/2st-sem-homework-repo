#include "parser.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function for creating temporary files
FILE* createTestCsv(const char* name, const char* content)
{
    errno = 0;
    FILE* f = fopen(name, "w+");

    if (f == NULL) {
        perror("Failed to open test file");
        return NULL;
    }

    if (content != NULL && *content != '\0') {
        if (fprintf(f, "%s", content) < 0) {
            perror("Failed to write to test file");
            fclose(f);
            return NULL;
        }
    }

    if (rewind(f), errno != 0) {
        perror("Failed to rewind test file");
        fclose(f);
        return NULL;
    }

    return f;
}

// Test 1: Regular File (Checking Basic Logic and Capacity Expansion)
void testNormalCsv()
{
    const char* filename = "test_normal.csv";
    FILE* f = createTestCsv(filename, "Name,Age\nIvan,25\nAlexander,30");
    assert(f != NULL);

    size_t capacity = 1;
    int* maxCols = calloc(capacity, sizeof(int));
    assert(maxCols != NULL);

    int numCols = columnWidth(&maxCols, &capacity, f);

    assert(numCols == 2);
    assert(maxCols[0] == 9);
    assert(maxCols[1] == 3);
    assert(capacity >= 2);

    free(maxCols);
    fclose(f);
    remove(filename);
    printf("[PASS] testNormalCsv\n");
}

// Test 2: Empty Fields and Extra Commas
void testEmptyFields()
{
    const char* filename = "test_empty.csv";
    // A line with an empty field in the middle and at the end
    FILE* f = createTestCsv(filename, "ID,,Note\n1,val,");
    assert(f != NULL);

    size_t capacity = 5;
    int* maxCols = calloc(capacity, sizeof(int));
    assert(maxCols != NULL);

    int numCols = columnWidth(&maxCols, &capacity, f);

    assert(numCols == 3);
    assert(maxCols[1] == 3);
    assert(maxCols[2] == 4);

    free(maxCols);
    fclose(f);
    remove(filename);
    printf("[PASS] testEmptyFields\n");
}

// Test 3: Single-Line File (Headers Only)
void testHeaderOnly()
{
    const char* filename = "test_header.csv";
    FILE* f = createTestCsv(filename, "Col1,Col2,Col3");
    assert(f != NULL);

    size_t capacity = 10;
    int* maxCols = calloc(capacity, sizeof(int));
    assert(maxCols != NULL);

    int numCols = columnWidth(&maxCols, &capacity, f);

    assert(numCols == 3);
    assert(maxCols[0] == 4);

    free(maxCols);
    fclose(f);
    remove(filename);
    printf("[PASS] testHeaderOnly\n");
}

// Test 4: "Ragged" CSV (the second row has more columns than the first)
void testJaggedCsv()
{
    const char* filename = "test_jagged.csv";
    FILE* f = createTestCsv(filename, "Col1,Col2\nVal1,Val2,Val3,Val4");
    assert(f != NULL);

    size_t capacity = 2;
    int* maxCols = calloc(capacity, sizeof(int));
    assert(maxCols != NULL);

    int numCols = columnWidth(&maxCols, &capacity, f);

    assert(numCols == 4);
    assert(maxCols[2] == 4);
    assert(maxCols[3] == 4);

    free(maxCols);
    fclose(f);
    remove(filename);
    printf("[PASS] testJaggedCsv\n");
}

// Test 5: Very Long Lines (Testing Getline Limits)
void testLongLine()
{
    const char* filename = "test_long.csv";
    FILE* f = fopen(filename, "w+");
    assert(f != NULL);

    for (int i = 0; i < 1000; i++)
        fputc('A', f);
    fprintf(f, ",Short");
    rewind(f);

    size_t capacity = 5;
    int* maxCols = calloc(capacity, sizeof(int));
    assert(maxCols != NULL);

    int numCols = columnWidth(&maxCols, &capacity, f);

    assert(numCols == 2);
    assert(maxCols[0] == 1000);
    assert(maxCols[1] == 5);

    free(maxCols);
    fclose(f);
    remove(filename);
    printf("[PASS] testLongLine\n");
}

// Test 6: Empty file (no data at all)
void testZeroByteFile()
{
    const char* filename = "test_zero.csv";
    FILE* f = createTestCsv(filename, "");
    assert(f != NULL);

    size_t capacity = 5;
    int* maxCols = calloc(capacity, sizeof(int));
    assert(maxCols != NULL);

    int numCols = columnWidth(&maxCols, &capacity, f);

    assert(numCols == 0);

    free(maxCols);
    fclose(f);
    remove(filename);
    printf("[PASS] testZeroByteFile\n");
}

int main()
{
    printf("--- Running CSV Parser Tests ---\n");
    testNormalCsv();
    testEmptyFields();
    testHeaderOnly();
    testJaggedCsv();
    testLongLine();
    testZeroByteFile();
    printf("--- All tests passed! ---\n");
    return 0;
}
