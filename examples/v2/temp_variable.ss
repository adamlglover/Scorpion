; This program will show how tempory variable are handled by the VM
; High Level Example ==============================
; temp_variable.sc
;
; int main()
; {
;    int a = 5;
;    return 0; // destroy a
; }
;

reg 0 main
reg 1 a

%func main

push main
   loadi a 5
return main

call main

rm a               ; a is destroyed

halt
