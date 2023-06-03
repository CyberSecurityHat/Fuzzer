#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_LENGTH 100

char generateRandomChar() {
    return (char)(rand() % 128);
}

void fuzzFunction(char (*functionToTest)(char*), int numTests) {
    srand(time(0));
    int failures = 0;

    for (int i = 0; i < numTests; i++) {
        char testString[MAX_LENGTH + 1];
        for (int j = 0; j < MAX_LENGTH; j++) {
            testString[j] = generateRandomChar();
        }
        testString[MAX_LENGTH] = '\0';

        char output = functionToTest(testString);
        char expectedOutput = islower(testString[0]) ? toupper(testString[0]) : testString[0];
        if (output != expectedOutput) {
            failures++;
            printf("Failure %d: input: %s, output: %c, expected: %c\n", failures, testString, output, expectedOutput);
        }
    }

    printf("Fuzzing complete. Total failures: %d out of %d tests.\n", failures, numTests);
}

char sampleTestFunction(char* input) {
    return input[0];
}

int main() {
    fuzzFunction(sampleTestFunction, 1000);
    return 0;
}
