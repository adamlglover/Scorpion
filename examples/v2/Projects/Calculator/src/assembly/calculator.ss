;fncs.ss
reg 200000 _print
reg 200001 _print_b
reg 200002 GetUserInput
reg 200003 GetUserInput_b
reg 200004 GetMatmaticialOpr
reg 200005 GetMatmaticialOpr_b
reg 200006 GetUserInput
reg 200007 GetUserInput_b
reg 200008 CalculateResult
reg 200009 CalculateResult_b

%func _print
$func GetUserInput
%func GetMatmaticialOpr
%func GetUserInput
%func CalculateResult

loadi _print_b 0
loadi GetUserInput_b 0
loadi GetMatmaticialOpr_b 0
loadi GetUserInput_b 0
loadi CalculateResult_b 0
;----------------

; io.ss
push _print
   loadr _print_b ip
   print 41  "========================================="
   printf 33 "      |  |  |  ANSWER : " + (r,txt) + " |  |  |"
   print 41  "========================================="
     
   rm txt
return _print
;----------------

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

; brain.ss

reg 1000 hasInp1
loadbl hasInp1 false
reg 1001 inp1
reg 1002 inp2
loadi inp1 203
neg inp1
loadi inp2 203
neg inp2
reg 1003 chOp
loadc chOp '-'
reg 1004 CalculateResult_return

push CalculateResult
   loadr CalculateResult_b ip
   loadi CalculateResult_return 0
   reg 100001 tmpb
   loadbl tmpb false
   reg 100000 tmpc
   loadc tmpc '*'
   same tmpb op,tmpc

   do tmpb
    mult CalculateResult_return inpt1,inpt2
    rm tmpb
    rm tmpc
    rm op
    rm inpt1
    rm inpt2
    return CalculateResult 1                            ; skip return if not true
   end

   loadc tmpc '-'
   same tmpb op,tmpc

   do tmpb
    sub CalculateResult_return inpt1,inpt2
    rm tmpb
    rm tmpc
    rm op
    rm inpt1
    rm inpt2
    return CalculateResult 1                            ; skip return if not true
   end
  
   loadc tmpc '+'
   same tmpb op,tmpc

   do tmpb
    add CalculateResult_return inpt1,inpt2
    rm tmpb
    rm tmpc
    rm op
    rm inpt1
    rm inpt2
    return CalculateResult 1                            ; skip return if not true
   end
 
  loadc tmpc '/'
   same tmpb op,tmpc

   do tmpb
    div CalculateResult_return inpt1,inpt2
    rm tmpb
    rm tmpc
    rm op
    rm inpt1
    rm inpt2
    return CalculateResult 1                            ; skip return if not true
   end
  
   loadc tmpc '%'
   same tmpb op,tmpc

   do tmpb
    rem CalculateResult_return inpt1,inpt2
    rm tmpb
    rm tmpc
    rm op
    rm inpt1
    rm inpt2
    return CalculateResult 1                            ; skip return if  not true
   end

   loadi CalculateResult_return 0
return CalculateResult

