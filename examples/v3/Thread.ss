
loadi r5 3

invoke 0 9    ; start thread cap
   loadi r5 3
invoke 0 10   ; end thread cap

mov scx 10
invoke 0 0    ; create thread

mov scx 10     ; thread id:10
invoke 0 1    ; start thread


loadi r5 3
halt
