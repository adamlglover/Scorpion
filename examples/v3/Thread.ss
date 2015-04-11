
loadi r5 3

invoke 0 9    ; start thread cap
   loadi r5 3
invoke 0 10   ; end thread cap

invoke 0 0    ; create thread

mov scx 1     ; thread 1
invoke 0 1    ; start thread

loadi r5 3
halt
