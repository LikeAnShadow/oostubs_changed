/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

#include "syscall/guarded_semaphore.h"

Guarded_Semaphore::Guarded_Semaphore(int c) : Semaphore(c){}

void Guarded_Semaphore::p(){
    Secure section;
    Semaphore::p();
}

void Guarded_Semaphore::v(){
    Secure section;
    Semaphore::v();
}

void Guarded_Semaphore::wait(){
    p();
}

void Guarded_Semaphore::signal(){
    v();
}