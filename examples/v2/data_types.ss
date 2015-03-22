; This program simply shows all scorpion's primative data types
; High level Example =================================
; dataTypes.sc
;
; int main()
; {
;    short a;
;    int b;
;    float c;
;    double d;
;   return 0;
; }
;

reg 0 main
reg 1 a
reg 2 b
reg 3 c
reg 4 d

%func main

push main
   sload a null          ; short
   loadi b null          ; int
   loadf c null          ; float
   dload d null          ; double
return main

call main

rm a
rm b
rm c
rm d
rm main  // destroy func

halt
