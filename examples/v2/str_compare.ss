; This program will compare the user input with a string

reg 0 main
reg 1 inputLength
reg 2 c_length
reg 3 currChar
reg 4 handleText
reg 5 consoleRead
reg 6 compare
reg 7 word
reg 8 usrWord
reg 9 zero
reg 10 areEqual

%func main
%func compare
%func consoleRead

loadbl areEqual false
loadi inputLength 0                                   ; set the inital length of the console input
loadi c_length 0                                      ; set a counter for interating
loadbl handleText true
loadi zero 0
loadi word 500                                           ; set word to the ascii equavilent of(72+101+108+108+111) or("Hello")
loadi usrWord 0

push consoleRead
   print 13 "Enter Hello: "
   rln inputLength 100 10
   loadi currChar 100                                    ; set start index of char string(in ram)
return consoleRead

push compare
   wloop handeText r20
      inc c_length
      same handleText c_length,inputLength               ; check if curr index == input length
      neg handleText                                      ; invert bool

      loadi_r usrWord curr_char                           ; add a char to user typed word
      inc curr_char                                       ; inc reg to print next char(if available)
   endwl handleText r20
return compare

push main
   call consoleRead
   call compare

   same areEqual word usrWord
   do areEqual
     print 15 "You typed Hello"
   end
   ndo areEqual
     print 22 "You did not type Hello"
   end
return main

call main

halt

