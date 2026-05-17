#include <stdio.h>
#include <stdbool.h>

struct letterWithNeighbours
{
    __int8_t letter : 5;
    __int32_t neighbourMask: 26;
};

struct letterWithNeighbours *qwerty;

__int8_t asciiToLetter(unsigned char symbol) {
    if (symbol >= 'a' && symbol <= 'z') return symbol - 'a' + 1;
    if (symbol >= 'A' && symbol <= 'Z') return symbol - 'A' + 1;
    return -1;
}

__int32_t asciiToMask(unsigned char symbol) {
    if (symbol >= 'a' && symbol <= 'z') return 1 << (symbol - 'a');
    if (symbol >= 'A' && symbol <= 'Z') return 1 << (symbol - 'A');
    return -1;
}

bool isCorrect(char *word, struct letterWithNeighbours *data) {
    while (word != '\0') {
        return false;
    }
    return true;
}

int main() {
    char word1[] = "swqa";
    char word2[] = 'qswa';

    return 0;
}