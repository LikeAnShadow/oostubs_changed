; $Id: toc.asm 9719 2018-12-05 09:57:29Z df $

;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
    ; lade alle register
    ; offsets aus toc.inc übernehmen
    mov rax, rdi

    mov rbx, [rax+rbx_offset]
    mov r12, [rax+r12_offset]
    mov r13, [rax+r13_offset]
    mov r14, [rax+r14_offset]
    mov r15, [rax+r15_offset]
    mov rbp, [rax+rbp_offset]
    mov rsp, [rax+rsp_offset]

    ret
    ; fertig



; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
    ; erst register sichern
    mov rdx, rdi

    mov [rdx+rbx_offset], rbx
    mov [rdx+r12_offset], r12
    mov [rdx+r13_offset], r13
    mov [rdx+r14_offset], r14
    mov [rdx+r15_offset], r15
    mov [rdx+rbp_offset], rbp
    mov [rdx+rsp_offset], rsp

    mov rax, rsi

    ; dann register laden
	mov rbx, [rax+rbx_offset]
	mov r12, [rax+r12_offset]
	mov r13, [rax+r13_offset]
	mov r14, [rax+r14_offset]
	mov r15, [rax+r15_offset]
	mov rbp, [rax+rbp_offset]
	mov rsp, [rax+rsp_offset]

	ret
	; fertig
