
; we will simply set up the pins

loadi trig 4    ; the trigger pin 
loadi echo 2    ; the echo pin for when we get the signal back
loadi sig 0     ; the signal from the ultrosonic module
loadi esig 1    ; the expected signal to be recieved

dload start 0.7
dload stop 0.9
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
   mov tmp 0
   mov sfc 1
   invoke 0x5 0          ; send signal 0
   
   mov scx 2
   sleep 1
   rmov sdx trig
   mov tmp 1
   mov sfc 1
   invoke 0x5 0          ; send signal 1
   
   mov scx 10
   sleep 1
   rmov sdx trig
   mov tmp 0
   mov sfc 1
   invoke 0x5 0          ; send signal 0
   
   ;rmov sdx trig
   ;mov sfc 1
   ;invoke 0x5 0          ; send signal 0
   ret

.dist:
   loadbl wait true
   wloop wait wait_b
        rmov sdx echo
        mov sfc 0
        invoke 0x5 0          ; is the signal 1?
		
		r_mv scr sig 
		same is1 sig,esig
		ndo is1 
		   adr start_adr start
		   rmov sdx start_adr
		   invoke 0xfa 0
		end 
		do is1
		   loadbl wait false
		end
   endwl wait wait_b
   
   loadbl wait true
   loadi esig 0
   wloop wait wait_b
        rmov sdx echo
        mov sfc 0
        invoke 0x5 0          ; is the signal 0?
		
		r_mv scr sig 
		same is1 sig,esig
		ndo is1 
		   adr stop_adr stop
		   rmov sdx stop_adr
		   invoke 0xfa 0 
		end 
		do is1
		   loadbl wait false
		end
   endwl wait wait_b
   
   ; dis = (float)(stop - start) / 1000000 * 34000 / 2;
   mov i1 12
   sub time stop,start
   loadi temp 1000000
   div time time,temp
   loadi temp 34000
   mult time time,temp
   loadi temp 2
   div time time,temp
   printf '<do,time>'
   ret   
