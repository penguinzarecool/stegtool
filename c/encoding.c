#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encoding.h"

#define BUFFER_SIZE 1000

int encodeFile(char originalFile[BUFFER_SIZE], char message[BUFFER_SIZE], int offset) {
    FILE *infile = fopen(originalFile, "rb");

    if (infile == NULL) {
        perror("error opening input file\n");
        return -1;
    }
    
    FILE *outfile = fopen("encoded.png", "wb");

    if (outfile == NULL) {
        perror("error opening output file\n"); fclose(infile);
        return -1;
    }

    int fileByte;
    
    for (int i = 0; i < offset; i++) {
        if ((fileByte = fgetc(infile)) != EOF) {
            if (fputc(fileByte, outfile) == EOF) {
                perror("Error writing to output file");
                break;
            }
        }
    }
    
    int msgBit;
    int counter = 0;
    
    for (int i = 0; message[i] != '\0'; i++) {
        for (int j = 128; j > 0; j = j / 2) {
            if (j & message[i]) {
                msgBit = 1;
            }
            else {
                msgBit = 0;
            }
            if ((fileByte = fgetc(infile)) != EOF) {
                printf("byte #%d letter: %c fileByte:%d message bit: %d\n", counter + 1, message[i], fileByte, msgBit);
                fileByte = fileByte ^ msgBit;
                printf("new byte: %d\n", fileByte);
                if (fputc(fileByte, outfile) == EOF) {
                    perror("Error writing to output file");
                    break;
                }
            counter++;
            }
            printf("j: %d\n\n", j);
        }
        printf("i: %d\n\n", i);
    }

    while ((fileByte = fgetc(infile)) != EOF) {
        if (fputc(fileByte, outfile) == EOF) {
            perror("Error writing to output file");
            break;
        }
    }
    
    //while ((fileByte = fgetc(infile)) != EOF) {
        //for (int i = 128; i > 0; i = i / 2) {
            
        //}
    //}


    //while ((byte = fgetc(infile)) != EOF) {
     //   printf("byte %d: %d\n", counter + 1, byte);
        //byte = msgByte ^ message[counter];
        //printf("edited byte %d: %d\n", counter, byte);
        //if (fputc(byte, outfile) == EOF) {
            //perror("Error writing to output file");
            //break;
        //}
    //counter++;
    //}

    fclose(infile);
    fclose(outfile);
    printf("File copied byte by byte.\n");
    return 0;
}
