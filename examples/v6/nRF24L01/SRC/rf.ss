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
* rf.ss
* Radio frequency class for 
* controlling the nRF24L01 
* wireless transmitter.
*
* Author: Braxton Nunnally
* Date: 6/15/2015
*/ 

import <scorpion/io/gpio>
import <scorpion/io/signal>

extern Analog.send          ; predefine Analog send() finction
extern Analog.DATA          ; predefine Analog int Data; label

class: Rf {

     /* ------------( Declare Constant Pin Numbers  )------------ */
     
	 loadi CE 4               ; Enables RX or TX mode
	 loadi CSN 2              ; SPI chip select
	 loadi MOSI 17            ; Master slave data in
	 loadi MISO 15            ; Master slave data out
	 loadi SCK 18             ; SPI clock
	 
	 
	 /* ----------( Set up data pins )----------  */
     .pin_setup:
	    cp gpio.PIN CE
		call gpio.export
	    cp gpio.PIN CSN
		call gpio.export
	    cp gpio.PIN MOSI
		call gpio.export
	    cp gpio.PIN MISO
		call gpio.export
	    cp gpio.PIN SCK
		call gpio.export
		
	    cp gpio.PIN CE
		cp gpio.DIR gpio_signal.OUT
		call gpio.direction
	    cp gpio.PIN CSN
		call gpio.direction
	    cp gpio.PIN MOSI
		call gpio.direction
	    cp gpio.PIN SCK
		call gpio.direction
		cp gpio.DIR gpio_signal.IN
	    cp gpio.PIN MISO
		call gpio.direction
	    ret 
		
    .pin_destroy:
	    cp gpio.PIN CE
		call gpio.unexport
	    cp gpio.PIN CSN
		call gpio.unexport
	    cp gpio.PIN MOSI
		call gpio.unexport
	    cp gpio.PIN MISO
		call gpio.unexport
	    cp gpio.PIN SCK
		call gpio.unexport
		ret 	
		   
		.enableTX:
		   cp gpio.PIN CE
		   cp gpio.SIG gpio_signal.ON
		   call gpio.write
		   cp gpio.PIN CSN 
		   call gpio.write
		   ret 
		   
		.transmit:
		    loadi Analog.DATA 5
            call Analog.send
            ret 		
}

import <util/bin>
import <scorpion/lang/String>

class: Analog {
    
	/*
    * The data to be transmitted
	*/
	loadi DATA 0
	
	/*
	* Our binary string
	*/
	loadi bin 0 &&idx_offset: 500
	
	.send:
	    cp Binary.BIN_NUM DATA
		adr Binary.BIN_START bin
		call Binary.e_bin
		printf 'transmitting: <str,bin>/n'
		loadi i 0
		r_mv ip for 
		ilt i[bin]
	         adr VirtualMachineStack.stackValue bin
	         call VirtualMachineStack.push
			 cp String.index i
			 call String.at 
			 
			 call VirtualMachineStack.pop
			 loadc chr '1' 
			 same is1 chr,VirtualMachineStack.stackValue
			 do is1
		        cp gpio.PIN MOSI
	      	    cp gpio.SIG gpio_signal.ON
		        call gpio.write
			 end 
			 
			 loadc chr '0' 
			 same is1 chr,VirtualMachineStack.stackValue
			 do is1
		        cp gpio.PIN MOSI
	      	    cp gpio.SIG gpio_signal.OFF
		        call gpio.write
			 end 
			 inc i 
			 rmov sdx for 
			 invoke 0xA 0 
		end 
	    ret 
}