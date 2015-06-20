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
* basic-gpio.ss
* Libary module
*
* This file provides a few simple set 
* of functions that allows you to 
* control a raspberry pi's GPIO pins.
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/
module: scorpion_io {
    class: basic_gpio {
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
		* WAIT represents the time that an I/O request runs. 
		* The time is calculated in seconds.
		*/
		loadi WAIT 0 

		/*
		* Alike gpio_write in "GPIO/gpio", gpio_out is a function that outputs a 
		* digital signal of either a high or low voltage.
		*
		* For more information on high and low digital signals, see "GPIO/signal"
		* for more information on GPIO I/O requests, see "GPIO/gpio"
		*/
		.gpio_out:   
			 rmov sdx PIN
			 mov sfc 2
			 invoke 0x6 0      
		 
			mov scx 1
			mov sfc 0
			invoke 0x6 0      

			rmov scx SIG
			mov sfc 1
			invoke 0x5 0  
			rmov sdx WAIT      

			sleep 0
			rmov sdx PIN
			mov scx 0
			invoke 0x5 0      

			mov sfc 1
			invoke 0x6 0     
			ret

		/*
		* Alike gpio_read in "GPIO/gpio", gpio_in is a function that reads a 
		* digital signal of either a high or low voltage.
		*
		* For more information on high and low digital signals, see "GPIO/signal"
		* for more information on GPIO I/O requests, see "GPIO/gpio"
		*/
		.gpio_in:
			rmov sdx PIN
			mov sfc 2
			invoke 0x6 0      

			mov scx 0
			mov sfc 0
			invoke 0x6 0    

			mov sfc 0
			invoke 0x5 0     
			r_mv scr SIG 

			mov sfc 1
			invoke 0x6 0     
			ret
	}
}	