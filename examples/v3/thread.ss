; This program will perform multitasking
; Some Assembler Tuning(Nessicary)
&&_Assembler:
   v_size: 1000
   start_index: 0
; ------------------------------
%func routine1
%func main

~main:
     call routine1
     ret

     ;*****************************
     ;SUBROUTINE 1                *
     ;func :  do some simple math *
     ;out  :  output result	  *
     ;*****************************
~routine1:
     thread_t 0                   ; create new thread on stack
     mov i1 11                    ; ref reg 10 as int 
     r_mv sdx 10                  ; get thread stack number
     printf 17 "created thread " + (r,10) + "\n" ; print thread number
     thread_t 1                   ; start created thread
     ; Thread Cap---------!!Must destroy thread when done!!-----
         mult eax[ 582,284 ]
         r_mv eax 10
         printf 1 (r,10)           ; print 582 * 284
     thread_t 4                    ; destroy thread
     ret

call main

halt
