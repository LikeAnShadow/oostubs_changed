/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

O_Stream::O_Stream() : Stringbuffer() {
    this -> man = DEC;
}

O_Stream::O_Stream(const O_Stream &copy) : Stringbuffer( copy ) {

}

/*****************************************************************************/
/* Hier folgen alle << operatoren                                            */
/*                                                                           */
/*****************************************************************************/
O_Stream& O_Stream::operator<< (unsigned char c){
    this -> put((char) c);
    return *this;
}

O_Stream& O_Stream::operator<< (char c){
    this -> put(c);
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned short number) {
    cast(number, true);
    return *this;
}

O_Stream& O_Stream::operator<< (short number) {
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned int number) {
    cast(number, true);
    return *this;
}

O_Stream& O_Stream::operator<< (int number) {
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned long number){
    cast(number, true);
    return *this;
}

O_Stream& O_Stream::operator<< (long number){
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (void* pointer){
    // Pointer in Hexadezimaldarstellung
    castHex((char*)&pointer, sizeof(void*));
    return *this;
}

O_Stream& O_Stream::operator<< (char* text){
    // Einzelne chars anfuegen
    while(*text){
        put(*(text++));
    }
    return *this;
}

// Funktion um Manipulatoren anzufuegen
O_Stream& O_Stream::operator<<(O_Stream& (*fkt) (O_Stream&)){
    // easy
    return (*fkt)(*this);
}


/*****************************************************************************/
/* Hier folgen alle cast Hilfsfunktionen                                     */
/*                                                                           */
/*****************************************************************************/

// caste zu hexadecimal
void O_Stream::castHex(char value, char *result){
    if(!result) return;
    char x;

    // wieder bitweiser Vergelich
    x = (value&0x0F);
    if(x > 9)
        x+=55;
    else
        x+='0';
    result[1] = x;

    x = (value&0xF0)>>4;
    if(x > 9)
        x+=55;
    else
        x+='0';
    *result = x;
}
void O_Stream::castHex(char* ptr, char size){
    char symb[2];
    ptr+=size;
    do
    {
        castHex(*(--ptr), &(symb[0]));
        this->put(symb[0]);
        this->put(symb[1]);
        size--;
    }while(size>0);
}

void O_Stream::cast(long long value, bool isUnsigned){
    char array[32];
    char *ptr = &array[0];
    char *lst = &array[32];

    if(!isUnsigned && value < 0){
        put('-');
        value *= -1;
    }

    long long temp = value;
    do{
        if(man != 16){
            *(ptr++) = (temp%man)+'0';
        }else{
            char x = temp%man;
            if(x > 9) {
                x += 7;
            }
            *(ptr++) = x + '0';
        }
        temp = temp/man;
    }while (temp && ptr != lst);
    printStringInReverse(&(array[0]), ptr-1);
}

void O_Stream::printStringInReverse(char* string, char* act){
    string--;
    while(string!=act)
    {
        put(*(act--));
    }
}

// Setter-methode. Wird von Manipulator-fkt genutzt
void O_Stream::setManipulator(manipulator man){
    this -> man = man;
}

// Fuegt einen Zeilenumbruch an
O_Stream& endl(O_Stream& x){
    x.put('\n');
    return x;
}

// BIN: waehlt das binaere Zahlensystem aus.
O_Stream& bin(O_Stream& x){
    x.setManipulator(BIN);
    return x;
};

// OCT: waehlt das oktale Zahlensystem aus.
O_Stream& oct(O_Stream& x){
    x.setManipulator(OCT);
    return x;
}

// DEC: waehlt das dezimale Zahlensystem aus.
O_Stream& dec(O_Stream& x){
    x.setManipulator(DEC);
    return x;
}

// HEX: waehlt das hexadezimale Zahlensystem aus.
O_Stream& hex(O_Stream& x){
    x.setManipulator(HEX);
    return x;
}
