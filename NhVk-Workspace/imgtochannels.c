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

            // RGB Werte des Pixels
            unsigned char r = p[0];
            unsigned char g = p[1];
            unsigned char b = p[2];

            // Ausgabe der RGB Werte in tempFile
            fprintf(tempFile, "Pixel am Punkt %d, %d hat die RGB Values: %u %u %u \n", x, y, r, g, b); 
        }
        // Zeilenumbruch
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

