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
* String.ss
* Library module
*
* This module will take use
* of the primitive element type 
* string in Scorpion.
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/

module: scorpion_lang {

   class: String {
       
	   /*
	   * strPtr will hold the pointer address 
	   * to a string element
	   */
	   loadi strPtr 0
	   
	   /*
	   * the index of a char in a string
	   */
	   loadi index 0
	   
	   /*
	   * Hold the length of a string refrence 
	   */
	   loadi strLen 0
	   
	   /*
	   * The max length for coppying a string 
	   */
	   loadi MaxLen 0 
	   
	   /*
	   * The max length that the string can hold
	   */
	   loadi strMaxLen 9000
	   
	   /*
	   * Our internal string to hold a value
	   */
	   loadi base_string 0 &&idx_offset: 10000
	   
	   
	   .assignString:
	       rload strLen strPtr
		   inc strPtr
		   igt strLen strMaxLen
		        string excpn 'StringSizeOverloadException'
				string msg 'string size too large!'
				throw excpn msg
		   end 
		   adr ref base_string
		   inc ref
		   cp base_string strLen
		   loadi i 0           ; for(int i = 0; i < base_string.len; i++)
		   r_mv ip for 
		   ilt i[strLen]      ; base_string += base_string.at(i);
		        rload ch strPtr
				r_load ref ch
				inc ref 
				inc strPtr
				inc i
				rmov sdx for 
				invoke 0xA 0 
		   end 
	       ret
		   
		.at:
           call scorpion_lang.VirtualMachineStack.pop
	       cp strPtr scorpion_lang.VirtualMachineStack.stackValue                   ; set ptr addr to the string var we want to create
		   call assignString               ; create a string from the ref var
		   
		   ; printf 'base_string <base_string,base_string> index <v,index> len <v,strLen>'
		   inlt index strLen
		         string excpn_ 'IndexOutOfBoundsException'
				 string msg_ 'String char at(): index >= length'
		        throw excpn_ msg_
		   end 
		   loadi chr 0
		   adr ref base_string
		   inc ref
		   loadi i 0          
		   r_mv ip for 
		   ile i[index]      ; return base_string.at(index);
		        same atChar i[index]
                do atChar            ; are we at the requested index?
                   rload chr ref    ; get char
                end 			
                inc ref			
				inc i 
				rmov sdx for         ; loop back
				invoke 0xA 0 
		   end 
		   cp scorpion_lang.VirtualMachineStack.stackValue chr
		   call scorpion_lang.VirtualMachineStack.push
           ret 		
		   
	    .strcpy:                     ; string strcpy(string ref_string, string assign_string);
		   call scorpion_lang.VirtualMachineStack.pop
	       cp strPtr scorpion_lang.VirtualMachineStack.stackValue                ; set ptr addr to the string var we want to create
		   cp ref_string scorpion_lang.VirtualMachineStack.stackValue           ; copy ptr value
		   call assignString               ; create a string from the ref var
		   cp ref_string_len strLen
		   call scorpion_lang.VirtualMachineStack.pop
	       cp assign_string scorpion_lang.VirtualMachineStack.stackValue   
           rload MaxLen assign_string   
		   inlt strLen[MaxLen]
		         print 'String:  error: ref_string.length > assign_string.length/n'
				 return strcpy 1 
		   end 
		           
           r_load assign_string strLen
		   loadi i 0
		   cp ref assign_string
		   adr str_ref base_string 
		   inc str_ref
		   inc ref 
		   r_mv ip for
		   ilt i[strLen]
		        rload ref_char str_ref 
				r_load ref ref_char
				inc ref 
				inc i
				inc str_ref
		        rmov sdx for
                invoke 0xA 0 				
		   end 
		   ret 
   }
}