push GetUserInput  
   loadr GetUserInput_b ip
   print 16 "Type a number : "
   ndo hasInp1
     loadi hasInp1 true
     ; Parse input
     reg 100000 inputLength
     loadi inputLength 0
     rln inputLength 990000 10                      ; recieve input and create an input buffer of 10,000 chars

     ; Parse to int
     reg 100002 max_size
     loadi max_size 10
     reg 100003 index
     loadi index 0
     reg 100004 handle_txt
     loadbl handle_txt false
     iltoeq inputLength max_size                             ; inputLength <= 10

         loadi index 0
         same handle_txt index,inputLength                   ; if inputLength == 0
         do handle_txt
                ; err plz type something
            print 5 "Err "
            loadr ip GetUserInput_b
         end
         loadi index 1
         same handle_txt index,inputLength                   ; if inputLength == 1
         do handle_txt
             ct_int inp1 r990000                             ; convert the char from input buffer into int
         end

         loadi index 2
         same handle_txt index,inputLength                   ; if inputLength == 2
         do handle_txt
             ct_int inp1 r990000                             ; convert the char from input buffer into int
             reg 100004 tmp
             ct_int tmp r990001                              ; convert the char from input buffer into int and store value in temp location
             anum inp1 tmp                                   ; append the number in tmp to end of inp1
         end

         loadi index 3
         same handle_txt index,inputLength                   ; if inputLength == 3
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
         end

         loadi index 4
         same handle_txt index,inputLength                   ; if inputLength == 4
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
         end

         loadi index 5
         same handle_txt index,inputLength                   ; if inputLength == 5
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
             ct_int tmp r990004
             anum inp1 tmp
         end
 
         loadi index 6
         same handle_txt index,inputLength                   ; if inputLength == 6
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
             ct_int tmp r990004
             anum inp1 tmp
             ct_int tmp r990005
             anum inp1 tm
         end
   
         loadi index 7
         same handle_txt index,inputLength                   ; if inputLength == 7
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
             ct_int tmp r990004
             anum inp1 tmp
             ct_int tmp r990005
             anum inp1 tm
             ct_int tmp r990006
             anum inp1 tm
         end

         loadi index 8
         same handle_txt index,inputLength                   ; if inputLength == 8
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
             ct_int tmp r990004
             anum inp1 tmp
             ct_int tmp r990005
             anum inp1 tm
             ct_int tmp r990006
             anum inp1 tm
	     ct_int tmp r990007
             anum inp1 tm
         end

         loadi index 9
         same handle_txt index,inputLength                   ; if inputLength == 9
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
             ct_int tmp r990004
             anum inp1 tmp
             ct_int tmp r990005
             anum inp1 tm
             ct_int tmp r990006
             anum inp1 tm
             ct_int tmp r990007
             anum inp1 tm
             ct_int tmp r990008
             anum inp1 tm
         end

         loadi index 10
         same handle_txt index,inputLength                   ; if inputLength == 10
         do handle_txt
             ct_int inp1 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp1 tmp
             ct_int tmp r990002
             anum inp1 tmp
             ct_int tmp r990003
             anum inp1 tmp
             ct_int tmp r990004
             anum inp1 tmp
             ct_int tmp r990005
             anum inp1 tm
             ct_int tmp r990006
             anum inp1 tm
             ct_int tmp r990007
             anum inp1 tm
             ct_int tmp r990008
             anum inp1 tm
             ct_int tmp r990009
             anum inp1 tm
         end
        ; destroy teporary variables
        rm inputLength
        rm max_size
        rm index
        rm tmp
        rm handle_txt
     end
     inltoeq inputLength max_size                             ; !(inputLength <= 10)
        ; Woah, I can't calculate that! int_max: 2.14748e+09
        print 51 "Woah, I can't calculate that! int_max: 2.14748e+09\n"
        loadr ip GetUserInput_b
     end
   end
   do hasInp1
     loadbl hasInp1 false
     ; Parse input
     reg 100000 inputLength
     loadi inputLength 0
     rln inputLength 990000 10                      ; recieve input and create an input buffer of 10,000 chars

     ; Parse to int
     reg 100002 max_size
     loadi max_size 10
     reg 100003 index
     loadi index 0
     reg 100004 handle_txt
     loadbl handle_txt false
     iltoeq inputLength max_size                             ; inputLength <= 10

         loadi index 0
         same handle_txt index,inputLength                   ; if inputLength == 0
         do handle_txt
                ; err plz type something
            print 5 "Err "
            loadr ip GetUserInput_b
         end
         loadi index 1
         same handle_txt index,inputLength                   ; if inputLength == 1
         do handle_txt
             ct_int inp2 r990000                             ; convert the char from input buffer into int
         end

         loadi index 2
         same handle_txt index,inputLength                   ; if inputLength == 2
         do handle_txt
             ct_int inp2 r990000                             ; convert the char from input buffer into int
             reg 100004 tmp
             ct_int tmp r990001                              ; convert the char from input buffer into int and store value in temp location
             anum inp2 tmp                                   ; append the number in tmp to end of inp1
         end

         loadi index 3
         same handle_txt index,inputLength                   ; if inputLength == 3
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
         end

         loadi index 4
         same handle_txt index,inputLength                   ; if inputLength == 4
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
         end

         loadi index 5
         same handle_txt index,inputLength                   ; if inputLength == 5
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
             ct_int tmp r990004
             anum inp2 tmp
         end

         loadi index 6
         same handle_txt index,inputLength                   ; if inputLength == 6
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
             ct_int tmp r990004
             anum inp2 tmp
             ct_int tmp r990005
             anum inp2 tm
         end

         loadi index 7
         same handle_txt index,inputLength                   ; if inputLength == 7
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
             ct_int tmp r990004
             anum inp2 tmp
             ct_int tmp r990005
             anum inp2 tm
             ct_int tmp r990006
             anum inp2 tm
         end

         loadi index 8
         same handle_txt index,inputLength                   ; if inputLength == 8
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
             ct_int tmp r990004
             anum inp2 tmp
             ct_int tmp r990005
             anum inp2 tm
             ct_int tmp r990006
             anum inp2 tm
             ct_int tmp r990007
             anum inp2 tm
         end

         loadi index 9
         same handle_txt index,inputLength                   ; if inputLength == 9
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
             ct_int tmp r990004
             anum inp2 tmp
             ct_int tmp r990005
             anum inp2 tm
             ct_int tmp r990006
             anum inp2 tm
             ct_int tmp r990007
             anum inp2 tm
             ct_int tmp r990008
             anum inp2 tm
         end

         loadi index 10
         same handle_txt index,inputLength                   ; if inputLength == 10
         do handle_txt
             ct_int inp2 r990000
             reg 100004 tmp
             ct_int tmp r990001
             anum inp2 tmp
             ct_int tmp r990002
             anum inp2 tmp
             ct_int tmp r990003
             anum inp2 tmp
             ct_int tmp r990004
             anum inp2 tmp
             ct_int tmp r990005
             anum inp2 tm
             ct_int tmp r990006
             anum inp2 tm
             ct_int tmp r990007
             anum inp2 tm
             ct_int tmp r990008
             anum inp2 tm
             ct_int tmp r990009
             anum inp2 tm
         end
     end
     inltoeq inputLength max_size                             ; !(inputLength <= 10)
        ; Woah, I can't calculate that! int_max: 2.14748e+09
        print 51 "Woah, I can't calculate that! int_max: 2.14748e+09\n"
        loadr ip GetUserInput_b
     end
        ; destroy teporary variables
        rm inputLength
        rm max_size
        rm index
        rm tmp
        rm handle_txt
   end

   reg 100006 inpt1
   reg 100007 inpt2
   reg 100008 op
   loadi inpt1 0
   loadi inpt2 0
   loadr inpt1 inp1
   loadr inpt2 inp2
   loadc op '-'
   loadr op chOp
   loadr CalculateResult  CalculateResult_b
   call CalculateResult

   reg 100008 txt
   loadi txt 0
   loadr txt CalculateResult_return
   loadr _print _print_b
   call _print
