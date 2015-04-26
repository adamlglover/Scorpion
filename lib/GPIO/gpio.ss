; Raspberry Pi Standard GPIO library

; ****Variables****
; PIN : the pin to write to
; DIR : the pis's direction(in/out[1:0])
; SIG : the signal that was recieved or sent from/to pin 

.gpio_export:
    mov i1 11
    rmov sdx PIN
    mov sfc 2
    invoke 0x6 0       ; export pin
    ret

.gpio_direction:
    mov i1 11
    rmov sdx PIN
    rmov tmp DIR
    mov sfc 0
    invoke 0x6 0        ; set direction
    ret

.gpio_write:               
    mov i1 11
    rmov sdx PIN
	rmov tmp SIG
    mov sfc 1
    invoke 0x5 0
    ret
	
.gpio_read:              
    mov i1 11
    rmov sdx PIN
    mov sfc 0
    invoke 0x5 0
	rmov scr SIG
    ret	
	
.gpio_unexport:
    mov i1 11
    rmov sdx PIN
    mov sfc 1
    invoke 0x6 0        ; unexport pin 4
    ret

	
	