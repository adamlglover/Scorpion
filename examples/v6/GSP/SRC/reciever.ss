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
* reciever.ss
* Recieve data via GPIO
* connection.
*
* Author: Braxton Nunnally
* Date: 6/17/2015
*/ 

import <scorpion/io/GSP>  ; import GSP library

class: Main {
    .main:
	  cp GSP.SP32_COMMAND GSP.SP32_EN_RXADDR
	  call GSP.internal_cmd
	  
	  call GSP.setup
	  breakp
	  print 'Executing GSP protocal.../nwaiting for signal.../n/&'
	  loadi packets 10
	  loadi i 0
	  r_mv ip for 
	  ilt i[packets] ; recieve 10 data packets
	       call GSP.Recieve
	       print 'recieved payload:  <v,GSP.SP32_PAYLOAD_MASK>/n'
		   inc i
		   rmov sdx for 
		   invoke 0xA 0 
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
