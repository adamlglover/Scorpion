include "io.ss"
include "prog.ss"
include "brain.ss"

reg 200030 bueatify

%func bueatify
reg 1050 bueatify_b
loadi bueatify_b 0

push bueatify
   loadr bueatify_b ip
   print 41 "========================================="
   print 31 "            Scorpion CALCULATOR"
   print 41 "========================================="
return bueatify

%func main
reg 1052 main_b
loadi main_b 0

push main
   loadr main_b ip
   
   call bueatify
   loadr bueatify bueatify_b

   call GetUserInput
   loadr GetUserInput GetUserInput_b

   call GetMatmaticialOpr
   loadr GetMatmaticialOpr GetMatmaticialOpr_b

   call GetUserInput
   loadr GetUserInput GetUserInput_b

   call ck_p
   loadr ck_p ck_p_b

return main
