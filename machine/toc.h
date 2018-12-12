/* $Id: toc.h 8485 2017-03-27 11:50:06Z friesel $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 T O C                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Struktur toc dient dazu, bei einem Koroutinenwechsel die Werte der    */
/* nicht-fluechtigen Register zu sichern.                                    */
/* Bei der vom GNU C-Compiler genutzten System V AMD64 ABI sind RBP, RBX und */
/* R12 bis R15 nicht-flüchtige Register, die beim Kontextwechsel von Hand    */
/* gesichert werden müssen. Zusätzlich gibt es 108 Byte an nicht-flüchtigem  */
/* Extended CPU State, die aber nur wichtig sind, wenn Komponenten wie die   */
/* FPU oder SIMD-Instruktionen genutzt werden.                               */
/*                                                                           */
/* Achtung: Fuer den Zugriff auf die Elemente von struct toc aus einer       */
/* Assemblerfunktion heraus werden in der Datei toc.inc Namen fuer die       */
/* benoetigten Abstaende der einzelnen Elemente zum Anfang der Struktur      */
/* definiert. Damit dann auch auf die richtigen Elemente zugegriffen wird,   */
/* sollten sich die Angaben von toc.h und toc.inc exakt entsprechen.         */
/* Wer also toc.h aendert, muss auch toc.inc anpassen (und umgekehrt.)       */
/*****************************************************************************/

#ifndef __toc_include__
#define __toc_include__

// TOC: ("thread of control")
//
struct toc {
	void *rbx;
	void *r12;
	void *r13;
	void *r14;
	void *r15;
	void *rbp;
	void *rsp;
	char fpu[108]; // Optional: 108 Byte extended CPU state (MMX, SSE, ...)
	// fpu wurde in der implementierung nicht beachtet, folgt vielleicht
	// irgendwann
};

/*
 * Diese Funktion bereitet die Struktur toc für die erste Aktivierung vor.
 * Dazu müssen Registerinhalte (toc) und Stack (tos) so initialisiert werden,
 * dass bei der ersten Aktivierung die Ausführung mit der Funktion kickoff
 * beginnt, die wiederum den Zeiger object als siebenten Parameter auf dem
 * Stack vorfinden muss (bei x86_64 werden die ersten sechs Parameter über
 * Register übergeben).
 */
/*void toc_settle (struct toc* regs, void* tos, void (*kickoff)(void*, void*,
        void*, void*, void*, void*, void*), void* object);*/

/*
 * Diese Funktion lädt die nicht-flüchtigen Prozessorregister mit den Inhalten
 * der Struktur regs.
 */
void toc_go (struct toc* regs);

/*
 * Diese Funktion führt einen Kontextwechsel durch. Dazu müssen die aktuellen
 * Registerwerte in regs_now gesichert und durch die Werte von regs_then
 * ersetzt werden.
 */
void toc_switch (struct toc* regs_now, struct toc* regs_then);


#endif
