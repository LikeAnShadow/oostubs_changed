/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Queue, die der Gloeckner verwaltet.        */
/*****************************************************************************/

#include "meeting/bellringer.h"

void Bellringer::check(){
    Bell *bell;
    // hole erste Glocke
    bell = (Bell*)first();
    if(!bell) return;
    // dekrementieren diese
    // andere Glocke in der Liste müssen nicht dekrementiert werden, da die
    // Ticks entsprechend angepasst wurden
    bell -> tick();
    // falls ticks auf null
    if(bell -> run_down()){
        // aus der Liste entfernen
        dequeue();
        // und läuten was das Zeug hält
        bell -> ring();
    }
}

// Glocke an die richtige Stelle der Liste einfügen, sodass Glocken in der
// passenden chronologischen Reihenfolge geläutet werden
void Bellringer::job(Bell *bell, int ticks){
    Bell *now;
    Bell *old;
    int allticks = 0;

    // hole erste Glocke
    now = (Bell*)first();
    // wenn Liste noch besetzt
    if(now != 0){
        // Wenn neue Glocke weniger ticks hat
        if(ticks < now -> wait()){
            // passe Ticks an
            now -> wait(now -> wait() - ticks);
            // setze neue Glocke
            bell -> wait(ticks);
            // und füge in die Liste ein
            insert_first(bell);
        // Wenn neue Glocke mehr ticks hat
        } else{
            // Laufe bis zum letzten Element
            while(now -> next != 0){
                // Hilfsvariable
                old = now;
                // zur nächsten Glocke
                now = (Bell*)(now -> next);
                // Addiere ticks der nächsten Glocke
                allticks += old -> wait();

                // Wenn neue Glocke weniger ticks hat, als alle Glocken bis
                // hier zusammen
                if(ticks < now -> wait() + allticks){
                    // setze richtige ticks für neue Glocke
                    bell -> wait(ticks - allticks);
                    // aktualisiere Ticks der Glocke in der Liste
                    now -> wait(now -> wait() - (ticks-allticks));
                    // setzt neue Glocke an die richtige Stelle in der Liste
                    insert_after(old, bell);
                    // breche aus der Schleife aus
                    return;
                }
                // sonst gehe zur nächsten Glocke in der Liste
            }
            // neue Glocke hat mehr Ticks, als alle anderen Glocken in der
            // Liste zusammen
            // Ticks anpassen
            bell -> wait(ticks - now -> wait());
            // an das Ende der Liste einfügen
            enqueue(bell);
        }
    // Wir sind hier, wenn die Liste leer war
    }else{
        // Dann einfach Ticks setzen
        bell -> wait(ticks);
        // und in die Liste einfügen
        enqueue(bell);
    }

}

void Bellringer::cancel(Bell *bell){
    // Glocke aus der Liste löschen... eZ
    remove(bell);
}
