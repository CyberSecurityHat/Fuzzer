#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 100

char generateRandomChar() {
    return ' ' + (rand());
}

void fuzzFuction(char (*functionToTest)(char*), int numTests) {
    srand(time(0));

    for (int i = 0; i < numTests; i++) {
        char testString[MAX_LENGTH + 1];
        for (int j = 0; j < MAX_LENGTH; j++) {
            testString[j] = generateRandomChar();
        }
        testString[MAX_LENGTH] = '\0';

        printf("TestCase %d = input: %s, output: %c\n", i, testString, functionToTest(testString));
    }
}

char sampleTestFunction(char* input) {
    return input[0];
}

int main() {
    fuzzFuction(sampleTestFunction, 1000);
    return 0;
}
