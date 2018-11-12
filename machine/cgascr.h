#ifndef __screen_include__
#define __screen_include__

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/io_port.h"

class CGA_Screen {
    private:
/* Hier muesst ihr selbst Code vervollstaendigen */
    // Anzahl Zeichen für eine Zeile
    int LINE_WIDTH = 80;
    // Anzahl Zeilen
    int LINES = 25;
    // Startpunkt für die Zeichen im Grafikspeicher
    char *CGA_START = (char *)0xb8000;
    // Positionszeiger, um ein Zeichen an eine feste Stelle zu schreiben
    char *pos;
    // Erstelle zwei Ports für das Index-/Datenregister
    IO_Port index = IO_Port(0x3d4);
    IO_Port data = IO_Port(0x3d5);

    // Privater Konstruktor
    CGA_Screen(const CGA_Screen &copy); // Verhindere Kopieren

    public:
    CGA_Screen()
/* Hier muesst ihr selbst Code vervollstaendigen */ 
    {
    }

    void scroll_down();

    void show(int x, int y, char c, unsigned char param);

    void setpos(int x, int y);

    void getpos(int &x, int &y);

    void print (char* text, int length, unsigned char attrib);
/* Hier muesst ihr selbst Code vervollstaendigen */ 
 };

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#endif

