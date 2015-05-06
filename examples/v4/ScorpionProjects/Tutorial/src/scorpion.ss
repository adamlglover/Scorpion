; This is a single line comment

/*
* This is a 
* multi-line 
* comment
*/

loadi min_age 18
loadi age 0

print 'What is your age? '
; prompt the user to input age 
loadi input 10          ; only accept 10 chars
rln input '/n'
&&idx_offset: 10

adr ref input
inc ref
rloop age_loop age_loop_b input
      rload digit ref
      ct_int digit digit
	  mov i1 11
      anum age digit	  
	  inc ref
endl age_loop age_loop_b

printf 'your age is: <v,age>/n'
ige age min_age
   print 'You are old enough to drive.'
end
ilt age min_age
   print 'You are not old enough to drive.'
end

halt
