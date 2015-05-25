
loadi input 259
&&idx_offset: 259

.main:
   print 'Please type a string: '
   rln input '/n'
   printf '/nThe string <str,input> reversed is: '
   
   loadi ref 0           ; our reference variable
   adr ref input         ; get ptr address to input variable 
   mov i3 0              ; Custom for loop
   add ref ref input     ; start at end of string
   ilt i3 input          ; for(int i = 0; i < input.length; i++)
       rload _char ref
	   printf '<c,_char>'
	   dec ref 
       inc i3 
   end 
   ret

