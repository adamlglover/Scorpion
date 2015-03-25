; io.ss
push _print
   loadr _print_b ip
   print 41  "========================================="
   printf 33 "      |  |  |  ANSWER : " + (r,txt) + " |  |  |"
   print 41  "========================================="
     
   rm txt
return _print
;--------

reg 1031 response
reg 1032 end_prog

loadc response '0'
%func main

reg 1033 end_prog_return
loadi end_prog_return 0
%func end_prog
push end_prog
   loadr end_prog ip
   print 41 "-----------------------------------------"
   print 31 "           ($---- EXIT ? ----$)"
   print 41 "-----------------------------------------"
   reg 100000 inputLength
     loadi inputLength 0
     rln inputLength 990000 10                      ; recieve input and create an input buffer of 10,000 chars
     rm inputLength                                 ; we immediatley delete this varible because we do not need it

     ; recieve 1st char from input buffer
     loadr response r990000

     reg 100000 limit
     loadi limit 1
     iltoeq response limit
        loadi limit 1
        loadbl r100001 limit,response
        do r100001
         loadi end_prog_return 1
         return end_prog 1
        end

        loadi limit 0
        loadbl r100001 limit,response
        do r100001
         loadi end_prog_return 0
         return end_prog 1
        end
     end
     inltoeq response limit
        loadi end_prog_return 0
         return end_prog 1
     end
     
    rm inputLength
    rm limit
    rm r100001    ; destroy bool variable
return end_prog

; Prog.ss
push ck_p
   loadr ck_p_b ip
   reg 100000 r
   loadi r 0
   loadr r end_prog_return
   
   loadi r100002 0            ; target num
   loadbl r100001 false
   same r100001 r r100002
   do r100001
     loadr main main_b
     call main                ; main();
   end

   loadi r100002 1            ; target num
   same r100001 r r100002
   do r100001
     ; close prog
     halt
   end
  
   loadi r100002 1            ; target num 
   same r100001 r r100002
   ndo r100001                  ; if(r != 1 || r != 0) halt
     loadi r100002 0            ; target num
     same r100001 r r100002
     ndo r100001
       ; err close
       halt
     end
   end

return ck_p
; ---------------

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
