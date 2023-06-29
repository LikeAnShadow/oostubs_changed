/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       S T R I N G B U F F E R                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Stringbuffer stellt einen Puffer fuer die Sammlung von Zeichen */
/* zur Darstellung auf dem Bildschirm oder anderen Ausgabegeraeten bereit.   */
/* Die Ausgabe der Zeichen erfolgt, sobald der Puffer voll ist oder wenn     */
/* explizit die Methode flush() aufgerufen wird.                             */
/* Da Stringbuffer geraeteunabhaengig sein soll, ist flush() eine virtuelle  */
/* Methode, die von den abgeleiteten Klassen definiert werden muss.          */
/*****************************************************************************/

#include "object/strbuf.h"

Stringbuffer::Stringbuffer(){
    int i = 0;
    // Erstelle einen Pointer, der auf das aktuelle Element im Buffer zeigen soll
    char* pointer = (char*)(this->buf);
    // Nullueberschreiben, um alte Daten zu löschen
    for(; i < BUF_SIZE; i++){
        *(pointer++)=0;
    }
}

Stringbuffer::Stringbuffer(const Stringbuffer &copy){
    int i = 0;
    // Erstelle einen Pointer, der auf das aktuelle Element im Buffer zeigen soll
    char* pointer = (char*)(this->buf);
    char* other_pointer = (char*)copy.buf;
    // Diesmal nicht Nullueberschreiben, sondern bitweises kopieren
    for(; i < BUF_SIZE; i++){
        *(pointer++)= *(other_pointer);
    }
}


// Haengt c an das Ende des Buffers
void Stringbuffer::put (char c){
    if(c == 13) return;
    if(counter == BUF_SIZE) flush();
    buf[counter++] = c;
}