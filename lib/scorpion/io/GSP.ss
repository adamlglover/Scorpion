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
* GSP.ss
* GPIO Signal Protocal(GSP)
* This is a library module used for 
* transmitting data accross 2 devices 
* via GPIO pins.
*
* This file will have the main methods for 
* performing this protocal
*
* Author: Braxton Nunnally
* Date: 6/17/2015
*/ 

import <scorpion/lang/io/signal>
import <scorpion/lang/io/gpio>

class: GSP {

    /* ------------( Declare Constant Pin Numbers  )------------ */
     
	 loadi CN 4               ; COM IN pin
	 loadi CO 3               ; COM OUT pin
	 loadi CSN 2              ; Sys bit select
	 loadi MOSI 17            ; Master slave data in
	 loadi MISO 15            ; Master slave data out
	 loadi SCK 18             ; Sys bit in
	 loadi IRQ 12             ; Data In/Out Interrupt
	 
	 /* -----------( Declare Constant Mnemonics For Config )----------- */
     loadi SP32_STATUS      0x04           &&idx_offset: 1
     loadi SP32_RX_ADDR_P0  0x06          &&idx_offset: 1
     loadi SP32_RX_ADDR_P1  0x07          &&idx_offset: 1
     loadi SP32_RX_ADDR_P2  0x08          &&idx_offset: 1
     loadi SP32_RX_ADDR_P3  0x09          &&idx_offset: 1
   	 loadi SP32_RX_ADDR_P4  0xA           &&idx_offset: 1
	 loadi SP32_RX_ADDR_P5  0xB           &&idx_offset: 1
	 loadi SP32_RX_ADDR_P6  0xC           &&idx_offset: 1
	 loadi SP32_RX_ADDR_P7  0xD           &&idx_offset: 1
	 loadi SP32_TX_ADDR_P0    0xF            &&idx_offset: 1
	 loadi SP32_TX_ADDR_P1    0x17          &&idx_offset: 1
	 loadi SP32_TX_ADDR_P2    0x18          &&idx_offset: 1
	 loadi SP32_TX_ADDR_P3    0x19          &&idx_offset: 1
	 loadi SP32_TX_ADDR_P4    0x20          &&idx_offset: 1
	 loadi SP32_TX_ADDR_P5    0x21          &&idx_offset: 1
	 loadi SP32_TX_ADDR_P6    0x22          &&idx_offset: 1
	 loadi SP32_TX_ADDR_P7    0x23          &&idx_offset: 1

     loadi SP32_TX_FULL     0
     loadi SP32_TX_EMPTY    0
     loadi SP32_RX_FULL     0
     loadi SP32_RX_EMPTY    0
     loadi SP32_RX_ADDR    0
     loadi SP32_TX_ADDR    0
     loadi SP32_PAYLOAD_JS     0
	 
	 /* Public variables */
     loadi SP32_PAYLOAD     0
	 loadi SP32_REGISTER_MASK  0
	 loadi SP32_COMMAND         0           ; out command holder
	 
	 /* Command Name Mnemonics (Instructions) */
	 loadi SP32_R_REGISTER     0x00
	 loadi SP32_W_REGISTER     0x20
	 loadi SP32_FLUSH_TX       0xE1
	 loadi SP32_FLUSH_RX       0xE2
     loadi SP32_EN_RXADDR      0x01    /* EN_RXADDR register */  
     loadi SP32_EN_TXADDR      0x02    /* EN_TXADDR register */

	 
	 .internal_cmd: 
		same cmd SP32_COMMAND[SP32_R_REGISTER]
		do cmd
		
		end 
		same cmd SP32_COMMAND[SP32_W_REGISTER]
		do cmd
		
		end 
		same cmd SP32_COMMAND[SP32_FLUSH_TX]
		do cmd
		
		end 
		same cmd SP32_COMMAND[SP32_FLUSH_RX]
		do cmd
		
		end 
		same cmd SP32_COMMAND[SP32_EN_TXADDR]
		do cmd
		    same isZero SP32_TX_ADDR,zero
			ndo isZero
			     print 'GSP:  warning: TX mode is already enabled./n'
				 return internal_cmd 1
			end 
			same isZero SP32_TX_ADDR,zero
			ndo isZero
			     print 'GSP:  warning: RX mode is already enabled, restart module with RX config to switch modes./n'
				 return internal_cmd 1
			end 
			loadi SP32_TX_ADDR 1    ; Enable TX mode
		end 
		
		same cmd SP32_COMMAND[SP32_EN_RXADDR]
		do cmd
		    same isZero SP32_RX_ADDR,zero
			ndo isZero
			     print 'GSP:  warning: RX mode is already enabled./n'
				 return internal_cmd 1
			end 
			same isZero SP32_TX_ADDR,zero
			ndo isZero
			     print 'GSP:  warning: TX mode is already enabled, restart module with TX config to switch modes./n'
				 return internal_cmd 1
			end 
			loadi SP32_RX_ADDR 1    ; Enable RX mode
		end 
	    ret 

	  .shutdown:
          cp gpio.PIN CN
		  call gpio.unexport
	      cp gpio.PIN CSN
		  call gpio.unexport
	      cp gpio.PIN MOSI
		  call gpio.unexport
	      cp gpio.PIN MISO
		  call gpio.unexport
	      cp gpio.PIN SCK
		  call gpio.unexport
	      cp gpio.PIN CO 
		  call gpio.unexport
	      cp gpio.PIN IRQ
		  call gpio.unexport
          ret 	  
		  
      .setup:
	     cp gpio.PIN CN
		call gpio.export
	    cp gpio.PIN CSN
		call gpio.export
	    cp gpio.PIN MOSI
		call gpio.export
	    cp gpio.PIN MISO
		call gpio.export
	    cp gpio.PIN SCK
		call gpio.export
	    cp gpio.PIN CO 
		call gpio.export
	    cp gpio.PIN IRQ
		call gpio.export
		
		do SP32_RX_ADDR
			cp gpio.DIR gpio_signal.IN
	        cp gpio.PIN CSN
			call gpio.direction
			cp gpio.PIN MOSI
			call gpio.direction
			cp gpio.PIN SCK
			call gpio.direction
			cp gpio.PIN CN
			call gpio.direction
			cp gpio.PIN MISO
			call gpio.direction
			cp gpio.PIN IRQ
			call gpio.direction
		    cp gpio.PIN CO
	    	cp gpio.DIR gpio_signal.OUT
		    call gpio.direction
		end
		
		do SP32_TX_ADDR 
		    cp gpio.PIN CO
			cp gpio.DIR gpio_signal.OUT
			call gpio.direction
			cp gpio.PIN CSN
			call gpio.direction
			cp gpio.PIN SCK
			call gpio.direction
			cp gpio.PIN MISO
			call gpio.direction
			cp gpio.PIN IRQ
			call gpio.direction
			cp gpio.DIR gpio_signal.IN
			cp gpio.PIN CN
			call gpio.direction
		end
	   ret

}

