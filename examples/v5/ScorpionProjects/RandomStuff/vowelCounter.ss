loadi input 259
&&idx_offset: 259
loadi vowelCount 0 
loadc _char 'x'
loadbl has_char false
loadi a_size 5
array vowels a_size char
&&idx_offset: 7

.hasChar:
   mov sdx 0 
   loop charlp charlp_b 5
        aaload vowels sdx vowel
        same has_char _char,vowel
		do has_char
	       inc vowelCount
		   return hasChar 1 
		end 
		inc sdx 
   endl charlp charlp_b
   ret 
   
.vowelCheck:
   call hasChar
   ret 
   
.main:
   print 'Please type a string: '
   rln input '/n'
   
   ; Assign array values
   loadc _char 'a'
   mov sdx 0             ; index 0 
   aload vowels sdx _char
   loadc _char 'e'
   mov sdx 1             ; index 1 
   aload vowels sdx _char
   loadc _char 'i'
   mov sdx 2             ; index 2 
   aload vowels sdx _char
   loadc _char 'o'
   mov sdx 3             ; index 3
   aload vowels sdx _char
   loadc _char 'u'
   mov sdx 4             ; index 4 
   aload vowels sdx _char
   
   loadi ref 0           ; our reference variable
   adr ref input         ; get ptr address to input variable
   inc ref    
   mov i3 0              ; Custom for loop
   r_mv ip backTrack
   ilt i3 input          ; for(int i = 0; i < input.length; i++)
       rload _char ref
       call vowelCheck
	
	   inc ref 
       inc i3 
	   rmov sdx backTrack
	   invoke 0xA 0 
   end 
   printf '/nThe string <str,input> has <v,vowelCount> vowel(s). '
   ret

   call main 
   
   halt
