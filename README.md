# Projekt der Gruppe 15

Dieses Projekt ist ein WIP und hat sich als Ziel gesetzt, durch LSB Steganographie eine Text-Datei in ein Bild zu Kodieren.

## Teilnehmer*innen:

- Jenny Herrmann

- Philipp Reich 

- Noah Vesenjak-Dolinsek

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



# Funktion

## main.c

Unsere `main.c-Datei` nimmt eine Bild-Datein und eine Text-Datei und verwendet die Least-Significant-Bit (LSB) Steganographie, um minimale Änderungen im Bild vorzunehmen und den Text aus der Text-Datei zu verbergen.

# Usage

Schritt 1:

`gcc main.c -o [gewünschter Name].exe` --> output ist eine .exe Datei

Schritt 2: 

`[Name].exe ./[Path-To-Text] ./[Path-To-Image]`--> Programm läd, nach ca. 20-40 Sekunden (auf unserem Testsystem) sollten 3 neue Datein im Ordner liegen. ./[Output-Image] ./[Bin-Output] ./[Output-Text]

**Achtung, es können keine 32bit Bilder verwendet werden (i.e. keine Bilder mit Transparentem Hintergrund, da dazu 4 Channels gebraucht werden.)**

## Resourcen:

Die Resourcen, die wir für das Projekt verwenden werden im folgenden gelistet:

- ['stb_image.h'](https://github.com/nothings/stb): Diese Datei kommt von [nothings](https://twitter.com/nothings), durch diese können wir uns die Pixel eines Bildes ganz genau anschauen.
- [imgtochannels.c](NhVk-Workspace/imgtochannels.c) war der erste Versuch unserer Gruppe Pixel Daten einzulesen. 
