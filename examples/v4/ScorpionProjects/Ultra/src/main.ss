/*
* Ultrasonic Distance Measurement program
* This program will use an ultrasonic module
* to calculate the distance of how far an obstacle 
* is from you
*
*/

import 'C:\Users\Braxton\Desktop\ScorpionProjects\Ultra\src\setup.ss'

call setup

print 'sending wave/n'
call trigger 

call dist

print 'recieved wave'

halt
