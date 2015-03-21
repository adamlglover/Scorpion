; Beginning of the program
loadi r0 #3                ; set params add(int a, int b)
loadi r1 #2

reg 2 _add                 ; tell the assembler to assosiate the name to r2
reg 7 _console
reg 9 _safe_exit

%func _add                 ; declare func add
%func _console
%func _safe_exit           ; used for program status code

push _console              ; load the data to be pushed to the console and print it
  rmov  sdx  r4            ; store the answer in sdx reg
  mov   bp   50            ; access port 50 on the stdout
  mov   sfc  0             ; tell the stdout to format the result as a number
  mov   scx  0             ; tell the stdout not to perform a command
  init  0                  ; notify the system to perform a system call with given params
return _console

push _add
    add  r4 r0,r1          ; add the contents in both registers
    call _console
return _add

push _safe_exit
    mov ebx 0              ; store the exit code
    mov exc 1              ; notify the system to print the program's exit code to log
    init    3              ; print exit code
return _safe_exit

call _add                  ; call add func
call _safe_exit            ; attempt to close prog w/ status code 0

halt                       ; end of prog

