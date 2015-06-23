/*
* Copyright (C) 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
* main.ss
*
* This file uses the ultrasonic 
* module for distance measurement.
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/

import <scorpion/io/gpio>
import <scorpion/io/signal>

import <scorpion/io/Color>
import <util/time>


class: Main {

	/*
	* Ultrasonic trigger
	* pin 
	*/
	loadi TRIG 4

	/*
	* Ultrasonic echo
	* pin 
	*/
	loadi ECHO 22

	
	.unexport:
	    cp GPIO.PIN TRIG 
	   call GPIO.unexport
	   
	   cp GPIO.PIN ECHO
	   call GPIO.unexport
	   ret 
    .setup:
	   cp GPIO.PIN TRIG 
	   call GPIO.export
	   
	   cp GPIO.PIN ECHO
	   call GPIO.export
	   
	   
	   cp GPIO.PIN TRIG 
	   cp GPIO.DIR signal.OUT
	   call GPIO.direction
	   
	   cp GPIO.PIN ECHO
	   cp GPIO.DIR signal.IN
	   call GPIO.direction
	   ret 

	.trigger:
	   
	   loadbl echo true
	   cp GPIO.PIN TRIG 
	   cp GPIO.SIG signal.ON
	   call GPIO.write
	   cp GPIO.SIG signal.ON
	   call GPIO.write
	   cp GPIO.SIG signal.OFF
	   call GPIO.write
	   cp GPIO.PIN ECHO 
       adr sdx time_before
       mov sfc 1 
	   invoke 0xfa 0 
	   wloop echo echob
	          call GPIO.read
			  same hasEcho GPIO.SIG[signal.ON]
;			  printf 'GPIO.SIG: <v,GPIO.SIG> <v,signal.ON>/n'
			  do hasEcho
                  adr sdx time_after
                  mov sfc 1 
	              invoke 0xfa 0 			 
                  mov sfc double  
                  sub Time time_after,time_before
;                printf 'tbefore: <v,time_before> tafter: <v,time_after> '
                  return trigger 1				  
			  end 
	   endwl echo echob 
       ret 
	   
	.main:
           call setup
	   print 'Sending Signal.../n/&'
           breakp
	   call trigger 
	   printf 'time: <v,Time>'
	   call unexport
        ret 	

}


call Main.main

halt
