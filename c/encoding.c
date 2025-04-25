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
    
    FILE *outfile = fopen("encoded.ppm", "wb");

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
                fileByte = fileByte ^ msgBit;
                if (fputc(fileByte, outfile) == EOF) {
                    perror("Error writing to output file");
                    break;
                }
            counter++;
            }
        }
    }

    while ((fileByte = fgetc(infile)) != EOF) {
        if (fputc(fileByte, outfile) == EOF) {
            perror("Error writing to output file");
            break;
        }
    }

    fclose(infile);
    fclose(outfile);
    printf("\nFile copied byte by byte.\n");
    return 0;
}
