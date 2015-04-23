; Send a positive signal to gpio 4

import <GPIO/basic-gpio>

.main:
   loadi WAIT 10         ; wait for 10 seconds
   loadi PIN 4
   loadi SIG 1           ; send a positive signal to gpio pin 4
   print 'sending signal!'
   call gpio_out
   ret
   
call main

halt    
   