return GetUserInput

push check
   loadr check_b ip
   reg 100001 foundOp
   loadbl foundOp false
   reg 100002 tmpb
   loadbl tmpb false
   reg 100003 tmpc
   loadc tmpc '+'
   same tmpb chOp,tmpc

   do tmpb
    loadbl foundOp true
   end

   loadc tmpc '-'
   same tmpb chOp,tmpc

   do tmpb
    loadbl foundOp true
   end

   loadc tmpc '*'
   same tmpb chOp,tmpc

   do tmpb
    loadbl foundOp true
   end

   loadc tmpc '/'
   same tmpb chOp,tmpc

   do tmpb
    loadbl foundOp true
   end

   loadc tmpc '%'
   same tmpb chOp,tmpc

   do tmpb
    loadbl foundOp true
   end

   ndo foundOp
     print 6 "Err : "
     loadr GetMatmaticialOpr GetMatmaticialOpr_b
     call GetMatmaticialOpr
   end
   rm foundOp
   rm tmpb
   rm tmpc
return check

push GetMatmaticialOpr
  loadr GetMatmaticialOpr_b ip
  print 46 "Please type an operator (*, +, -, %, or /)  : "
     reg 100000 inputLength
     loadi inputLength 0
     rln inputLength 990000 10                      ; recieve input and create an input buffer of 10,000 chars
     rm inputLength                                 ; we immediatley delete this varible because we do not need it

     ; recieve 1st char from input buffer
     loadr chOp r990000

     loadr check check_b
     call check
return GetMatmaticialOpr
; ---------------

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
