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

/******************************************************************************
/* Hier folgen alle << operatoren
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
    switch (man) {
        case BIN:
            castBin((short) number);
            break;
        case DEC:
            castValue((long long) number);
            break;
        case HEX:
            castHex((char *) &number, sizeof(short));
            break;
        case OCT:
            castValue((long long) number, 8);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<< (short number) {
    switch (man) {
        case BIN:
            castBin((short) number);
            break;
        case DEC:
            castValue((long long) number);
            break;
        case HEX:
            castHex((char *) &number, sizeof(short));
            break;
        case OCT:
            castValue((long long) number, 8);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned int number) {
    switch (man) {
        case BIN:
            castBin((int) number);
            break;
        case DEC:
            castValue((long long) number);
            break;
        case HEX:
            castHex((char *) &number, sizeof(int));
            break;
        case OCT:
            castValue((long long) number, 8, true);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<< (int number) {
    switch (man) {
        case BIN:
            castBin((int) number);
            break;
        case DEC:
            castValue((long long) number);
            break;
        case HEX:
            castHex((char *) &number, sizeof(int));
            break;
        case OCT:
            castValue((long long) number, 8, true);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned long number){
    switch (man){
        case BIN:
            castBin((long) number);
            break;
        case DEC:
            castValue((long long) number);
            break;
        case HEX:
            castHex((char*) &number, 4);
            break;
        case OCT:
            castValue((long long) number, 8);
            break;
    }
    return *this;
}

O_Stream& O_Stream::operator<< (long number){
    switch (man){
        case BIN:
            castBin((long) number);
            break;
        case DEC:
            castValue((long long) number);
            break;
        case HEX:
            castHex((char*) &number, 4);
            break;
        case OCT:
            castValue((long long) number, 8);
            break;
    }
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


/******************************************************************************
/* Hier folgen alle cast Hilfsfunktionen
/*                                                                           */
/*****************************************************************************/


void O_Stream::castBin(short number){
    unsigned short compare = (1<<15);
    char x = 0 ;
    bool is_one = false;

    do
    {
        // bitweiser Vergleich
        x = (number&compare)?'1':'0';
        compare = compare>>1;
        if(!is_one)
        {
            if(x=='1')
                is_one=true;
            else
                continue;
        }
        this->put(x);

    }while(compare>0);
}

void O_Stream::castBin(int number){
    unsigned int compare = (1<<(sizeof(int)*8-1));
    char x = 0 ;
    bool is_one = false;

    do
    {
        // bitweiser Vergleich
        x = (number&compare)?'1':'0';
        compare = compare>>1;
        if(!is_one)
        {
            if(x=='1')
                is_one=true;
            else
                continue;
        }
        this->put(x);

    }while(compare>0);
}

void O_Stream::castBin(long number){
    unsigned long compare = (1<<31);
    char x = 0 ;
    bool is_one = false;

    do
    {
        // bitweiser Vergleich
        x = (number&compare)?'1':'0';
        compare = compare>>1;
        if(!is_one)
        {
            if(x=='1')
                is_one=true;
            else
                continue;
        }
        this->put(x);

    }while(compare>0);
}
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
// caste zu char
void O_Stream::castValue(long long value, unsigned int base, bool isUnsigned){
    char array[32];
    char *act = &(array[0]);
    char *last = &(array[32]);
    long temp;

    if((!isUnsigned) && (value<0)) {
        put('-');
        value *= -1;
    }

    temp = (long long) value;
    do
    {
        *act = (temp%base)+'0';
        act++;
        temp = temp/base;
    }while(temp && act != last);

    // Printe number in der richtigen Reihenfolge
    printStringInReverse(&(array[0]), act-1);
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
