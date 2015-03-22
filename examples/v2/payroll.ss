; This program will calculate a person's payroll
; High Level Example ====================================
; payroll.sc
;
; #include <stdio>  // printf method
;
; int main()
; {
;    int hours = 40;
;    double grosspay, payRate = 25.0;
;
;    grosspay = hours * payRate;
;    printf("Your gross pay is $%s", grosspay);
;    return 0;
; }
;

reg 0 main
reg 1 hours
reg 2 grosspay
reg 3 payRate

%func main

push main
  loadi hours 40
  dload grosspay null
  dload payRate 25.0

  mult grosspay hours,payRate
  printf 20 "Your gross pay is $" + (r,grosspay)
return main

call main

halt
