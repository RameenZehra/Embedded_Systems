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
      jmp 101H ; 
     
     org 0003h; ISR EXT0 INTERRUPT INCREASE
            PUSH ACC ; PUSH accumulator on stack
	    Mov A, #100; A=100
	    SUBB A, R0; A= A-R0
	    JZ Exit_INC_ISR ; Jump on Exit_INC_ISR if A=0
	    Mov A, R0; A=R0
	    ADD A, #10; A=A+10
	    Mov R0, A ; R0=A
	    
 Exit_INC_ISR:
            POP ACC ; POP  accumulator from stack
	    RETI; Return form Interrupt0
	    
       org 0013h ; ISR EXT1 INTERRUPT DECREASE
          PUSH ACC ; PUSH accumulator on stack
	   MOV A, R0; A = R0
	   JZ EXIT_DECR_ISR; Jump on Exit_DEC_ISR if A=0
	   SUBB A, #10;  A=A-10;
	   MOV R0, A ; R0=A
	   
EXIT_DECR_ISR:
        POP ACC ; POP  accumulator from stack
	 RETI ; Return form Interrupt1
 
      
     org 101h ; MIAN
 start:
       SETB TCON.2; TCON's bit 2 set to make external interrupt 1 generate on falling edge
       SETB TCON.0; TCON's bit 0 set to make external interrupt 0 generate on falling edge

       mov IP, #00H; all interrupts have low priority
       mov IE, #85H ; enable external interrupts
	
	mov R0, #50 ; R0 --> our brightness
	mov R1, #0 ;  R1 --> count
	
high_loop_start:
        setb P0.1; SET Port0 Pin1 to high  (1us)
	mov A, R0;  A=R0 (1us)
	SUBB A, R1; A= A - R1 (1us)
	JNZ high_loop; Jump if  A!=0 (2us)
	jmp low_loop_start; Jump on low_loop start if A=0
high_loop:
	 NOP; No operation(1us)
	 INC R1; R1=R1+1 (1us)
	 jmp high_loop_start; Jump on high_loop start (2us)
low_loop_start:
         clr P0.1 ;CLEAR Port0 Pin1 to 0  (1us)
	 MOV A, #100;A=100
	 SUBB A, R1; A=A-R1
	 JNZ low_loop ; Jump if  A!=0 (2us)
	 Mov R1, #0 ; R1=0
	 jmp high_loop_start ; Jump on  high_loop_start
low_loop:
         NOP;No operation(1us)
	 INC R1 ; R1=R1+1
	 jmp low_loop_start; Jump on low_loop start 
	 

 loop:
      jmp loop
;====================================================================
      END
      
     


