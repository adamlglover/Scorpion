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

module:  Test {

	class: main {
	    string msg '/'message/' '
    	.main:
		   loadi oi 10
		   loadbl bl true
		   dload pi 3.14159642
		   print 'hello!'
		   ret
	}

	class: sys {
		.run:
		   call main.main
		   printf '<str,main.msg>/ndone./n'
		   
		   ret 
	}

}   

call sys.run
   
halt
