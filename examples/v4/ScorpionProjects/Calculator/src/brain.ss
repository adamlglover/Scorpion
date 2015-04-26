loadbl hasInp1 0
loadc chOp '-'

.CalculateResult:
   r_mv ip CalculateResult_b
   loadi CalculateResult_return 0
   loadbl tmpb 0
   loadc tmpc '*'
   mov i1 14
   same tmpb op tmpc

   do tmpb
    mult CalculateResult_return inpt1 inpt2
    return CalculateResult 1                            ; skip return if not true
   end

   loadc tmpc '-'
   mov i1 14
   same tmpb op tmpc

   do tmpb
    sub CalculateResult_return inpt1 inpt2
    return CalculateResult 1                            ; skip return if not true
   end
  
   loadc tmpc '+'
   mov i1 14
   same tmpb op tmpc

   do tmpb
    add CalculateResult_return inpt1 inpt2
    printf 'inpt1 = <v,inpt1> inpt2 = <v,inpt2> CalculateResult_return = <v,CalculateResult_return>'
    return CalculateResult 1                            ; skip return if not true
   end
 
  loadc tmpc '\'
   mov i1 14
   same tmpb op tmpc

   do tmpb
    div CalculateResult_return inpt1 inpt2
    return CalculateResult 1                            ; skip return if not true
   end
  
   loadc tmpc '%'
   mov i1 14
   same tmpb op tmpc

   do tmpb
    rem CalculateResult_return inpt1 inpt2
    return CalculateResult 1                            ; skip return if  not true
   end

   loadi CalculateResult_return 0
   ret

