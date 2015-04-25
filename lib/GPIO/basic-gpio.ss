; Raspberry Pi Basic GPIO library

; ****Variables****
; PIN : the pin to write to
; WAIT : the ammount of time(in sec) to send/recieve the signal from/to the pin
; SIG : the signal that was recieved from pin

.gpio_out:   
     r_mv ip gpio_out_b
     mov i1 11
     rmov sdx PIN
     mov sfc 2
     invoke 0x6 0       ; export pin
 
    mov tmp 1
    mov sfc 0
    invoke 0x6 0        ; set direction

    rmov tmp SIG
    mov sfc 1
    invoke 0x5 0        ; send signal 1
    rmov scx WAIT       ; sleep

    sleep 0
    mov tmp 0
    invoke 0x5 0        ; send signal 0

    mov sfc 1
    invoke 0x6 0        ; unexport pin 4
    ret

.gpio_in:
    r_mv ip gpio_in_b
    mov i1 11
    rmov sdx PIN
    mov sfc 2
    invoke 0x6 0       ; export pin

    mov tmp 0
    mov sfc 0
    invoke 0x6 0       ; set direction

    mov sfc 0
    invoke 0x5 0       ; read signal 
    rmov scx WAIT      ; sleep
    sleep 0
    r_mv scr SIG 

    mov sfc 1
    invoke 0x6 0       ; unexport pin 4
    ret
	
	