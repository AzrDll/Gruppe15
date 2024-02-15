# Projekt der Gruppe 15

Dieses Projekt ist ein WIP und hat sich als Ziel gesetzt, durch LSB Steganographie eine Text-Datei in ein Bild zu Kodieren.

## Teilnehmer*innen:

- [Jenny Herrmann](https://github.com/Jenny04H)

- [Philipp Reich](https://github.com/PhilippRe1ch04)

- [Noah Vesenjak-Dolinsek](https://github.com/AzrDll)

## Beschreibung:

Least Significant Bit (LSB)-Steganografie ist eine Methode zum Verstecken von Daten in einem Bild durch Manipulation der niedrigstwertigen Bits der Pixelwerte. Dieses Projekt implementiert die LSB-Steganografie in C und ermöglicht es den Benutzern, geheime Nachrichten in Bildern mit minimalen visuellen Veränderungen zu kodieren und zu dekodieren.

## Konzept

Bei der LSB-Steganografie werden die niederwertigsten Bits der Pixelwerte eines Bildes durch Bits der geheimen Nachricht ersetzt. Da sich diese Bits nur geringfügig auf die Farbe auswirken, sind die Änderungen für das menschliche Auge nicht wahrnehmbar, was sie zu einer wirksamen Methode zum Verbergen von Informationen macht.

## Implementation

Das Projekt ist in C implementiert und verwendet die Bibliothek `stb_image.h` für die Verarbeitung von JPG-Bildern, da diese verlustfrei sind, was für die Integrität der versteckten Daten entscheidend ist.

### Encoding 

1. **Bild laden**: Das Originalbild wird in den Speicher geladen.
2. **Nachrichtenvorbereitung**: Die geheime Nachricht wird in eine binäre Darstellung umgewandelt.
3. **Encodierung**: Die niedrigstwertigen Bits der Pixel des Bildes werden durch die Bits der geheimen Nachricht ersetzt.
4. **Bild speichern**: Das geänderte Bild wird als neue PNG-Datei gespeichert.

### Decoding 

1. **Bild laden**: Das Bild, das die versteckte Nachricht enthält, wird geladen.
2. **Extraktion**: Die niedrigstwertigen Bits der Pixel des Bildes werden gesammelt, um die binäre Darstellung der geheimen Nachricht zu rekonstruieren.
3. **Nachricht dekodieren**: Die binären Daten werden wieder in die ursprüngliche Nachricht umgewandelt.

# Showcase and PoC

***Bild unseres Source Codes:***

<p align="center">
  <a href="https://github.com/AzrDll/Gruppe15/blob/main/main/src/main.c">
    <img src="https://cdn.discordapp.com/attachments/1085987325995135007/1207450485947371522/hi7cEjC.png?ex=65dfb0e5&is=65cd3be5&hm=05fd5eb37d1e9f4069e0b17de313708e9bbd157b29e8f547e3f158529ad92892&" alt="AzRDll style="display:block; margin:auto;" width="400" /></a>
</p>

***Bild unseres Source Codes (mit Source Code):***

<p align="center">
  <a href="https://github.com/AzrDll/Gruppe15/blob/main/main/src/main.c">
    <img src="https://cdn.discordapp.com/attachments/1085987325995135007/1207460655213576252/JjppEHV.png?ex=65dfba5d&is=65cd455d&hm=da1ee4823dfcf3febfae5cf94584648d0fa9ef8b32ff69e99a740d8eb661ad91&" alt="AzRDll style="display:block; margin:auto;" width="400" /></a>
</p>

In diesem Bild ist die Datei main.c formatiert abgespeichert.

# Funktion

## main.c

Unsere `main.c-Datei` nimmt eine Bild-Datein und eine Text-Datei und verwendet die Least-Significant-Bit (LSB) Steganographie, um minimale Änderungen im Bild vorzunehmen und den Text aus der Text-Datei zu verbergen.

### TextToBit

`main.c` hat mehrere Funktionen darunter auch `Texttobin`.

```c
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
```

Text2Bin verwendet eine while-Schleife, die solange ausgeführt wird, bis die Datei inputFilePath leer ist. Dabei wird jedes aktuelle Zeichen in seine 8-Bit-Darstellung umgewandelt und in die Datei ./[Bin-Output] geschrieben (ebenfalls als Char.).

### setLeastSignificantBit

```c
void setLeastSignificantBit(unsigned char *c, int bitValue){
    // Basically *c and not(0x01) --> 11111110 also wird letzte bitValue immer 0
    *c &= ~0x01;
    if (bitValue == 1){
        *c |= 0x01;
    }
}
```

Die Funktion setLeastSignificantBit setzt zuerst das aktuelle LSB auf 0. Wenn bitValue (später im Code relevant) gleich 1 ist, wird diese anstelle des überschriebenen LSB-Werts gesetzt.

### WritetoImg

```c
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
```

WritetoImg ist das Herzstück unserer Logik und daher unser ganzer **Stolz**.

```c
    int b;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
```

`int b`initialisiert eine Ganzzahl-Variable `b`, die später verwendet wird, um die Binärwerte aus der Datei `binaryOut` zu speichern.
Die erste for-Schleife geht über jede Zeile des Bildes von `0` bis `height - 1`.
Die zweite Schleife durchläuft jede Spalte des Bildes von `0` bis `width - 1`.
Auf diese Weise durchlaufen beide Schleifen jedes Pixel des Bildes.

```c
unsigned char *p = img + (y * width + x) * channels;
```

Dieser Teil berechnet die Adresse des einzelnen Pixels an der Position `{x,y}` im Bild. Dabei ist `img` der Zeiger auf den Anfang der Bilddaten. Das Bild ist in einem linearen Array gespeichert, in dem jedes Pixel aus mehreren Kanälen `{r,g,b}` besteht. Die Berechnung `(y * Breite + x) * Kanäle` findet den korrekten Offset im Array für das Pixel `{x,y}`.

```c
for(int i = 0; i < channels && (b = fgetc(binaryFile)) != EOF; i++){
```

`b = fgetc(binaryFile)`liest das nächste Zeichen aus unserer Binärdatei. EOF bedeutet einfach `end of file`.

```c
if (i < 3){
    int bitValue = b - '0';
    setLeastSignificantBit(&p[i], bitValue);
}
```

Die if-Bedingung prüft, ob der aktuelle Kanal den Index < 3 hat. Wenn ja, wird der Character aus dem Bitfile in `b - '0'` umgewandelt. Zum Verständnis, wenn b dem Char 0 entspricht ist 48 - 48 = 0 also int = 0, wenn b aber dem Char 1 entspricht ist 49 - 48 = 1 also int = 1.

Jetzt kommt wieder setLeastSignificantBit ins Spiel. Es ändert nun den Wert an der Stelle `&p[i]` auf unseren bitValue.

```c
stbi_write_png(outputImage, width, height, channels, img, width * channels);
```

Das speichert das Bild im `.png`Format.

### LSBtoBit

```c
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
```

LSBtoBit macht basically genau das Gegenteil von WritetoImg. 

```c
char *str = malloc(width * height * channels + 1);
```

`malloc` Allokiert hier den Speicher für jedes LSB im Bild und den Nullterminierer.

```c
for(int i=0; i < width * height * channels; i++){
        str[i] = (img[i] & 0x01) + '0';
}

str[width * height * channels] = '\0';
``` 
`img[i] & 0x01` extrahiert das LSB an der Stelle [i] und konvertiert es in das entsprechende Zeichen. (0 + 48 = '0', 1 + 48 = '1')

`str[width * height * channels] = '\0';` fügt den Nullterminierer am Ende von str hinzu, wodurch aus `str` ein echter C-String wird.

```c 
stbi_image_free(img);
```

**Wichtig**, sonst wird es schwierig mit dem Memory :) .

### BittoText

```c
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
```

BittoText Konvertiert die binary Strings wieder in lesbare Schrift.

```c
int len = strlen(bin);
char *str = malloc(len / 8 + 1);
```

`int len = strlen(bin)` Berechnet die Länge des binären Strings von `LSBtoBit`.
`char *str = malloc(len / 8 + 1);` Allokiert Speicher für die eingegebene Zeichenkette. Da jedes Byte eines ASCII-Zeichens aus 8 Bit besteht, teilen wir die Länge `len` durch 8, die `+ 1` ist wie immer für den Nullterminierer.

```c
 for(int i = 0; i < len; i += 8){
        char byte = 0;
            for(int j = 0; j < 8; j++){
                byte = (byte << 1) | (bin[i + j] - '0');
            }
```

Der erste for loop geht jeweils über len/8 Iterationen. 

Der zweite for loop geht immer über die 8 Bits des aktuellen Bytes.

`byte = (byte << 1) | (bin[i + j] - '0');` funktioniert wie folgt:

- Der aktuelle Teil von `byte` wird um ein Bit nach links verschoben, um Platz für das nächste zu schaffen, bis das gesamte Byte rekonstruiert ist.
- `bin[i + j] - '0'` nimmt das Zeichen an der Stelle `[i + j]` und wandelt es wieder in seinen `int` Wert um. 
- Zuletzt wird dieser Wert mit `byte` durch den Operator OR (`|`) verknüpft.

```c
str[i / 8] = byte;
```

Indext den Byte an der Stelle `i/8`.

```c
if(i >= endOfCodeTermination * 8 && strncmp(str + i / 8 - endOfCodeTermination + 1, "/*404 END OF FORMATED CODE*/", endOfCodeTermination) == 0){
    str[i / 8 - endOfCodeTermination + 1] = '\0';
    break;
}
```

Wurde Implementiert, da wir kontrolliert diesen Schritt terminieren wollten, da dieser sonst sehr zeitraubend ist.

`strncmp(str + i / 8 - endOfCodeTermination + 1, "/*404 END OF FORMATED CODE*/", endOfCodeTermination) == 0)` Checkt durch eine Art "Pointer allignement" an welchem Punkt im zurzeitigen `str` unsere Termination vorkommen sollte.

```c
str[len / 8] = '\0'; 
```

Sicherheitsmaßnahme für den Fall, dass "jemand" /*404 END OF FORMATED CODE*/ vergisst :) .

### writeStringToFile

```c
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
```

Schreibt den `return str;` von `BittoText` in unser `outputFile`.



# Usage

Schritt 1:

`gcc main.c -o [gewünschter Name].exe` --> output ist eine .exe Datei

Schritt 2: 

`[Name].exe ./[Path-To-Text] ./[Path-To-Image]`--> Programm läd, nach ca. 20-40 Sekunden (auf unserem Testsystem) sollten 3 neue Datein im Ordner liegen. ./[Output-Image] ./[Bin-Output] ./[Output-Text]

### Testsystem

**Laptops der Teilnehmer*innen**

<p align="center">
  <a href="https://github.com/AzrDll/Gruppe15">
    <img src="https://blog.sergeyev.info/images/works-on-my-machine/the-line.jpg" alt="AzRDll style="display:block; margin:auto;" width="400" /></a>
</p>

**Achtung, es können keine 32bit Bilder verwendet werden (i.e. keine Bilder mit Transparentem Hintergrund, da dazu 4 Channels gebraucht werden.)**

**Man kann theoretisch das Tool `32to24.c` verwenden gibt aber keine Doku ;(**

## Resourcen:

Die Resourcen, die wir für das Projekt verwenden werden im folgenden gelistet:

- ['stb_image.h'](https://github.com/nothings/stb), ['stb_image_write.h'](https://github.com/nothings/stb): Diese Dateien kommen von [nothings](https://twitter.com/nothings), durch diese können wir uns die Pixel eines Bildes ganz genau anschauen.
- [imgtochannels.c](NhVk-Workspace/imgtochannels.c) war der erste Versuch unserer Gruppe Pixel Daten einzulesen. 
