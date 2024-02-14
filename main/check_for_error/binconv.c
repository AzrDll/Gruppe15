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
    int bitCount = 0;
    while((c = fgetc(imgFile)) != EOF){
        for(int i = 7; i >= 0; i--){
            fputc(((c >> i) & 0x1) + '0', outputFile); 
            bitCount++;

            if(bitCount == 8){
                fputc('\n', outputFile);
                bitCount = 0;
            }
        }
    }   

    fclose(imgFile);
    fclose(outputFile);
}

void checksimilarity(const char* check1, const char* check2){
    FILE *file1 = fopen(check1, "r");
    if (file1 == NULL)
    {
        printf("Error: Datei konnte nicht geladen werden\n");
        exit(1);
    }

    FILE *file2 = fopen(check2, "r"); 
    if (file2 == NULL)
    {
        printf("Error: Datei konnte nicht geladen werden\n");
        exit(1);
    }

    int char1, char2;
    char1 = fgetc(file1);
    char2 = fgetc(file2);

    while ((char1 != EOF) && (char2 != EOF)){
        if (char1 != char2){
            printf("Datein sind gleich.\n");
            fclose(file1);
            fclose(file2);
            return;
        }
        char1 = fgetc(file1);
        char2 = fgetc(file2);
    }

    if (char1 == EOF && char2 == EOF){
        printf("Datein sind gleich.\n");
    } else {
        printf("Datein sind nicht gleich.\n");
    }

    fclose(file1);
    fclose(file2);
}

int main(){

    TexttoBit("test.txt", "out.bin");
    checksimilarity("test.bin", "out.bin");

}