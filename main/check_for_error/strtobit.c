#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* LSBtoBit(const char* imgPath){
    int width, height, channels;
    unsigned char *img = stbi_load(imgPath, &width, &height, &channels, 0);
    if(img == NULL)
    {
        printf("Error: Bild konnte nicht geladen werden\n");
        exit (1);
    }

    char *str = malloc(width * height * channels + 1);
    if(str == NULL)
    {
        printf("Error: Speicher konnte nicht allokiert werden\n");
        exit(1);
    }

    for(int i=0; i < width * height * channels; i++){
        str[i] = (img[i] & 0x01) + '0';
    }

    str[width * height * channels] = '\0';

    stbi_image_free(img);

    return str;
}

void writeBittoFile(const char* str, const char* outputFilePath){
    FILE *outputFile = fopen(outputFilePath, "w");
    if(outputFile == NULL)
    {
        printf("Error: Datei konnte nicht erstellt werden\n");
        exit (1);
    }

    for(int i = 0; i < strlen(str); i++){
        fputc(str[i], outputFile);
    }   

    fclose(outputFile);
}

int main(){
    char *bit = LSBtoBit("out.png");
    writeBittoFile(bit, "asdasdadadadadadadasd.txt");
    free(bit);
}