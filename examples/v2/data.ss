; This program will simply print some data values to the console;
; High Level Example ====================================
; data.sc
;
; #include <stdio>  // printf()
;
; int main()
; {
;
;    int a = null;
;    bool b = true;
;    printf("%s \n %s", a, b); 
;
;   return 0;
; }
;

reg 0 main
reg 1 a 
reg 2 b

%func main

push main
  loadi a null
  loadbl b true
  printf 3 (r,a) + "\n" + (r,b)
return main

call main

halt
