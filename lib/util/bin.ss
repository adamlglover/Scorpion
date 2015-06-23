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
* bin.ss
* Library Module
*
* This library module will calculate the 
* binary number of a given element
* 
* Author: Braxton Nunnally
* Date: 6/18/2015
*/

module: util {
	class: Binary {

		/*
		* BIN_START is used to signify the start address
		* of the binary string.
		*
		* You set this value to tell the digital processor where 
		* to start gathering the binary number to be disassembled.
		*/
		loadi BIN_START 0 

		/*
		* BIN_LENGTH is used to state the length of the binary number.
		*/
		loadi BIN_LENGTH 0 

		/*
		* BIN_NUM is used when you want to encode a number into binary
		*/
		loadi BIN_NUM 0

		/*
		* d_bin is a function used to decode a binary number. It 
		* takes a binary string as input and decodes the binary value 
		* then stores the value in BIN_NUM
		*
		* Both functions use the digital processor's built-in binary
		* encoder/decoder
		*/
		.decimalToBin: 
		   rmov sdx BIN_START
		   rmov scx BIN_LENGTH
		   invoke 0x13 0 
		   r_mv sdx BIN_NUM
		   ret

		/*
		* e_bin is a function used to encode binary string to decimal.
		*/   
		.binaryToDecimal:
		   rmov sdx BIN_NUM
		   rmov scx BIN_START
		   inc scx
		   invoke 0x12 0
		   r_mv sdx BIN_LENGTH   
		   r_load BIN_START BIN_LENGTH
		   ret
	}
}