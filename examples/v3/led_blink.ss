; Simply send 1 high pulse signal to led
; Some Assembler Tuning(Nessicary)
&&_Assembler:
   v_size: 1000
   start_index: 0
; ------------------------------
mov sdx 4
mov sfc 2
invoke 0x6     ; export pin 4

mov tmp 1
mov sfc 0
invoke 0x6     ; set direction

mov scx 1      ; sleep for 1 second
mov sfc 1
invoke 0x5       ; send signal 1

sleep
mov tmp 0
invoke 0x5       ; send signal 0
sleep

mov tmp 1
invoke 0x5       ; send signal 1
sleep

mov sdx 4
mov sfc 1
invoke 0x6     ; unexport pin 4
