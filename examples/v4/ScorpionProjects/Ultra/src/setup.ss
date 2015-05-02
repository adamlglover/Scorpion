
; we will simply set up the pins

loadi trig 4    ; the trigger pin 
loadi echo 2    ; the echo pin for when we get the signal back
loadi sig 0     ; the signal from the ultrosonic module
loadi esig 1    ; the expected signal to be recieved

.setup:
   mov sdx 4
   mov sfc 2
   invoke 0x6 0         ; export pin 4

   mov tmp 1
   mov sfc 0
   invoke 0x6 0         ; set direction

   mov sdx 2
   mov sfc 2
   invoke 0x6 0         ; export pin 2

   mov tmp 0
   mov sfc 0
   invoke 0x6 0         ; set direction
   ret

.trigger:
   rmov sdx trig
   mov sfc 1
   invoke 0x5 0          ; send signal 1
   ret

.dist:
   loadbl wait true
   wloop wait wait_b
        rmov sdx echo
        mov sfc 0
        invoke 0x5 0          ; is the signal 1?
		
		r_mv scr sig 
		same is1 sig,esig
		do is1 
		   loadbl wait false
		   return dist 1
		end 
   endwl wait wait_b
   ret   
