/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C G A _ S T R E A M                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse CGA_Stream ermoeglicht die Ausgabe verschiedener Datentypen    */
/* als Zeichenketten auf dem CGA Bildschirm eines PCs.                       */
/* Fuer weitergehende Formatierung oder spezielle Effekte stehen die         */
/* Methoden der Klasse CGA_Screen zur Verfuegung.                            */
/*****************************************************************************/

#include "device/cgastr.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

CGA_Stream::CGA_Stream() : CGA_Screen(), O_Stream() {
    this-> setpos(0,0);
}


void CGA_Stream::flush(){
    this->print(this->buf, (int) this->act_buf_char);
    this->act_buf_char = 0;
    return;
}
