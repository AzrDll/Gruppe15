#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void TexttoBit(const char* inputFilePath, const char* outputFilePath){

    FILE *imgFile = fopen(inputFilePath, "r");
    if(imgFile == NULL)
    {
        printf("Error: Input-File konnte nicht geladen werden\n");
        exit (1);
    }

    FILE *outputFile = fopen(outputFilePath, "w");
    if(outputFile == NULL)
    {
        printf("Error: Datei konnte nicht erstellt werden\n");
        exit (1);
    }

    char c;
    while((c = fgetc(imgFile)) != EOF){
        for(int i = 7; i >= 0; i--){
            fputc(((c >> i) & 0x1) + '0', outputFile); 
        }
    }   


    fclose(imgFile);
    fclose(outputFile);
}

void setLeastSignificantBit(unsigned char *c, int bitValue){
    *c &= ~0x01;
    if (bitValue == 1){
        *c |= 0x01;
    }
}

void WritetoImg(const char* imgPath, const char* binaryOut, const char* outputImage){
    int width, height, channels;
    unsigned char *img = stbi_load(imgPath, &width, &height, &channels, 0);

    if (img == NULL)
    {
        printf("Error: Bild konnte nicht geladen werden\n");
        exit(1);
    }

    FILE *binaryFile = fopen(binaryOut, "r");
    if(binaryFile == NULL)
    {
        printf("Error: Datei konnte nicht geladen werden\n");
        exit (1);
    }

    int b;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            unsigned char *p = img + (y * width + x) * channels;
            for(int i = 0; i < channels && (b = fgetc(binaryFile)) != EOF; i++){
                if (i < 3){
                    int bitValue = b - '0';
                    setLeastSignificantBit(&p[i], bitValue);
                }
            }
        } 
    }

    fclose(binaryFile);

    if(!stbi_write_png(outputImage, width, height, channels, img, width * channels)){
        printf("Error: Bild konnte nicht gespeichert werden\n");
        exit(1);
    }

    stbi_write_png(outputImage, width, height, channels, img, width * channels);

}

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
    if (argc != 3){
        printf("Usage: %s <yourTextFile> <yourImageFile>\n", argv[0]);
        return 1;
    }

    const char *inputFilePath = argv[1];
    const char *imgPath = argv[2];

    char binaryOut[200] = "binoutput.txt";
    char outputImage[200] = "output.png";
    char outputText[200] = "output.txt";

    TexttoBit(inputFilePath, binaryOut);
    WritetoImg(imgPath, binaryOut, outputImage);

    char *binaryString = LSBtoBit(outputImage);
    if(binaryString != NULL){
        char *eS = BittoText(binaryString);
        writeSringToFile(eS, outputText);

        free(binaryString);
        free(eS);
    }
    else {
        fprintf(stderr, "Error: Binarys konnten nicht von Bild extrahiert werden\n");
        return 1;
    }

}

/*
int main(){
    TexttoBit("test.txt", "test.bin");
    WritetoImg("cpy.png", "test.bin", "out.png");

    char *binaryString = LSBtoBit("out.png");
    if (binaryString != NULL){
        char *eS = BittoText(binaryString);
        writeSringToFile(eS, "f_output.txt");

        free(binaryString);
        free(eS);
    }
    else {
        fprintf(stderr, "Error: Binarys konnten nicht von Bild extrahiert werden\n");
        return 1;
    }
}
*/