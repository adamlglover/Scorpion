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
* VirtualMachineStack.ss
* Library module
*
* This module will use 
* the scorpion VM as a 
* stack machine.
* 
* This module will aid in 
* perforing function calls
*
* Author: Braxton Nunnally
* Date: 6/1/2015
*/

module: scorpion_lang {

   class: VirtualMachineStack {

		/*
		* STACK_SIZE will hold the total size of 
		* the stack to be created. This size will be 
		* the max allowed ammount that the stack can 
		* process at one time and overflow will cause 
		* a StackOverflowException
		*/
		loadi STACK_SIZE 0

		/*
		* stackPtr will hold the ptr address to the 
		* stack to set and or get data from the stack.
		*/
		loadi stackPtr 1                    ;  = -1
		
		/*
		* stackHeight is the current size of the stack
		*/
		loadi stackHeight 0

		/*
		* stackValue can either be used to get data from 
		* the stack and or send data to the stack.
		*/
		loadi stackValue 0

		/*
		* the max size of the stack
		*/
		loadi STACK_MAX 0 

		/*
		* wehter the stack has been created
		*/
		loadbl STACK_CREATED false

		.create_stack:
		   array stack STACK_SIZE double                     ; we create an integer stack that will hold all our data
		   &&idx_offset: 5000
		   mov sfc int
		   neg stackPtr
		   cp STACK_MAX STACK_SIZE
		   loadbl STACK_CREATED true
		   ret

		.push:
		   inc stackPtr
		   inc stackHeight
		   inle stackPtr STACK_MAX
			   string ecpn 'StackOverflowException'
			   string msg 'failed to add more data to the stack'  
			   throw ecpn msg
		   end
		   aload stack stackPtr stackValue
		   ret
		   
		.pop:
		   dec stackPtr
		   dec stackHeight
		   ige stackPtr ZERO 
			   aaload stack stackPtr stackValue
		   end 
		   ilt stackPtr ZERO
		       loadi stackHeight 0
			   loadi stackPtr 1
			   mov sfc int
			   neg stackPtr
		   end 
		   ret 

   }

}
   
   