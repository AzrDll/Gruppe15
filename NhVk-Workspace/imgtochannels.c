#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>

void imgtoRGB(const char* imagePath, const char* tempFilePath) {
    int width, height, channels;

    // stbi_load lädt ein Bild und gibt einen Pointer auf die Bilddaten zurück
    unsigned char *img = stbi_load(imagePath, &width, &height, &channels, 0);
    
    // error handling, falls das Bild nicht geladen werden konnte
    if(img == NULL){
        printf("Error: Bild konnte nicht geladen werden\n");
        exit (1);
    }

    printf("Bild wurde geladen!\n");

    // tempFile wird geöffnet
    FILE *tempFile = fopen(tempFilePath, "w");
    
    // error handling, falls tempFile nicht geöffnet werden konnte
    if(tempFile == NULL){
        printf("Error: Temp konnte nicht geladen werden!\n");
        exit (1);
    }

    // für jeden Pixel werden die RGB Werte ausgegeben
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            // Pointer auf den ersten Pixel in der aktuellen Zeile
            unsigned char *p= img + (y*width + x)*channels;

            /**
             * Diese Funktion ist ein wenig scuft, ich versuche das mal zu erklären:
             * 
             * *p ist der Pointer auf den ersten Pixel in der aktuellen Zeile einfacherheits halber stellen wir uns das mal so vor:
             * |p1 p2|
             * |p3 p4|
             * 
             * p1 ist das erste Pixel in der ersten Zeile und wird bei unserem 2x2 Beispiel so berechnet (y*width + x)*channels also (0*2 + 0)*3 = 0, + img ist der Pointer auf den ersten Pixel in der ersten Zeile also p1.
             * Wenn wir nun auf p2 zeigen wollen berechnen wir (0*2 + 1)*3 = 3, also 3 Bytes weiter, da wir 3 Channels haben. Das ist dann p2. Und das geht dann so weiter.
             * 
             * Falls Fragen aufkommen einfach pm per Discord :).
             * 
             * Kann man sich also als Zeilen shift vorstellen.
             * **/

            // RGB Werte des Pixels
            unsigned char r = p[0];
            unsigned char g = p[1];
            unsigned char b = p[2];

            // Ausgabe der RGB Werte in tempFile
            fprintf(tempFile, "Pixel am Punkt %d, %d hat die RGB Values: %u %u %u \n", x, y, r, g, b); 
        }
        // Zeilenumbruch basically :)
        fprintf(tempFile, "\n");
    }

    // tempFile wird geschlossen
    fclose(tempFile);
    // Speicher für das Bild wird freigegeben
    stbi_image_free(img);
}

int main(){
    // Aufruf der Funktion imgtoRGB
    imgtoRGB("./img.jpg", "./temp.txt");
    return 0;
}

