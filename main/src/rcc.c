#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


char* int_to_binary(unsigned int value) {
    char* binary = malloc(9); 
    binary[8] = '\0'; 
    for (int i = 7; i >= 0; --i) {
        binary[i] = (value & 1) + '0';
        value >>= 1;
    }
    return binary;
}

char* lsb_to_string(unsigned char value) {
    char* bitString = malloc(2); 
    bitString[0] = (value & 1) + '0'; 
    bitString[1] = '\0'; 
    return bitString;
}

int main() {
    int width, height, channels;
    unsigned char *img = stbi_load("out.png", &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error: Bild konnte nicht geoeffnet werden.\n");
        exit(1);
    }

    if (channels < 3) {
        printf("Error: Channel-Error dieses Bild hat nicht genügend Channels.\n");
        stbi_image_free(img);
        exit(1);
    }

    FILE* file = fopen("RGB_DUMP_TEMP.txt", "w");
    if (file == NULL) {
        printf("Error Dump konnte nicht erstellt werden.\n");
        stbi_image_free(img);
        exit(1);
    }

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            unsigned char* pixel = img + (j * width + i) * channels;
            char* r_bin = int_to_binary(pixel[0]);
            char* g_bin = int_to_binary(pixel[1]);
            char* b_bin = int_to_binary(pixel[2]);

            
        
            
            fprintf(file, "Pixel [%d, %d]: R=%s, G=%s, B=%s\n", i, j, r_bin, g_bin, b_bin);

            

            free(r_bin);
            free(g_bin);
            free(b_bin);
        }
    }

    fclose(file);

    stbi_image_free(img);
    printf("RGB Dump wurde fertig gestellt.\n");
    return 0;
}
