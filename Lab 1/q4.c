//Farhan Bukhari------BCS-5F-----21L-5247
//Q4

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const int BUFFER_SIZE = 1024;

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void invertWord(char* word) {
    int length = strlen(word);
    for (int i = 0; i < length / 2; i++) {
        char temp = word[i];
        word[i] = word[length - i - 1];
        word[length - i - 1] = temp;
    }
}

int main() {
    int inputFd = open("input_file.txt", O_RDONLY);
    if (inputFd == -1) {
        perror("Failed to open input file.");
        return 1;
    }

    int outputFd = open("invertedwords.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outputFd == -1) {
        perror("Failed to create output file.");
        close(inputFd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    int bytesRead;
    char* wordStart = NULL;
    bool insideWord = false;

    while ((bytesRead = read(inputFd, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            if (!insideWord && isalpha(buffer[i])) {
                wordStart = &buffer[i];
                insideWord = true;
            } else if (insideWord && !isalpha(buffer[i])) {
                char* wordEnd = &buffer[i];
                *wordEnd = '\0';

                if (strpbrk(wordStart, "aeiouAEIOU") != NULL) {
                    invertWord(wordStart);
                }

                int wordLength = strlen(wordStart);
                write(outputFd, wordStart, wordLength);
                write(outputFd, " ", 1);

                insideWord = false;
            }
        }
    }

    close(inputFd);
    close(outputFd);

    return 0;
}