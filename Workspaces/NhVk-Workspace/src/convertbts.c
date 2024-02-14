#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Test
// imgtoRGB: nimmt ein bild und schreibt die RGB bits in eine datei
void imgtoRGB(const char* imgPath, const char* bitDumpPath){
    int width, height, channels;

    // stbi_load: lädt ein bild in den speicher
    unsigned char *img = stbi_load(imgPath, &width, &height, &channels, 0);
    if(img == NULL){
        printf("Error: Bild konnte nicht geladen werden\n");
        exit (1);
    }

    // message für den User, das Bild wurde geladen
    printf("Success: Bild wurde geladen!\n");

    // öffnet die datei in die die bits geschrieben werden
    FILE *bitDump = fopen(bitDumpPath, "w");
    if(bitDump == NULL){
        printf("Error: Temp konnte nicht geladen werden!\n");
        exit (1);
    }

    // message für den User, die datei wurde geladen
    printf("Success: Temp wurde geladen!\n");


    // die bitGroup und der bitCounter werden initialisiert
    int bitGroup = 0;
    int bitCount = 0;

    // basically das gleiche wie bei imgtochannels.c
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){

            // docu für die arythmetik ist in imgtochannels.c, wenn ich Zeit habe werde ich das hier auch noch dokumentieren
            unsigned char *p= img + (y*width + x)*channels;

            unsigned char r = p[0];
            unsigned char g = p[1];
            unsigned char b = p[2];


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

            bitGroup = (bitGroup << 1) | (r & 1);

            //bitCount wird um 1 erhöht
            bitCount++;

            // wenn bit count 8 ist dann wird der bitGroup in einen string umgewandelt und in die datei geschrieben
            if(bitCount == 8){
                // bitString [9] weil der letzte char ein \0 sein muss
                char bitString[9];

                // die bits werden in den string geschrieben
                for(int i = 7; i >= 0; --i){
                    // wenn das letzte bit von bitGroup 1 ist dann wird ein 1 in den string geschrieben, wenn nicht dann wird ein 0 in den string geschrieben
                    bitString[i] = (bitGroup & 1) ? '1' : '0';
                    // die bits werden um 1 nach rechts geschoben
                    bitGroup >>= 1;
                }
                // der letzte char wird ein \0
                bitString[8] = '\0'; 
                // der string wird in die datei geschrieben
                fprintf(bitDump, "%s\n", bitString);
                // die bitGroup und der bitCount werden zurückgesetzt
                bitGroup = 0;
                bitCount = 0;
            }

            // gleich wie bei r
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

            // gleich wie bei r
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
    /*
    TODO:

    - image file als Argument
    - text.txt als echtes temp was sich nach dem Prozess selbst löscht
    - Verschlüsselung für bessere Sicherheit 
    - Formatierung?
    - Hin und Rückwandlung

    - notes NhVk
    
    */
    imgtoRGB("./img.jpg", "./test.txt");
    return 0;
}   
