#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* byte_to_binary(int x) {
    char* b = malloc(9);
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1) {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

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

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            unsigned char *p= img + (y*width + x)*channels;

            unsigned char r = p[0];
            unsigned char g = p[1];
            unsigned char b = p[2];

            char* rBin = byte_to_binary(r);
            char* gBin = byte_to_binary(g);
            char* bBin = byte_to_binary(b);  

            fprintf(bitDump,"r: %s, g: %s, b: %s\n", rBin, gBin, bBin);

            free(rBin);
            free(gBin);
            free(bBin);
        }

    }

    fclose(bitDump);
    stbi_image_free(img);

}

int main(){
    imgtoRGB("./img.jpg", "./test.txt");
    return 0;
}
