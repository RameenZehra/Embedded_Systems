;====================================================================
; Main.asm file generated by New Project wizard
;
; Created:   Wed Nov 3 2021
; Author: Rameen Zehra
; Processor: AT89C51
; Compiler:  ASEM-51 
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
      jmp   Start; jump to main

;====================================================================
; CODE SEGMENT
;====================================================================

      org   101h; main
Start:	
      ; Write your code here    
      mov P2, #13H;  P2= 0001 0011(binary)
    
      mov P2, #45H ; P2=0100 0101 (binary);
      
      jmp start ; jump to main

;====================================================================
      END
