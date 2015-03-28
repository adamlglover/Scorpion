reg 0 main
reg 1 i
reg 2 for
reg 3 max

%func main

push main
   mov lsl 7
   invoke 1
   loadi i 0
   loadi for 0
   loadi max 10
   loadr for ip
   ilt i max
     printf 6 "i = " + (r,i) + "\n"
     inc i
     loadr ip for
   end
return main

call main

halt
