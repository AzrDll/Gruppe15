#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;


int main(int argc, char** argv){
 int width, height, channels;

    unsigned char *img = stbi_load("./Eifelturm-767x522.jpg", &width, &height, &channels, 0);
    if(img == NULL){
        printf("Error: Bild konnte nicht geladen werden\n");
        exit (1);
    }
    printf("Success: Bild wurde geladen!\n");

    RGBPixel* rgbArray = (RGBPixel*)malloc((width) * (height) * sizeof(RGBPixel));
    if(rgbArray == NULL) {
        printf("Error: Speicher konnte nicht allokiert werden\n");
        exit(1);
    }

    // Extrahiere Pixel in RGB die als Binary gespeichert sind
    int pixelIndex = 0;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            unsigned char *p = img + (y * (width) + x) * (channels);
            rgbArray[pixelIndex].r = p[0];
            rgbArray[pixelIndex].g = p[1];
            rgbArray[pixelIndex].b = p[2];
            pixelIndex++;
        }
    }

    // Verschlüssele unser Geheimnis
    char* secret = "Hello :)";
    size_t secret_len = strlen(secret);

    for (size_t i = 0; i < secret_len; i++) {
        rgbArray[pixelIndex].r = secret[i];
        pixelIndex++;
    }

    // Speichere das Geheimnis zurück in das Bild
    pixelIndex = 0;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            unsigned char *p = img + (y * (width) + x) * (channels);
            p[0] = rgbArray[pixelIndex].r;
            p[1] = rgbArray[pixelIndex].g;
            p[2] = rgbArray[pixelIndex].b;
            pixelIndex++;
        }
    }

    // Speichere das Bild als Datei ab
    stbi_write_jpg("out.jpg", width, height, channels, img, 100);

    // Freigabe des Speicherplatzes
    free(rgbArray);
    stbi_image_free(img);

    return 0;
}