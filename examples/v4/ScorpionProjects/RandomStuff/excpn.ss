
string excpn 'RandomException'
adr sdx excpn
string msg 'RandoMEXception'
adr scx msg
strcpi equal
do equal
   print 'The strings are equal/n'
end

ndo equal   
    print 'The strings are not equal/n'
end

import <util/time>

print 'delaying thread for 1.2 seconds.../n'
dload SECS 1.250
call delay 
print 'exiting main thread'


halt
