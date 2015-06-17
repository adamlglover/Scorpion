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
* Main class file for 
* nRF24L01 wireless 
* transmitter.
*
* Author: Braxton Nunnally
* Date: 6/15/2015
*/ 

import <scorpion/lang/VirtualMachineStack>
import '../rf.ss' ; import all soruce files

; We isolate this class from the rest of the other files because we can use the * shortcut to import everything without double compiling main
class: Main {
   .main:
     call Rf.pin_setup
	 call Rf.enableTX
	 call Rf.transmit
	 call Rf.pin_destroy
     ret
}

class: sys {
   .start_:
      loadi VirtualMachineStack.STACK_SIZE 1000
      call VirtualMachineStack.create_stack
      call Main.main
      ret
}

call sys.start_