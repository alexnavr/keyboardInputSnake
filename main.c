#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 256

int32_t neighbourBitMask[ALPHABET_SIZE] = {0};

int8_t asciiToNumber(unsigned char symbol) {
    if (symbol >= 'a' && symbol <= 'z') return symbol - 'a';
    if (symbol >= 'A' && symbol <= 'Z') return symbol - 'A';
    return -1;
}

int32_t asciiToMask(unsigned char symbol) {
    if (symbol >= 'a' && symbol <= 'z') return 1 << (symbol - 'a');
    if (symbol >= 'A' && symbol <= 'Z') return 1 << (symbol - 'A');
    return -1;
}

bool isCorrect(char *word) {
    bool prevWasRepeat = false;
    for (;*(word+1) != '\0'; word++) {
        char nextChar = *(word + 1);
        if (*word == nextChar) {
            if (prevWasRepeat) return false;
            prevWasRepeat = true;
            continue;
        } else {
            prevWasRepeat = false;
        }

        int32_t nextMask = asciiToMask(nextChar);
        if (nextMask == -1) return false;

        int8_t curIdx = asciiToNumber(*word);
        if (curIdx == -1) return false;

        int32_t allowedMask = neighbourBitMask[curIdx];
        if ((nextMask & allowedMask) == 0) {
            return false;
        } 
    }
    return true;
}

int main(int argc, char* argv[]) {
    FILE *fAdjacency, *fDictionary;
    int counter = 0;
    char buffer[MAX_WORD_LEN];

    fAdjacency = fopen("data/qwerty.txt", "r");

    if (fAdjacency == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fAdjacency)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        size_t size = strlen(buffer);

        if (size < 3) {
            fprintf(stderr ,"Expected format: 'x abc...' where x is a letter and abc... are neighbours");
            return 2;
        }

        int32_t neighbourMask = 0;
        int8_t letterIdx = asciiToNumber(buffer[0]);

        for (int16_t i = 2; i < size; i++) {
            int32_t candidate = asciiToMask(buffer[i]);
            if (candidate == -1) {
                fprintf(stderr ,"Unexpected symbol in adjacency file");
                return 2;
            }
            neighbourMask |= candidate;
        }
        
        neighbourBitMask[letterIdx] = neighbourMask;
    }

    fclose(fAdjacency);

    
    if (argc > 1) {
        fDictionary = fopen(argv[1], "r");
    } else {
        fDictionary = fopen("data/dictionary.txt", "r");
    }

    if (fDictionary == NULL) {
        perror("Error opening dictionary.txt");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), fDictionary)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        if (buffer[0] == '\0') continue;
        bool res = isCorrect(buffer);
        if (res) counter++;
    }

    fclose(fDictionary);

    printf("result: %d\n", counter);

    return 0;
}