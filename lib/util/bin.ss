/*
* bin.ss
* Library Module
*
* This library module will calculate the 
* binary number of a given element
*/

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
.d_bin: 
   r_mv ip d_bin_b
   rmov sdx BIN_START
   rmov scx BIN_LENGTH
   invoke 0x13 0 
   r_mv sdx BIN_NUM
   ret

/*
* e_bin is a function used to encode an element into a binary string.
*/   
.e_bin:
   r_mv ip e_bin_b
   rmov sdx BIN_NUM
   rmov scx BIN_START
   invoke 0x12 0
   r_mv sdx BIN_LENGTH   
   ret

