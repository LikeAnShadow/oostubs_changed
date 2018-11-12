/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

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

#include "machine/cgascr.h"


void CGA_Screen::scroll_down() {
    char* old_char = CGA_START;
    char* new_char = CGA_START + 2 * LINE_WIDTH;
    for (int zeile = 0; zeile <= LINES-2; zeile++) {
        for (int spalte = 0; spalte <= LINE_WIDTH; spalte++) {
            *(old_char++) = *(new_char++);
            *(old_char++) = *(new_char++);
        }
    }
    new_char = CGA_START + 2*(LINES-1)*LINE_WIDTH;
    for (int last = 0; last <= LINE_WIDTH*2; last++) {
        *(new_char++) = 0;
    }
}

/* Schreibe Zeichen c and Position(x,y) mit den Attributen param */
void CGA_Screen::show(int x, int y, char c, unsigned char param) {
    if (0 <= x && x <= LINE_WIDTH-1 && 0 <= y && y <= LINES-1) {
        pos = CGA_START + 2 * (x + y * LINE_WIDTH);
        *pos = c;
        *(pos +1) = param;
    }

}

/* Setter für den Cursor */
void CGA_Screen::setpos(int x, int y) {
    int cursor_pos = y*LINE_WIDTH+x;
    // Setze upper Byte der Cursorposition
    index.outb(14);
    // upper Byte
    data.outw(cursor_pos >> 8);
    // Setze lower Byte der Cursorposition
    index.outb(15);
    // lower Byte
    data.outw(cursor_pos%256);
}

/* Getter für den Cursor */
void CGA_Screen::getpos(int &x, int &y) {
    // Hole upper Byte
    index.outb(14);
    // links shift, da upper byte
    int cursor_pos = data.inb() << 8;
    // Hole lower Byte
    index.outb(15);
    // Addiere auf
    cursor_pos += data.inb();
    // Umrechnung in (x,y)-Koordinaten
    y = cursor_pos/LINE_WIDTH;
    x = cursor_pos%LINE_WIDTH;
}

void CGA_Screen::print(char* text, int length, unsigned char attrib) {
    // (x,y)-Koordinaten holen
    int x_pos, y_pos;
    getpos(x_pos, y_pos);
    // ueber text iterieren
    for (int i = 0; i < length; i++) {
        if (*text == '\n') {
            text++;
            x_pos = 0;
            y_pos++;
        }
        else {
            char c = *(text++);
            // überprüfe, ob das Zeilenende erreicht ist
            if (x_pos >= LINE_WIDTH) {
                x_pos = 0;
                y_pos++;
            }
            // Überprüfe, ob das Seitenende erreicht ist
            if (y_pos >= LINES) {
                scroll_down();
                y_pos = LINES - 1;
                x_pos = 0;
            }
            // schreibe aktuellen char an aktuelle Koordinate
            show(x_pos++, y_pos, c, attrib);
        }
    }
    // aktualisiere Cursor (nur der Schönheit halber)
    if (x_pos >= LINE_WIDTH) {
        x_pos = 0;
        y_pos++;
    }
    if (y_pos >= LINES) {
        scroll_down();
        y_pos = LINES-1;
        x_pos = 0;
    }
    setpos(x_pos, y_pos);
}
