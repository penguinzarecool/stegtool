#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decoding.h"

#define BUFFER_SIZE 1000

int bitsToMessage(int msgByte[8]) {
    int msgInt = 0;
    int index = 0;

    for (int i = 128; i > 0; i = i / 2) {
        msgInt += (i * msgByte[index]);
        index++;
    }
    printf("%c", msgInt);
    return 0;
}

int decodeFile(char originalFile[BUFFER_SIZE], char encodedFile[BUFFER_SIZE], int offset) {
    FILE *file1 = fopen(originalFile, "rb");
    
    if (file1 == NULL) {
        perror("error opening original file\n");
        return -1;
    }
    
    FILE *file2 = fopen(encodedFile, "rb");
    
    if (file2 == NULL) {
        perror("error opening decoded file\n");
        return -1;
    }
    
    int fileByte1;
    int fileByte2;
    int msgBit;
    int msgByte[8];

    int endCtr = 0;

    for (int i = 0; i < offset; i++) {
        if (((fileByte1 = fgetc(file1)) != EOF) && (fileByte2 = fgetc(file2)) == EOF) {
            printf("Error: End of file reached before messsage reached\n");
            return -1;
        }
    }
    printf("\nSecret message: ");

    for (int i = 0; endCtr < 16; i++) {
        if (((fileByte1 = fgetc(file1)) != EOF) && (fileByte2 = fgetc(file2)) != EOF) {
            msgBit = fileByte1 ^ fileByte2;
            if (msgBit == 0) {
                endCtr++;
            }
            else {
                endCtr = 0;
            }
                
        }
        int msgIndex = i % 8; //gets a number 0-7 for index of bit in byte
        msgByte[msgIndex] = msgBit;
        if (msgIndex == 7) {   //if msgByte 0-7 full (full byte of bits)
            bitsToMessage(msgByte);
        }
    }   

    printf("\n");
    return 0;
}
