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
* gpio.ss
* Libary module
*
* This file provides a complete set 
* of functions that allows you to have 
* control over handling the os calls for 
* controlling the raspberry pi's GPIO pins.
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/
module: scorpion_io {
    class: gpio {
		/*
		* PIN is used for specifying which pin to 
		* import/export or to send a signal to.
		*
		* Raspberry's GPIO pins range from 0 - 27 that you 
		* can control signal I/O
		*
		* When performing GPIO I/O, you must export and set 
		* the direction to the desired pin before using it. Otherwise
		* the operating system will reject your I/O request.
		*
		* If you attempt to make an I/O request for a pin that is not
		* in conjunction with the set direction, then the os will reject
		* the I/O request.
		*
		* Example: 
		* pin 4 DIR = IN 
		*
		* pin 4 can only handle I/O requests for receiving signals of a pin.
		*/
		loadi PIN 0

		/*
		* DIR is used for specifying the direction
		* of I/O requests that a specified pin can handle.
		*
		* import "GPIO/signal" to get the different signals 
		* that you will use to  determine the signal to send and 
		* for setting the direction of a GPIO pin
		*
		* DIR supports 2 types of directions:
		* IN=0  &  OUT=1 
		*
		* for more information on direction signals and I/O signals,
		* see "GPIO/signal"
		*/
		loadi DIR 0

		/*
		* SIG represents the signal that was received from a specified 
		* GPIO pin. This element will only hold data if a pin's DIR=IN.
		*
		* once gpio_read has been called, SIG will then be populated with the 
		* calculated digital signal received.
		*
		* SIG also represents the signal that is being sent to a specified 
		* GPIO pin. This will only work id the specified GPIO pin's DIR=OUT
		*/
		loadi SIG 0 

		/*
		* gpio_export is used to send an os call to request to use a gpio pin 
		* on the raspberry pi.
		*
		* If the pin is already exported, then nothing will happen, however if the 
		* pin is not exported, this function should be the very first function you 
		* call for that pin. 
		*
		* DO NOT call any other gpio functions for an unexported pin, otherwise you 
		* will experience unpleasent errors and the os will reject all your I/O requests.
		*
		* If you experience any errors, please check the log "/usr/share/scorpion/log.txt"
		* and you will most likely figure out what's wrong. A common error you may experience
		* may be that you attempted to set the direction for an unexported pin and then exported 
		* the pin. When this happens, the pin's direction will not be set, therefore denying all
		* I/O requests.
		*/
		.export:
			rmov sdx PIN
			mov sfc 2
			invoke 0x6 0  
			ret

		/*
		* gpio_direction is used to send an os call to specify the I/O direction of an 
		* exported GPIO pin.
		*
		* If the specified pin is not exported, an error(that's not fatal) will occur. In 
		* order to perform an I/O request to a pin, the DIR must be set.
		*/
		.direction:
			rmov sdx PIN
			rmov scx DIR
			mov sfc 0
			invoke 0x6 0   
			ret

		/*
		* gpio_write is a function that performs the actual I/O request.
		* Specifically, sending a high or low voltage digital signal to a 
		* GPIO pin.
		*
		* For information on high and low voltage signals, see "scorpion/io/signal"
		*/	
		.write:    
			rmov sdx PIN
			rmov scx SIG
			mov sfc 1
			invoke 0x5 0
			ret

		/*
		* gpio_read is a function that performs the actual I/O request.
		* Specifically, recieving a high or low voltage digital signal from a 
		* GPIO pin.
		*
		* For information on high and low voltage signals, see "scorpion/io/signal"
		*/		
		.read:           
			rmov sdx PIN
			mov sfc 0
			invoke 0x5 0
			r_mv scr SIG
			ret	

		/*
		* gpio_unexport is used to send an os call to request to use a gpio pin 
		* on the raspberry pi.
		*
		* Once this function is called you can NO LONGER send I/O requests to send 
		* and recieve signals from a GPIO pin.
		*
		* In order to use a GPIO pin again, you must go through the process angain of 
		* preparing the pin for use.
		*
		* 1. export pin
		* 2. set dir
		* (pin ready for use)
		* 3. send I/O requests
		*
		* If you experience any errors, please check the log "/usr/share/scorpion/log.txt"
		* and you will most likely figure out what's wrong. 
		*/	
		.unexport:
			rmov sdx PIN
			mov sfc 1
			invoke 0x6 0     
			ret
	
   }	
}
