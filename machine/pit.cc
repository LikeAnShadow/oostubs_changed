/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "machine/pit.h"

void PIT::interval(int us) {
    this -> us = us;

    double temp = (double)this -> us;

    // intervall normieren
    // 15/(4*PI) = 1,193 also sehr nah an 1,19366207 dran
    temp *= 15;
    temp /= (4*PI);

    char ergebnis = (char)temp;

    // Steuerregister wie folgt beschreiben
    // 00, damit Zähler 0
    // 11, niederwertiges, anschließend höherwertiges Byte
    // 010, damit periodische Unterbrechungen
    // 0, binäre Zählung von 16 Bit
    // ergibt 0b00110100 = 0x34
    this -> steuerregister.outb(0x34);

    // niederwertiges Byte und dann höherwertiges Byte schreiben
    this -> zaehler.outb(ergebnis);
    this -> zaehler.outb(ergebnis >> 8);
}