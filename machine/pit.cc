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

    long temp = this -> us;

    // intervall normieren
    // 15/(4*PI) = 1,193 also sehr nah an 1,19366207 dran
    // Klappt leider nicht, da Multiplikation mit PI zum Absturz führt
    // deswegen *128/107 was auch sehr nahe dran ist, aber etwas zu groß
    // mit -(us*3/1000) passt es ziemlich genau
    temp /= 828;
    temp *= 1000;
//    temp *= 128;
//    temp /= 107;
//    temp = temp - ( ( us*3 ) / 1000 );
    //temp *= 1.19366207;

    // wegen 2 Byte Größe
    unsigned short ergebnis = (unsigned short)temp;

    // Steuerregister wie folgt beschreiben
    // 00, damit Zähler 0
    // 11, niederwertiges, anschließend höherwertiges Byte
    // 010, damit periodische Unterbrechungen
    // 0, binäre Zählung von 16 Bit
    // ergibt 0b00110100 = 0x34
    /*kout.setpos(0,0);
    kout << "Warte auf Prozessor-freigabe";
    kout.flush();
    while((steuerregister.inb() & 0x02) != 0);

    kout << endl << "Versuche in das Steuerregister zu schreiben";
    kout.flush();*/
    this -> steuerregister.outb(0x34);

    /*kout << endl << "Warte auf Zustimmung" << endl;
    kout.flush();
    while((steuerregister.inb() & 0x01) == 0);
    kout << endl << "Zustimmung erhalten" << endl;
    kout.flush();
    kout.setpos(0, 20);
    kout << ergebnis << endl;
    kout.flush();*/
    // niederwertiges Byte und dann höherwertiges Byte schreiben
    this -> zaehler.outb((char)ergebnis);
    this -> zaehler.outb((char)(ergebnis >> 8));
}