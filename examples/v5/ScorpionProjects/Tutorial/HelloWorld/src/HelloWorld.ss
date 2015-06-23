; This is a comment
; osjf
; doubhfidjfvs
; hdsvbjdifznvs
;
;

/*
* This is a 
* multi-line comment
* ekijsdak
*/

; int short double float char string bool

loadi pencils 429
sload cars 2
dload pi 3.1415937
loadf inches 3.11
loadc chr 39 ; '
loadbl _bool true
string msg 'This is a message'

printf 'I have <v,pencils> pencils./n'
printf 'pi = <v,pi> || <do,pi>/n'
printf 'chr = <c,chr>/n'
printf '_bool = <bl,_bool>/n'
printf 'msg == <v,msg> || msg = <str,msg>/n/n'

loadbl iLikeCake false 

do cars
   print 'I Like Cake./n'
end 
ndo iLikeCake
    print 'I Do Not Like Cake./n'
end

loadc apple '1'

do apple 
   print 'apple == 1'
end 

ndo apple
   print 'apple == 0'
end 

loadi Adam 19
loadi Braxton 18

ige Adam Braxton
    print 'Adam is older than or == Braxton./n'
end 

loadi time 0
adr sdx time_before 
invoke 0xfa 0 
mov sdx 0
loop reg_loop reg_loop_b 250000
      inc sdx 
endl reg_loop reg_loop_b
r_mv sdx num 
adr sdx time
invoke 0xfa 0 

sub time time,time_before
printf 'num = (<v,num>) | time: <v,time>'

; 
;
;


halt
