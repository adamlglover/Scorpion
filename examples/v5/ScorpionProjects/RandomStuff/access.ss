   
scmnd
rhalt
rhalt
scmnd   
loadi CARS 0   

add eax 734,43222
r_mv eax val
printf '<v,val>/n'

div eax 0,0
r_mv eax val
printf '<v,val>/n'
print ' '
print ''
print ' 4'
printf ''
printf '<v,val>'
print '/n'

loadi a 0

div a a,a
div a a,a
div a a,a
div a a,a
div a a,a
printf '<v,a>/n'
loadi a 4
loadi b 5
rem a a,b
printf '<v,a>/n'
mov i1 double
rem a a,a
printf '<v,a>/n'

loadi a 0

sub a a,a
printf '<v,a>/n'

mult a a,a
printf '<v,a>/n'

inc a
dec a
printf 'a = <v,a>/n'

mov sdx 1
mov scx 1
and eax sdx scx
r_mv eax a 
printf 'eax = <bl,a>/n'

mov sdx 0
or eax sdx scx
r_mv eax a 
printf 'eax = <bl,a>/n'

xor eax sdx scx 
r_mv eax a 
printf 'eax = <bl,a>/n'

not sdx
r_mv scx a 
printf 'scx = <bl,a>/n'

nand eax sdx scx 
r_mv eax a 
printf 'eax = <bl,a>/n'

nor eax sdx scx 
r_mv eax a 
printf 'eax = <bl,a>/n'

xnor eax sdx scx 
r_mv eax a 
printf 'eax = <bl,a>/n'

loadi a 7
loadi b 32

swp a b 
printf 'a = <v,a>; b = <v,b>/n'

nac

mov sdx 9
mov scx 100
sr scx 
r_mv scx a
printf 'scx = <v,a>/n'


mov sdx 3
mov scx 100
sl scx 
r_mv scx a
printf 'scx = <v,a>/n'

rdtsc
r_mv eax a
printf 'eax = (<v,a>)/n'

mov sdx 100
rand_3
r_mv eax a
printf 'rand 3 = [<v,a>]/n'

mov sdx 100
rand_3
r_mv eax a
printf 'rand 3 = [<v,a>]/n'


mov sdx 100
rand_1
r_mv eax a
printf 'rand 1 = [<v,a>]/n'

mov sdx 100
rand_1
r_mv eax a
printf 'rand 1 = [<v,a>]/n'


mov sdx 100
rand_1
r_mv eax a
printf 'rand 1 = [<v,a>]/n'

string excpn 'Random Exception'
string msg 'This is a random exception'
print '/n'
throw excpn msg

