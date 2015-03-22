: This program will close the program with a certain code
; High Level Example ====================================
; prog_exit.sc
;
; int main()
; {
;    return 6;
; }
;

reg 0 main

%func main

push main
   mov ebx 6                 ; set return value
return main

call main

halt
