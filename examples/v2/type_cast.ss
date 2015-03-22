; This program will type cast a integer to a double

; High Level Example =============================
; type_cast.sc
; #include <stdio> // printf method
;
; double a = 5.3;
;
; int main()
; {
;   int b = (int) a;     // type cast a double to an integer
;   printf("Var b is: %s\n    ", b);
;   printf("a is: %s", a);
;   return 0;
; }
;

reg 0 main
reg 1 a
reg 2 b

dload a 5.3

%func main

push main
   loadi b 0                                  ; must initalize variable b
   t_cast a 0                                 ; cast double a; as int
   loadr b a                                  ; store b <- a
   t_cast a 1                                 ; convert double a; back to double
   printf 16 "Var b is: " + (r,b) + "\n    "  ; print result
   printf 7 "a is: " + (r,a)
return main

call main

halt
