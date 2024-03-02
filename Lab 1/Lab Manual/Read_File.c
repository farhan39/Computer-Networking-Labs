#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile, *outputFile;
    char filenameInput[] = "input.txt"; // Change to your input file name
    char filenameOutput[] = "output.txt"; // Change to your desired output file name
    char ch;

    // Open the input file in read mode
    inputFile = fopen(filenameInput, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Open the output file in write mode
    outputFile = fopen(filenameOutput, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile); // Close the input file before exiting
        return 1;
    }

    // Read character by character from the input file and write to the output file
    while ((ch = fgetc(inputFile)) != EOF) {
        fputc(ch, outputFile);
    }

    // Close both files
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}
