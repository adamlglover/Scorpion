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
* transmitter.ss
* Transmit data via GPIO
* connection.
*
* Author: Braxton Nunnally
* Date: 6/17/2015
*/ 

import <scorpion/io/GSP>  ; import GSP library

class: Main {
    .main:
	  cp GSP.SP32_COMMAND GSP.SP32_EN_TXADDR
	  call GSP.internal_cmd
	  
	  call GSP.setup
	  loadi Analog.DATA 5
	  loadi GSP.SP32_PAYLOAD 1
	  breakp
	  print 'Executing GSP protocal.../n'
	  printf 'payload size: <v,GSP.SP32_PAYLOAD>/n/nwaiting for signal.../n/&'
	  call GSP.Transmit 
	  call GSP.shutdown
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
