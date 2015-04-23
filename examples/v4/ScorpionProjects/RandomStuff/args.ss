; Bare metal program args print

loadi argc 0  ; argument count
loadi str 0   ; will hold the pointer for arg string
loadi ref 0
.main:
  adr ref str      ; get the address of the str label
  rmov sdx ref
  mov scx 990000   ; specify arg input buffer
  invoke 0x23 0    ; retrieve args
  r_mv scx argc
  
  printf 'The argument count is: <r,argc> the argument str_size is: <r,str>/n'
  
  loadi ref 990000
  print 'program args >> '
  rloop parse loop_b str
     rload char ref
     printf '<c,char>'
     inc ref
  endl parse loop_b

  print '/n'
  ret
  
  call main 
 
 halt
  