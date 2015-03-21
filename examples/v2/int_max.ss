; This program will calculate the max value of an integer
reg 0 max
ivar overload 3000000000

loadi max overload                          ; overload the integer value

printf 17 "int max_length: " + (r,max)      ; print the max integer value

halt
