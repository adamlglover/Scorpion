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
* signal.ss 
* Library module
* 
* This file contains a series 
* of reference variables that you can
* use in your code for GPIO I/O requests
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/
module: scorpion_io {
    class: signal {

		/*
		* IN is used for setting the 
		* direction for a GPIO pin.
		*
		* IN signifies that the specified GPIO 
		* pin will read the current state of the pin.
		* [How much voltage is being applied to the pin]
		*
		* Voltage at 0v or less signifies OFF
		* Voltage at 3.5v or more signifies ON
		*
		* A stable voltage of 3.5v will produce an accurate 
		* reading of ON, any voltage higher may skew the reading
		* of the pin state
		*/
		loadi IN 0

		/*
		* OUT is used for setting the direction
		* of a GPIO pin.
		*
		* OUT signifies that the specified GPIO 
		* pin will output a signal of both a high and 
		* low voltage.
		* [high: ~3.5v  low: ~0v]
		*
		* High and low voltage output is not constant and 
		* may vary depending on a few conditions. However the
		* average voltage is what is depicted above.
		*/
		loadi OUT 1

		/*
		* ON represents a digital high voltage signal 
		* of ~3.5v
		*
		* This high voltage signal represents the digital 
		* signal of 1. When the microprocessor receives this
		* signal, it will determine the digital signal value
		* based on the voltage.
		* 
		*   ~0v = 0
		* ~3.5v = 1
		*/
		loadi ON 1

		/*
		* OFF represents a digital low voltage signal 
		* of 0v 
		*
		* This low voltage signal represents the digital 
		* signal of 0. This occurs usually when the computer
		* blocks off sending a signal to the pin and it results 
		* as the digital signal 0.
		*/
		loadi OFF 0 
   }
}
