#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Struktur für ein RGB-Pixel
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

// Funktion zur Konvertierung eines Zeichens in eine binäre Zeichenkette
char* byte_to_binary(unsigned char x) {
    char* binary = (char*)malloc(9); // 8 Bits + Nullterminator
    if (binary == NULL) {
        printf("Error: Speicher konnte nicht allokiert werden\n");
        exit(1);
    }

    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = ((x >> i) & 1) ? '1' : '0'; // Bit für Bit überprüfen und in Zeichen konvertieren
    }
    binary[8] = '\0'; // Nullterminator setzen

    return binary;
}

// Funktion zum Verstecken eines Texts in einem Bild
void hide_text_in_image(const char* image_path, const char* output_path, const char* text) {
    int width, height, channels;

    // Bild laden
    unsigned char *img = stbi_load(image_path, &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error: Bild konnte nicht geladen werden\n");
        exit(1);
    }

    // :)
    size_t text_len = strlen(text);
    int pixelIndex = 0;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            unsigned char *p = img + (y * (width) + x) * (channels);
            if (pixelIndex < text_len) {
                p[0] = text[pixelIndex]; // setze den roten Farbwert (0 - 254) auf den ASCI-Wert (0-127)
            }
            pixelIndex += channels; // Zum nächsten Pixel springen
        }
    }

    // Text in das Bild verstecken

    for (size_t i = 0; i < text_len; i++) {
        img[pixelIndex] = text[i]; // Verstecke das Zeichen im roten Anteil des Pixels
        
    }

    // Bild speichern
    stbi_write_jpg(output_path, width, height, channels, img, 100);

    // Speicher freigeben
    stbi_image_free(img);
}

// Funktion zum Extrahieren eines Texts aus einem Bild
char* extract_text_from_image(const char* image_path) {
    int width, height, channels;

    // Bild laden
    unsigned char *img = stbi_load(image_path, &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error: Bild konnte nicht geladen werden\n");
        exit(1);
    }


    // Text aus dem Bild extrahieren
    char* extracted_text = (char*)malloc((width * height * channels) + 1); // Platz für den extrahierten Text + Nullterminator
    if (extracted_text == NULL) {
        printf("Error: Speicher konnte nicht allokiert werden\n");
        exit(1);
    }

int pixelIndex = 0;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            unsigned char *p = img + (y * (width) + x) * (channels);
            extracted_text[pixelIndex] = p[0];
            pixelIndex += channels; // Zum nächsten Pixel springen
        }
    }
    extracted_text[pixelIndex] = '\0'; // Nullterminator setzen

    // Speicher freigeben
    stbi_image_free(img);

    return extracted_text;
}

int main(int argc, char** argv) {
    // Überprüfen der Befehlszeilenargumente
    if (argc < 3 || argc > 4) {
        printf("Verwendung: %s <Bildpfad> <'hide' oder 'extract'> [<Geheimtext>]\n", argv[0]);
        return 1;
    }

    const char* image_path = argv[1];
    const char* mode = argv[2];

    if (strcmp(mode, "hide") == 0) {
        if (argc != 4) {
            printf("Fehlender Geheimtext\n");
            return 1;
        }
        const char* text = argv[3];
        hide_text_in_image(image_path, "output.jpg", text);
        printf("Geheimtext erfolgreich in das Bild versteckt.\n");
    } else if (strcmp(mode, "extract") == 0) {
        char* extracted_text = extract_text_from_image(image_path);
        printf("Extrahierter Text: %s\n", extracted_text);
        free(extracted_text); // Speicher freigeben
    } else {
        printf("Unbekannter Modus: '%s'. Verwenden Sie 'hide' oder 'extract'.\n", mode);
        return 1;
    }

    return 0;
}
