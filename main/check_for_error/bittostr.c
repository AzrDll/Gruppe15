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

char* BittoText(char* bin){
    int len = strlen(bin);
    char *str = malloc(len / 8 + 1);
    if(str == NULL)
    {
        printf("Error: Speicher konnte nicht allokiert werden\n");
        exit(1);
    }
  
    int endOfCodeTermination = strlen("/*404 END OF FORMATED CODE*/");

    for(int i = 0; i < len; i += 8){
        char byte = 0;
            for(int j = 0; j < 8; j++){
                byte = (byte << 1) | (bin[i + j] - '0');
            }

            str[i / 8] = byte;  

            if(i >= endOfCodeTermination * 8 && strncmp(str + i / 8 - endOfCodeTermination + 1, "/*404 END OF FORMATED CODE*/", endOfCodeTermination) == 0){
                str[i / 8 - endOfCodeTermination + 1] = '\0';
                break;
            }
        
    }
    str[len / 8] = '\0';  

    return str;
}

void writeSringToFile(const char* str, const char* outputFile){
    FILE *file = fopen(outputFile, "w");
    if (file == NULL)
    {
        printf("Error: Datei konnte nicht erstellt werden\n");
        exit(1);
    }

    fputs(str, file);
    fclose(file);

}

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Usage: %s <image>\n", argv[0]);
        return 1;
    }

    const char *imgPath = argv[1];

    char *bit = LSBtoBit(imgPath);
    char *text = BittoText(bit);
    writeSringToFile(text, "out.txt");
    free(bit);
    free(text);
}