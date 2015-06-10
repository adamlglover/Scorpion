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
* Reboot the Raspberry Pi
*
* Author: Braxton Nunnally
* Date: 6/1/2015
*/

string command 'sudo shutdown -r now'         ; This will represent our console command

.main:
   adr sdx command
   invoke 0x0 0                                    ; reboot the raspberry pi
   ret 
   
call main 

halt 

module: ap {

	%Class Dog {
	   
	   loadi age 8
	   
	}

}

cp age [ap]Dog{age}

