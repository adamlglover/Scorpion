; This program will use the VM's 3 random number generators

reg 0 main
reg 1 n1                ; will be used for the first random number generator
reg 2 n2
reg 3 n3
reg 4 random
reg 60 console
reg 61 console_b
reg 62 random_b
reg 63 gen
ivar _length

%func main
%func random
%func console

push cosole
  loadr console_b ip
  mov   bp   50            ; access port 50 on the stdout
  mov   sfc  0             ; tell the stdout to format the result as a number
  mov   scx  0             ; tell the stdout not to perform a command
  init  0                  ; notify the system to perform a system call with gi$
return console

push random
  loadi r21 1
  loadi r22 2
  loadi r23 3
  loadi n1 0
  loadi n2 0
  loadi n3 0
  loadr random_b ip             ; store bactrack

  same r6 gen,r21                 ; if(gen == 1)
  do r6                           ; random generator 1 
    loop r10 r11 5                ; generate 5 random numbers
       rand_1 n1 30               ; gen a random # from 1 to 30 rand(max)
       rmov sdx n1 
       call console               ; print result
       loadr console console_b
    endl r10 r11
  end

  same r6 gen,r22                 ; ; if(gen == 2)
  do r6                           ; random generator 2
    loop r10 r11 5                ; generate 5 random numbers
       rand_2 n2 6 30             ; gen a random # from 1 to 30 rand(seed,max)
       rmov sdx n2
       call console               ; print result
       loadr console console_b
    endl r10 r11
  end

  same r6 gen,r23                ; if(gen == 3)
  do r6                          ; random generator 3
   loop r10 r11 5                ; generate 5 random numbers
       rand_3 n3 30              ; gen a random # from 1 to 30 rand(max)
       rmov sdx n3
       call console               ; print result
       loadr console console_b
    endl r10 r11
  end
return random

push main

   str _length "Random Number Generator 1\n"              ; Assembler code for getting length of a string
   print _length "Random Number Generator 1\n"
   loadi gen 1
   call random
   loadr random random_b
   str _length "\n"                                       ; Assembler code for getting length of a string
   print _length "\n"

   str _length "Random Number Generator 2\n"              ; Assembler code for getting length of a string
   print _length "Random Number Generator 2\n"
   loadi gen 2
   call random
   loadr random random_b
   str _length "\n"                                       ; Assembler code for getting length of a string
   print _length "\n"

   str _length "Random Number Generator 3\n"              ; Assembler code for getting length of a string
   print _length "Random Number Generator 3\n"
   loadi gen 3
   call random

return main 

call main

halt
