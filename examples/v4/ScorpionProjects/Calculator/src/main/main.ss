; This Is a Calculator designed to show the power of scorpion

%include 'C:\Users\Braxton\ScorpionProjects\Calculator\src\prog.ss'
%include 'C:\Users\Braxton\ScorpionProjects\Calculator\src\brain.ss'
%include 'C:\Users\Braxton\ScorpionProjects\Calculator\src\io.ss' 

loadi bueatify_b 0

.bueatify:
    r_mv ip bueatify_b
    print 42 '=========================================/n'
    print 32 '            Scorpion CALCULATOR/n'
    print 42 '=========================================/n'
    ret

loadi main_b 0

.main:
   r_mv ip main_b
   
   
   mov i1 11
   call bueatify
   cp bueatify bueatify_b

   
   mov i1 11
   call GetUserInput
   cp GetUserInput GetUserInput_b

   
   mov i1 11
   call GetMatmaticialOpr
   cp GetMatmaticialOpr GetMatmaticialOpr_b

   
   mov i1 11
   call GetUserInput
   cp GetUserInput GetUserInput_b

   
   mov i1 11
   call ck_p
   cp ck_p ck_p_b
   ret

call main

halt

