PRINT 'What is your name: '

RLN input_length 990000 '/n'

PRINT 'Hello '
; parse input
LOADI ref 990000
RLOOP parse loop_b input_length
   RLOAD char ref
   PRINTF '<c,char>'
   INC ref
ENDL parse loop_b

PRINT '/n'

string msg 'This is a string!'

halt

