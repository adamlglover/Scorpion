; This program will utilize getting a progra argument from the console

.main:
   call console     ; recieve the data from the console and store it
   call _print      ; print data
   ret

loadi argc 0
loadi str  0 
loadi max_args 1
.console:
   adr ref str      ; get the address of the str label
   rmov sdx ref
   mov scx 990000   ; specify arg input buffer
   invoke 0x23 0    ; retrieve args
   r_mv scx argc    ; retrieve arg count
   ret   

loadc space ' '   
._print:
   same has_correct_arg max_args,argc
   ndo has_correct_arg
      print 'Hello World!'
	  return _print 1
   end
   do has_correct_arg
      print 'Hello '
	  loadbl printArg true
	  loadi ref 990000
	  loadi idx 1
	  wloop printArg printArg_b
		 rload ch ref
	     same char ch,space
		 do char
		     loadbl printArg false
		 end 
		 same reachedEnd idx,str          ; have we reached the end of the args?
		 do reachedEnd
		    return _print 1
		 end
		 ndo char 
            printf '<c,ch>'
			inc ref
		 end
		 inc idx
	  endwl printArg printArg_b
   end
   print '/n'
   ret   

call main
   
halt   
   