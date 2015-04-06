; This program will turn on 3 les's in sequence using gpio pins 4, 27, & 22
; I didn't feel like making this shit fancy w/ functions and what not
; Some Assembler Tuning(Nessicary)
&&_Assembler:
   v_size: 1000
   start_index: 0
; ------------------------------
mov sdx 4
mov sfc 2
invoke 0x6     ; export pin 4

mov sdx 27
invoke 0x6     ; export pin 27

mov sdx 22
invoke 0x6     ; export pin 22

mov tmp 1
mov sfc 0
invoke 0x6     ; set direction pin 22 -> out

mov sdx 27
invoke 0x6     ; set direction pin 27 -> out

mov sdx 4
invoke 0x6     ; set direction pin 4 -> out

mov scx 1      ; sleep for 1 second

; ***************************************
; Led Subroutine                        *
; light led1(4), led2(27), and led3(22) *
; ***************************************
loop r100 r101 5        ; loop 5 times
   mov sfc 1

   mov sdx 4
   mov tmp 1
   invoke 0x5       ; turn on pin 4
   sleep

   mov sdx 4
   mov tmp 0
   invoke 0x5       ; turn off pin 4
   mov sdx 27
   mov tmp 1
   invoke 0x5       ;  turn on pin 27
   sleep

   mov sdx 27
   mov tmp 0
   invoke 0x5       ; turn off pin 27
   mov sdx 22
   mov tmp 1
   invoke 0x5       ;  turn on pin 22
   sleep

   mov sdx 22
   mov tmp 0
   invoke 0x5       ; turn off pin 22
endl r100 r101
; *************************************

mov sdx 4
mov sfc 1
invoke 0x6     ; unexport pin 4

mov sdx 27
invoke 0x6     ; unexport pin 27

mov sdx 22
invoke 0x6     ; unexport pin 22

halt
