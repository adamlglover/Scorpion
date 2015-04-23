; Bare metal code for gpio sig reading
; read gpio sig

import <GPIO/basic-gpio>

.main:
   loadbl is1 true                  ; bool is1 = true;
   loadi SIG 0
   loadi ESIG 1                    ; the expected sig
   loadi WAIT 1
   loadi PIN 13
   print 'waiting for signal/n'
   wloop is1 is1_b
      same is1 ESIG SIG            ; is1 = if(SIG == ESIG)
	  do is1
	    printf 'sig == <r,SIG>'
		halt
	  end
	  ndo is1
	    mov i1 14
	    neg is1
        call gpio_in
	    cp gpio_in gpio_in_b
	  end
   endwl is1 is1_b
   ret
	
call main	

halt
