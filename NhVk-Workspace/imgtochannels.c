#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>

void imgtoRGB(const char* imagePath, const char* tempFilePath) {
    int width, height, channels;

    unsigned char *img = stbi_load(imagePath, &width, &height, &channels, 0);
    if(img == NULL){
        printf("Error: Bild konnte nicht geladen werden\n");
        exit (1);
    }

    printf("Bild wurde geladen!\n");

    FILE *tempFile = fopen(tempFilePath, "w");
    if(tempFile == NULL){
        printf("Error: Temp konnte nicht geladen werden!\n");
        exit (1);
    }

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            unsigned char *p= img + (y*width + x)*channels;

            unsigned char r = p[0];
            unsigned char g = p[1];
            unsigned char b = p[2];
            fprintf(tempFile, "Pixel am Punkt %d, %d hat die RGB Value: %u %u %u \n", x, y, r, g, b); 
        }
        fprintf(tempFile, "\n");
    }

    fclose(tempFile);
    stbi_image_free(img);
}

int main(){
    imgtoRGB("./img.jpg", "./temp.txt");
    return 0;
}