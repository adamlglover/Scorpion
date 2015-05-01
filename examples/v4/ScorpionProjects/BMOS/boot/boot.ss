; This program represents the entry-point for our Os
;
; Considering thst the Scorpion Virtual Machine 
; has already booted the CPU and The ram mem is mapped 
; and set we do not need a serious bootloader to control
; the hardware
;
; First we boot and perform some simple output to signify 
; that the Os is active
;

import 'C:\Users\Braxton\Desktop\ScorpionProjects\BMOS\os\kernal.ss'
; We use this method to signify that the os has been started
; This pwr led will be on for the life of the os
; GPIO pin 4 
.pwr_on:
    mov sdx 4
    mov sfc 2
    invoke 0x6 0         ; export pin 4

    mov tmp 1
    mov sfc 0
    invoke 0x6 0         ; set direction

    mov sfc 1
    invoke 0x5 0         ; send signal 1(keep power led on while Os is running)

   mov sdx 14
   mov sfc 2
   invoke 0x6 0          ; export pin 14

   mov tmp 1
   mov sfc 0
   invoke 0x6 0          ; set direction

   mov sfc 1
   invoke 0x5 0          ; send signal 1
   
   mov scx 2
   sleep 0              ; sleep for 2 seconds

   mov tmp 0
   invoke 0x5 0          ; send signal 0

   mov sdx 14
   mov sfc 1
   invoke 0x6 0          ; unexport pin 14
   ret

.pwr_off:
    mov sdx 4
    mov tmp 0
    invoke 0x5 0         ; send signal 0

    mov sfc 1
    invoke 0x6 0         ; unexport pin 4
    ret	
	
; We use this function to signify that the Os is active
; The led will only flash when hardware on the raspberry 
; pi has been accessed(excluding ram)
.led_act:                ; send a quick signal signifying that the Os is active(only when hardware interactions are performed)
   r_mv ip led_act_b     ; store func backtrack
   mov sdx 14
   mov sfc 2
   invoke 0x6 0          ; export pin 14

   mov tmp 1
   mov sfc 0
   invoke 0x6 0          ; set direction

   mov scx 150           ; sleep for 150 mills
   mov sfc 1
   invoke 0x5 0          ; send signal 1

   sleep 1
   mov tmp 0
   invoke 0x5 0          ; send signal 0

   mov sdx 14
   mov sfc 1
   invoke 0x6 0          ; unexport pin 14
   ret

.wait:
   mov sdx 19
   mov sfc 2
   invoke 0x6 0          ; export pin 14

   mov tmp 0             ; we want to read a positive signal for pwr btn
   mov sfc 0
   invoke 0x6 0          ; set direction
   
   loadi on 1            ; have we pressed the pwr btn?
   loadbl pwr_wait true
   wloop pwr_wait pwr_wait_b
        invoke 0x5 0     ; read btn state
		r_mv scr pwr
        same has_pwr pwr,on	
        do has_pwr
          loadbl pwr_wait false ; pwr button pressed, start os
		  return wait 1
        end		
   endwl pwr_wait pwr_wait_b
   ret
   
; Boot the Os
.boot:
     call pwr_on         ; send positive signal to pwr led pin 4 
     call led_act
     cp led_act led_act_b

     ; print Os logo
	 print ' __________   __       __               ___________  ___________ /n'
     print '¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦¦     ¦¦¦¦             ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦/n'
     print '¦¦¦¯¯¯¯¯¯¯¦¦¦¦¦¦¦¦   ¦¦¦¦¦             ¦¦¦¯¯¯¯¯¯¯¦¦¦¦¦¦¯¯¯¯¯¯¯¯¯ /n'
     print '¦¦¦       ¦¦¦¦¦¦¦¦¦ ¦¦¦¦¦¦             ¦¦¦       ¦¦¦¦¦¦          /n'
     print '¦¦¦_______¦¦¦¦¦¦ ¦¦¦¦¦ ¦¦¦ ___________ ¦¦¦       ¦¦¦¦¦¦_________ /n'
     print '¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦  ¦¦¦  ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦       ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦/n'
     print '¦¦¦¯¯¯¯¯¯¯¦¦¦¦¦¦   ¯   ¦¦¦ ¯¯¯¯¯¯¯¯¯¯¯ ¦¦¦       ¦¦¦ ¯¯¯¯¯¯¯¯¯¦¦¦/n'
     print '¦¦¦       ¦¦¦¦¦¦       ¦¦¦             ¦¦¦       ¦¦¦          ¦¦¦/n'
     print '¦¦¦_______¦¦¦¦¦¦       ¦¦¦             ¦¦¦_______¦¦¦ _________¦¦¦/n'
     print '¦¦¦¦¦¦¦¦¦¦¦¦ ¦¦¦       ¦¦¦             ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦/n'
     print ' ¯¯¯¯¯¯¯¯¯¯   ¯         ¯               ¯¯¯¯¯¯¯¯¯¯¯  ¯¯¯¯¯¯¯¯¯¯¯ /n'
	 print '#################################################################/n'
     
	 mov scx 2000
     sleep 1	 
     call led_act
     cp led_act led_act_b
     ret

.main:
     call wait     ; wait for user to press pwr btn
     call boot     ; boot os
     call kernal   ; Run kernal
     ;call Os      ; Start Os
	 call pwr_off  ; pwr off device
	 loadi @1000
     ret

call main


halt
   