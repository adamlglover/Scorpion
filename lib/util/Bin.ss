; This program will calculate the binary number of a given element
; This library module will use the built-in cpu binary dis/assembler

; ****Variables****
; BIN_START  : the start address of the binary string
; BIN_LENGTH : the length of the binary string
; BIN_NUM : the element to encode to binary

.d_bin:    ; decode a binary number
   r_mv ip d_bin_b
   rmov sdx BIN_START
   rmov scx BIN_LENGTH
   invoke 0x13 0 
   r_mv sdx BIN_NUM
   ret
   
.e_bin:   ; encode an element into binary
   r_mv ip e_bin_b
   rmov sdx BIN_NUM
   rmov scx BIN_START
   invoke 0x12 0
   r_mv sdx BIN_LENGTH   
   ret

