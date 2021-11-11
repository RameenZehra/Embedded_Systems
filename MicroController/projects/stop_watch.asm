;====================================================================
; Main.asm file generated by New Project wizard
;
; Created:   Wed Nov 3 2021
; Processor: AT89C51
; Compiler:  ASEM-51 (Proteus)
;====================================================================

$NOMOD51
$INCLUDE (8051.MCU)

;====================================================================
; DEFINITIONS
;====================================================================

;====================================================================
; VARIABLES
;====================================================================

;====================================================================
; RESET and INTERRUPT VECTORS
;====================================================================

      ; Reset Vector
      org   0000h
      jmp 101H ; jump to main
     
     org 0003h; ISR EXT0 INTERRUPT STARTS
    loop2:
	  ;mov P2, SP;  display will show where the stack pointer is pointing to
	   INC P2; P2=P2+1;
	   JB P0.0, forced_exit ;Jump to forced_exit if (P0.0 == 0) 
	   jmp loop2; jump to loop2 if (P0.0 !== 0)
   forced_exit:
	    mov P2, #7FH; P2=0111 1111(binary)
	    RETI; return from interrupt0
 
      org 0013h; ISR EXT1 INTERRUPT STARTS
      MOV P2,  #00h; P2=0
      RETI; return from interrupt1
      
     org 101h ;main
 start:
       SETB TCON.2; TCON's bit 2 set to make external interrupt 1 generate on falling edge
       SETB TCON.0; TCON's bit 0 set to make external interrupt 0 generate on falling edge

	CLR  A ; our counter
	mov P1,   #00h; our display
        mov P2,   #00h; our display
	;mov P3,   #00h; ;;;;;;;;;; WHY DOING THIS STOPS INTERRUPTS FROM GENERATING????????? TODO

	mov IP, #00H; all interrupts have low priority
	;mov IP, #04H; ext1 high
	mov IE, #85H ; enable external interrupts
	


 loop:
      jmp loop
;====================================================================
      END
      
     


