#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encoding.h"
#include "decoding.h"

#define BUFFER_SIZE 1000


int main() {
    int input;
    int offset = 99;

    printf("Choose an option: Encode (1) or Decode(2): ");
    scanf("%d", &input);

    char originalFile[BUFFER_SIZE];
    char encodedFile[BUFFER_SIZE] = "encoded.png";

    printf("What is the original file? (ex: picture.png): ");
    scanf("%c");
    if (fgets(originalFile, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strlen(originalFile);
        if (len > 0 && originalFile[len - 1] == '\n') {
            originalFile[len - 1] = '\0';
        }
    }
    else {
        printf("Error reading original file.\n");
    }

    char message[BUFFER_SIZE] = "this is a test of a much longer message i'm interested to see how it does so im just going to keep typing forever. That was a period and THESE are uppercase, and heres some numbers: 232 234";
    
    switch (input) {
        case 1:
            printf("You chose to encode a file\n");
            encodeFile(originalFile, message, offset);
            break;
        case 2:
            printf("You chose to decode a file\n");

            printf("What is the modified file? (ex: encoded.png): ");
            if (fgets(encodedFile, BUFFER_SIZE, stdin) != NULL) {
                size_t len = strlen(encodedFile);
                if (len > 0 && encodedFile[len - 1] == '\n') {
                    encodedFile[len - 1] = '\0';
                }
            }
            printf("You chose to use the file: %s\n", encodedFile);
            decodeFile(originalFile, encodedFile, offset);
            break;
        default:
            printf("You chose to enter an invalid option for encode/decode\nexiting...\n");
    }
    return 0;
}
