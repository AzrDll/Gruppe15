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

    int i;
    for(i = 0; i < ((fgetc(file1) != EOF) && (fgetc(file2) != EOF)); i++){
        if(fgetc(file1) != fgetc(file2)){
            printf("Files are not similar\n");
            return;
        }
        else{
            printf("Files are similar\n");
        }
    }

}

int main(){

    TexttoBit("test.txt", "out.bin");
    checksimilarity("test.bin", "out.bin");

}