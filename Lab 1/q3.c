//Farhan Bukhari------BCS-5F-----21L-5247
//Q3

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

const int BUFFER_SIZE = 1024;

bool isNonAlphabetWord(const char* word) {
    for (int i = 0; i < strlen(word); i++) {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) {
            return false;
        }
    }
    return true;
}

int main() {
    int inputFd = open("input_file.txt", O_RDONLY);
    if (inputFd == -1) {
        perror("Failed to open input file.");
        return 1;
    }

    int outputFd = open("nonalphabetwords.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
            if (!insideWord && !isalpha(buffer[i])) {
                wordStart = &buffer[i];
                insideWord = true;
            } else if (insideWord && isalpha(buffer[i])) {
                char* wordEnd = &buffer[i];
                *wordEnd = '\0';

                if (isNonAlphabetWord(wordStart)) {
                    int wordLength = wordEnd - wordStart;
                    write(outputFd, wordStart, wordLength);
                    write(outputFd, "\n", 1);
                }

                insideWord = false;
            }
        }
    }

    close(inputFd);
    close(outputFd);

    return 0;
}