.GetUserInput:
   r_mv ip GetUserInput_b
   print 'Type a number : '
   mov i1 14
   ndo hasInp1
     ; Parse input
     loadi inputLength 0
     rln inputLength 990000 '/n'                      ; recieve input and create an input buffer of 10,000 chars

     ; Parse to int
     loadi max_size 10
     loadi index 0
     loadbl handle_txt 0
     ile inputLength max_size                             ; inputLength <= 10

         loadi index 0
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 0
         do handle_txt
                ; err plz type something
            print 'Err : '
            mov i1 11
            rmov sdx GetUserInput_b
            invoke 0xA 0
         end
         loadi index 1
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 1
         do handle_txt
             mov i1 11
             ct_int inp1 @990000                             ; convert the char from input buffer into int
			 loadi hasInp1 1
			 return GetUserInput 1
         end

         loadi index 2
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 2
         do handle_txt
             mov i1 11
             ct_int inp1 @990000                             ; convert the char from input buffer into int
             ct_int tmpi @990001                              ; convert the char from input buffer into int and store value in temp location
             anum inp1 tmpi                                   ; append the number in tmp to end of inp1
			 return GetUserInput 1
         end

         loadi index 3
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 3
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
			 return GetUserInput 1
         end

         loadi index 4
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 4
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
			 return GetUserInput 1
         end

         loadi index 5
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 5
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
             ct_int tmpi @990004
             anum inp1 tmpi
         end
 
         loadi index 6
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 6
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
             ct_int tmpi @990004
             anum inp1 tmpi
             ct_int tmpi @990005
             anum inp1 tmpi
         end
   
         loadi index 7
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 7
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
             ct_int tmpi @990004
             anum inp1 tmpi
             ct_int tmpi @990005
             anum inp1 tmpi
             ct_int tmpi @990006
             anum inp1 tmpi
         end

         loadi index 8
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 8
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
             ct_int tmpi @990004
             anum inp1 tmpi
             ct_int tmpi @990005
             anum inp1 tmpi
             ct_int tmpi @990006
             anum inp1 tmpi
	         ct_int tmpi @990007
             anum inp1 tmpi
         end

         loadi index 9
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 9
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
             ct_int tmpi @990004
             anum inp1 tmpi
             ct_int tmpi @990005
             anum inp1 tmpi
             ct_int tmpi @990006
             anum inp1 tmpi
             ct_int tmpi @990007
             anum inp1 tmpi
             ct_int tmpi @990008
             anum inp1 tmpi
         end

         loadi index 10
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 10
         do handle_txt
             mov i1 11
             ct_int inp1 @990000
             ct_int tmpi @990001
             anum inp1 tmpi
             ct_int tmpi @990002
             anum inp1 tmpi
             ct_int tmpi @990003
             anum inp1 tmpi
             ct_int tmpi @990004
             anum inp1 tmpi
             ct_int tmpi @990005
             anum inp1 tmpi
             ct_int tmpi @990006
             anum inp1 tmpi
             ct_int tmpi @990007
             anum inp1 tmpi
             ct_int tmpi @990008
             anum inp1 tmpi
             ct_int tmpi @990009
             anum inp1 tmpi
         end
     end
     inle inputLength max_size                             ; !(inputLength <= 10)
            ; Woah, I can't calculate that! int_max: 2.14748e+09
            print 'Woah, I can/'t calculate that! int_max: 2.14748e+09/n'
            rmov sdx GetUserInput_b
            invoke 0xA 0
     end
	 
   end
   mov i1 14
   do hasInp1
     ; Parse input
     loadi inputLength 0
     rln inputLength 990000 '/n'                      ; recieve input and create an input buffer of 10,000 chars

     ; Parse to int
     loadi max_size 10
     loadi index 0
     loadbl handle_txt 0
     ile inputLength max_size                             ; inputLength <= 10

         loadi index 0
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 0
         do handle_txt
                ; err plz type something
            print 'Err : '
            mov i1 11
            rmov sdx GetUserInput_b
            invoke 0xA 0
         end
         loadi index 1
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 1
         do handle_txt
             mov i1 11
             ct_int inp2 @990000                             ; convert the char from input buffer into int
			 loadi hasInp1 0
         end

         loadi index 2
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 2
         do handle_txt
             mov i1 11
             ct_int inp2 @990000                             ; convert the char from input buffer into int
             ct_int tmpi @990001                              ; convert the char from input buffer into int and store value in temp location
             anum inp2 tmpi                                   ; append the number in tmp to end of inp1
         end

         loadi index 3
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 3
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
			 return GetUserInput 1
         end

         loadi index 4
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 4
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
			 return GetUserInput 1
         end

         loadi index 5
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 5
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
             ct_int tmpi @990004
             anum inp2 tmpi
         end

         loadi index 6
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 6
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
             ct_int tmpi @990004
             anum inp2 tmpi
             ct_int tmpi @990005
             anum inp2 tmpi
         end

         loadi index 7
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 7
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
             ct_int tmpi @990004
             anum inp2 tmpi
             ct_int tmpi @990005
             anum inp2 tmpi
             ct_int tmpi @990006
             anum inp2 tmpi
         end

         loadi index 8
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 8
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
             ct_int tmpi @990004
             anum inp2 tmpi
             ct_int tmpi @990005
             anum inp2 tmpi
             ct_int tmpi @990006
             anum inp2 tmpi
             ct_int tmpi @990007
             anum inp2 tmpi
         end

         loadi index 9
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 9
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
             ct_int tmpi @990004
             anum inp2 tmpi
             ct_int tmpi @990005
             anum inp2 tmpi
             ct_int tmpi @990006
             anum inp2 tmpi
             ct_int tmpi @990007
             anum inp2 tmpi
             ct_int tmpi @990008
             anum inp2 tmpi
         end

         loadi index 10
         mov i1 14
         same handle_txt index inputLength                   ; if inputLength == 10
         do handle_txt
             mov i1 11
             ct_int inp2 @990000
             ct_int tmpi @990001
             anum inp2 tmpi
             ct_int tmpi @990002
             anum inp2 tmpi
             ct_int tmpi @990003
             anum inp2 tmpi
             ct_int tmpi @990004
             anum inp2 tmpi
             ct_int tmpi @990005
             anum inp2 tmpi
             ct_int tmpi @990006
             anum inp2 tmpi
             ct_int tmpi @990007
             anum inp2 tmpi
             ct_int tmpi @990008
             anum inp2 tmpi
             ct_int tmpi @990009
             anum inp2 tmpi
         end
     end
     inle inputLength max_size                             ; !(inputLength <= 10)
            ; Woah, I can't calculate that! int_max: 2.14748e+09
            print 'Woah, I can/'t calculate that! int_max: 2.14748e+09/n'
            rmov sdx GetUserInput_b
            invoke 0xA 0
     end
        loadbl hasInp1 0
		
		cp inpt1 inp1
		cp inpt2 inp2
		cp op chOp
		call CalculateResult
		cp CalculateResult  CalculateResult_b

		cp txt CalculateResult_return
		call _print 
		cp _print _print_b
   end
  
   return GetUserInput 0  
   

.check:
   r_mv ip check_b
   loadbl foundOp 0
   loadbl tmpb 0
   loadc tmpc '+'
   mov i1 14
   same tmpb chOp tmpc

   do tmpb
    loadbl foundOp 1
	return check 1
   end

   loadc tmpc '-'
   mov i1 14
   same tmpb chOp tmpc

   do tmpb
    loadbl foundOp 1
	return check 1
   end

   loadc tmpc '*'
   mov i1 14
   same tmpb chOp tmpc

   do tmpb
    loadbl foundOp 1
	return check 1
   end

   loadc tmpc '\'
   mov i1 14
   same tmpb chOp tmpc

   do tmpb
    loadbl foundOp 1
	return check 1
   end

   loadc tmpc '%'
   mov i1 14
   same tmpb chOp tmpc

   do tmpb
    loadbl foundOp 1
	return check 1
   end

   mov i1 14
   ndo foundOp
     print 'Err : '
     cp GetMatmaticialOpr GetMatmaticialOpr_b
     call GetMatmaticialOpr
   end
   ret

.GetMatmaticialOpr:
  r_mv ip GetMatmaticialOpr_b
  print 'Please type an operator (*, +, -, %, or \)  : '
     loadi inputLength 0
     rln inputLength 990000 '/n'                      ; recieve input and create an input buffer of 10,000 chars

     ; recieve 1st char from input buffer
     cp chOp @990000

     call check
     cp check check_b
     ret
	 
	 
	 
	 
	 