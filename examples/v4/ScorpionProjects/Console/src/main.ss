print 'What is your name: '

loadi input 10000            ; The max ammount of input chars set to the console
rln input '/n'               ; use the "input" label as a string and store the console input in it
&&idx_offset: 10000          ; allocate 10,000 addresses for the input

print 'Hello '
printf '<str,input>/n'       ; print the input from the console

string msg 'This is a string!'

halt

