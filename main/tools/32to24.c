#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>

unsigned char* convertRGBAtoRGB(unsigned char* rgba, int width, int height) {
    int channels_in = 4;
    int channels_out = 3;
    size_t total_pixels = width * height;
    unsigned char* rgb = (unsigned char*)malloc(total_pixels * channels_out);
    if (rgb == NULL) {
        fprintf(stderr, "Error bei malloc.\n");
        exit(1);
    }

    for (size_t i = 0, j = 0; i < total_pixels * channels_in; i += channels_in, j += channels_out) {
        rgb[j] = rgba[i];      
        rgb[j + 1] = rgba[i + 1]; 
        rgb[j + 2] = rgba[i + 2]; 
    }

    return rgb;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s [Path2Bild]\n", argv[0]);
        return 1;
    }

    const char* outPNG = "output.png";

    int width, height, channels;
    unsigned char* img = stbi_load(argv[1], &width, &height, &channels, 0);
    if (img == NULL) {
        fprintf(stderr, "Bild konnte nicht geladen werden.\n");
        return 1;
    }

    if (channels != 4) {
        fprintf(stderr, "Bild ist nicht 32Bit.\n");
        stbi_image_free(img);
        return 1;
    }

    unsigned char* converted_img = convertRGBAtoRGB(img, width, height);
    stbi_image_free(img); 

    if (!stbi_write_png(outPNG, width, height, 3, converted_img, width * 3)) {
        fprintf(stderr, "Fehler Bild konnte nicht erstellt werden.\n");
        free(converted_img);
        return 1;
    }

    free(converted_img); 
    printf("Passt.\n");
    return 0;
}

/* gcc -o 4to3 32to24.c */