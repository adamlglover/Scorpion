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
* time.ss
* Library module
*
* This library module holds a simple function
* for delaying time
* 
* Author: Braxton Nunnally
* Date: 6/18/2015
*/
module: util {
	class: Time {
		/*
		* SECS is used for determining how long will the 
		* delay function wait before continuing execution.
		*
		* The delay() function only has a precision of 3 
		* nubers behind the decimal point.
		*/
		dload SECS 0.000
		
		/*
		* USECS is used for determining how long will the 
		* delay function wait before continuing execution.
		*
		* The udelay() measures timing in microseconds to delay 
		* a thread's exection.
		*/
		dload USECS 0.000
		
		/*
		* MILLS is used for determining how long will the 
		* delay function wait before continuing execution.
		*
		*/
		dload MILLS 0

		/*
		* delay is used for delaying a thread's execution.
		* this function is an alternative to the sleep instruction.
		*
		* Unlike sleep, this function dosent actually stop the thread for 
		* a specified ammount of time, but rather, it pre-occupies it(delays it)
		* for a specified ammount of time.
		*/
		.delay:
		   adr sdx time_before
		   mov sfc 0
		   invoke 0xfa 0
		   
		   loadbl delay_time true
		   adr sdx time
		   mov i1 double
		   wloop delay_time delay_time_b
				 invoke 0xfa 0
				 sub time time,time_before
				 ige time SECS
					 loadbl delay_time false
					 return delay 1
				 end
		   endwl delay_time delay_time_b
		   ret
		
		.delayMills:
		   loadi US 1000          ; microseconds
		   mov sfc int
		   mult MILLS MILLS,US  ; convert from mills to microseconds 
		   rmov sdx MILLS 
		   sleep 1 
		   ret 
		   
		.udelay:
           adr sdx time_before
		   mov sfc 1
		   invoke 0xfa 0
		   
		   loadbl delay_time true
		   adr sdx time
		   mov i1 int
		   wloop delay_time delay_time_b
				 invoke 0xfa 0
				 sub time time,time_before
				 ige time USECS
					 loadbl delay_time false
					 return udelay 1
				 end
		   endwl delay_time delay_time_b
        ret 		
	}	
}
