; in-app Exception call module

; ****Variables****
; EXCEPTION_MSG : the length of the exception string
; EXCEPTION_ADDR : the address pointed to the exception string
; EXCEPTION_MESSAGE : the length of the excpetion message
; EXCEPTION_MSG_ADDR : the address to the exception message
; EXCEPTION_EXIT : the exit code for closing the program
; EXCEPTION_IP : The ip address before application shutdown

loadi EXCEPTION_IP 0
.Exception:
   r_mv ip Exception_b
   print 'Virtural Machine RuntimeException: caused by '
   loadi i 0
   cp addr EXCEPTION_ADDR
   inc addr
   r_mv ip for
   ilt i EXCEPTION_MSG 
      rload ch addr
	  printf '<c,ch>'
	  inc i
	  inc addr
	  rmov sdx for
      invoke 0xA 0       ; jump back on the for loop
   end
   print ':/n    '
   
   loadi i 0
   cp addr EXCEPTION_MSG_ADDR
   inc addr
   r_mv ip for
   ilt i EXCEPTION_MESSAGE
      rload ch addr
	  printf '<c,ch>'
	  inc i
	  inc addr
	  rmov sdx for
      invoke 0xA 0       ; jump back on the for loop
   end
   printf '/n    Program Position {<r,EXCEPTION_IP>}'
   rmov ebx EXCEPTION_EXIT 
   halt
   ret

