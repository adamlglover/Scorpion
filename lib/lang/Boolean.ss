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
* Boolean.ss
* Library module
*
* This module will take use
* of the primitive element type 
* bool in Scorpion.
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/

import <lang/VirtualMachineStack>
import <lang/String>

module: scorpion_lang {

     class: Boolean {
	 
			/*
			* the Boolean object corresponding to 
			* the primative element type bool value of true
			*/
			loadbl TRUE true

			/*
			* the Boolean object corresponding to 
			* the primative element type bool value of false
			*/
			loadbl FALSE false
			
			/*
			* The type of object the Boolean class represents
			*/
			string TYPE 'bool'

			/* 
			* internal Obj value 
			*/
			loadbl value false 

			/*
			* thr string version of primitive 
			* element type true
			*/
			string true_s 'true'

			/*
			* thr string version of primitive 
			* element type false
			*/
			string false_s 'false'

			/*
			* it is not recommended to use 
			* this function as it will yeild more
			* time consumption. 
			*
			* assign internal variable to boolean value
			*/
			.Boolean:                                      ; Boolean(bool value){ this.value = value } 
			  call scorpion_lang.VirtualMachineStack.pop
			  t_cast scorpion_lang.VirtualMachineStack.stackValue bool ; ensure data is a bool
			  cp value scorpion_lang.VirtualMachineStack.stackValue
			  ret

			/*
			* check if a string element 
			* has the characters bool
			*/  
			.isBool:                                     ; isBool(string value){ return toBool(value); } 
			   call toBool
			   ret 
			   
			.toBool:                                      ; toBool(string value){ return (value == "true" || value == "false") ? true : false; }
			   call scorpion_lang.VirtualMachineStack.pop
			    cp scorpion_lang.String.strPtr scorpion_lang.VirtualMachineStack.stackValue                   ; set ptr addr to the string var we want to create
			   call scorpion_lang.String.assignString               ; create a string from the ref var
			   
			   strcpi scorpion_lang.VirtualMachineStack.stackValue  scorpion_lang.String.base_string,true_s
			   do scorpion_lang.VirtualMachineStack.stackValue
				   call scorpion_lang.VirtualMachineStack.push
				   return toBool 1 
			   end
			   
			   strcpi scorpion_lang.VirtualMachineStack.stackValue scorpion_lang.String.base_string,false_s
			   do scorpion_lang.VirtualMachineStack.stackValue
				   call scorpion_lang.VirtualMachineStack.push
				   return toBool 1 
			   end
			   
			   loadbl scorpion_lang.VirtualMachineStack.stackValue false
			   call scorpion_lang.VirtualMachineStack.push
			   ret    

     }
}		
