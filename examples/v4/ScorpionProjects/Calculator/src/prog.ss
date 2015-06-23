loadc response '0'
loadi end_prog_return 0

.end_prog:
   mov i1 11
   r_mv ip end_prog_b
   print '-----------------------------------------/n'
   print '           ($---- EXIT ? ----$)/n'
   print '-----------------------------------------/n'
     loadi inputLength 0
     rln inputLength 990000 '/n'                      ; recieve input and create an input buffer of 10,000 chars

     ; recieve 1st char from input buffer
     cp response @990000

        loadc limit '1'
        mov i1 14
        same @100001 limit response
        do @100001
         loadi end_prog_return 1
         return end_prog 1
        end

        loadc limit '0'
        mov i1 14 
        same @100001 limit response
        do @100001
         loadi end_prog_return 0
         return end_prog 1
        end 

     loadi end_prog_return 0
      ret

.ck_p:
   r_mv ip ck_p_b
   call end_prog
   cp end_prog end_prog_b
   cp r end_prog_return
   
   loadi @100002 0            ; target num
   loadbl @100001 0
   mov i1 14
   same @100001 r @100002
   do @100001
     cp main main_b
     call main                ; main();
   end

   loadi @100002 1            ; target num
   mov i1 14
   same @100001 r @100002
   do @100001
     ; close prog
     halt
   end
  
   loadi @100002 1            ; target num 
   mov i1 14
   same @100001 r @100002
   ndo @100001                  ; if(r != 1 || r != 0) halt
     loadi @100002 0            ; target num
     mov i1 14
     same @100001 r @100002
     ndo @100001
       ; err close
       halt
     end
   end
   ret

