#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decoding.h"

#define BUFFER_SIZE 1000

int bitsToMessage(int msgByte[8]) {
    //printf("sanitycheck 6\n");
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
    //printf("sanitycheck 1\n");
    
    if (file1 == NULL) {
        perror("error opening original file\n");
        return -1;
    }
    //printf("sanitycheck 2\n");
    
    FILE *file2 = fopen(encodedFile, "rb");
    //printf("sanitycheck 3\n");
    
    if (file2 == NULL) {
        perror("error opening decoded file\n");
        return -1;
    }
    //printf("sanitycheck 4\n");
    
    int fileByte1;
    //printf("sanitycheck 4.1\n");
    int fileByte2;
    //printf("sanitycheck 4.2\n");
    int msgBit;
    //printf("sanitycheck 4.3\n");
    int msgByte[8];
    //printf("sanitycheck 4.4\n");

    int endCtr = 0;
    //printf("sanitycheck 5\n");

    for (int i = 0; i < offset; i++) {
        if (((fileByte1 = fgetc(file1)) != EOF) && (fileByte2 = fgetc(file2)) == EOF) {
            printf("Error: End of file reached before messsage reached\n");
            return -1;
        }
    }
    printf("Secret message: ");

    for (int i = 0; endCtr < 8; i++) {
        if (((fileByte1 = fgetc(file1)) != EOF) && (fileByte2 = fgetc(file2)) != EOF) {
        //printf("sanitycheck 5.1; bytes: %d %d\n", fileByte1, fileByte2);
            msgBit = fileByte1 ^ fileByte2;
        //printf("sanitycheck 5.2; msgBit: %d\n", msgBit);
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
