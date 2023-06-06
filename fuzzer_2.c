#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_LENGTH 1000

char generateRandomChar() {
    return (char)(rand() % 128);
}

void fuzzFunction (char (*functionToTest)(char*), int numTests) {
    srand(time(0));
    int failures = 0;
    clock_t start = clock();

    for (int i = 0; i < numTests; i++) {
        int length = rand() % MAX_LENGTH + 1;
        char* testString = (char*)malloc((length + 1) * sizeof(char));
        for (int j = 0; j < length; j++) {
            testString[j] = generateRandomChar();
        }
        testString[length] = '\0';

        char output  = functionToTest(testString);
        char expectedOutput = islower(testString[0]) ? toupper(testString[0]) : testString[0];
        if (output != expectedOutput) {
            failures++;
            printf("----------------------------------------------------------------------------------------\n");
            printf("Failure. %d\n", failures);
            printf("input length: %d\n", length);
            printf("input: %s\n", testString);
            printf("output: %c\n", output);
            printf("expected: %c\n", expectedOutput);
            printf("----------------------------------------------------------------------------------------\n");
            printf("\n");
        }
        free(testString);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Fuzzing complete. Total failures: %d out of %d tests. Time taken %.2f seconds.\n", failures, numTests, time_spent);
}

char sampleTestFuncion(char* input) {
    return input[0];
}

int main() {
    fuzzFunction(sampleTestFuncion, 1000);
    return 0;
}