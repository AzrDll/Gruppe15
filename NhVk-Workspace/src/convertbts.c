/**
 * Auch bloat, brauchen wir später für bin-to-str
 * **/

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void imgtoRGB(const char* imgPath, const char* bitDumpPath){
    int width, height, channels;

    unsigned char *img = stbi_load(imgPath, &width, &height, &channels, 0);
    if(img == NULL){
        printf("Error: Bild konnte nicht geladen werden\n");
        exit (1);
    }

    printf("Success: Bild wurde geladen!\n");

    FILE *bitDump = fopen(bitDumpPath, "w");
    if(bitDump == NULL){
        printf("Error: Temp konnte nicht geladen werden!\n");
        exit (1);
    }

    int bitGroup = 0;
    int bitCount = 0;

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            unsigned char *p= img + (y*width + x)*channels;

            unsigned char r = p[0];
            unsigned char g = p[1];
            unsigned char b = p[2];

            bitGroup = (bitGroup << 1) | (r & 1);
            bitCount++;
            if(bitCount == 8){
                char bitString[9];
                for(int i = 7; i >= 0; --i){
                    bitString[i] = (bitGroup & 1) ? '1' : '0';
                    bitGroup >>= 1;
                }
                bitString[8] = '\0'; 
                fprintf(bitDump, "%s\n", bitString);
                bitGroup = 0;
                bitCount = 0;
            }

            bitGroup = (bitGroup << 1) | (g & 1);
            bitCount++;
            if(bitCount == 8){
                char bitString[9];
                for(int i = 7; i >= 0; --i){
                    bitString[i] = (bitGroup & 1) ? '1' : '0';
                    bitGroup >>= 1;
                }
                bitString[8] = '\0';
                fprintf(bitDump, "%s\n", bitString);
                bitGroup = 0;
                bitCount = 0;
            }

            /**
             * Danke an Copilot für die arythmetik lol bitGroup = (bitGroup << 1) | (b & 1); ist insane wenn man es versteht...
             * 
             * (bitGroup << 1) -> schiebt die bits um 1 nach links
             * | (b & 1) -> fügt das letzte bit von b an die letzte stelle von bitGroup an
             * bitCount++; -> erhöht den bitCount um 1
             * 
             * aber wie funktioniert jetzt (b & 1) ???
             * 
             * naja 
             * 
             * & ist ein bitweises AND
             * 
             * und 1 ist 00000001
             * 
             * also wird nur das letzte bit von b übernommen und mit 1 verglichen wenn 1 & 1 ist dann ist das ergebnis 1, wenn 1 & 0 ist dann ist das ergebnis 0
             * 
             * unglaublich schlau hätte ich nicht selbst drauf kommen können... also danke an die GitHub Devs und OpenAI lmfao :skull:
             * 
             * rest von der arythmetik ist einfach nur das bitGroup und bitCount updaten, und einen overflow verhindern. Aber trotzdem blown away...
             * **/

            bitGroup = (bitGroup << 1) | (b & 1);
            bitCount++;
            if(bitCount == 8){
                char bitString[9];
                for(int i = 7; i >= 0; --i){
                    bitString[i] = (bitGroup & 1) ? '1' : '0';
                    bitGroup >>= 1;
                }
                bitString[8] = '\0'; 
                fprintf(bitDump, "%s\n", bitString);
                bitGroup = 0;
                bitCount = 0;
            }
        }
    }

    if(bitCount > 0){
        fprintf(bitDump, "%s", bitGroup);
    }

    fclose(bitDump);
    stbi_image_free(img);
}


int main(){
    imgtoRGB("./img.jpg", "./test.txt");
    return 0;
}   