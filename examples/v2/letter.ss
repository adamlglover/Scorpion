; This program will simply read input from the console and print out what was inputed

reg 0 input_length
reg 3 c_length
reg 1 handle_txt
reg 5 curr_char

loadi input_length 0                                  ; set the inital length of the console input
loadi c_length 0                                      ; set a counter for interating
print 17 "Enter some text: "
rln input_length 100 10                               ; read input from console(readln) and set excape seq
loadi curr_char 100                                   ; set start index of char string(in ram)

loadbl handle_txt true 
print 13 "You entered: "
wloop handle_txt r2
  inc c_length
  same handle_txt c_length,input_length               ; check if curr index == input length
  neg handle_txt                                      ; invert bool
  
  printf 1 (crr,curr_char)                            ; print char
  inc curr_char                                       ; inc reg to print next char(if available)
endwl handle_txt r2

halt
