; Simple GPIO code

%include <GPIO/basic-gpio> ; basic gpio lib

.main:
   mov lsl 7
   invoke 0x1 0
   loadi PIN,4
   loadi WAIT,1       
   call gpio_out
   ret

call main

halt