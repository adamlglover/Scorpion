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

import <scorpion/io/signal>
import <scorpion/io/gpio>
import <util/time>
import <scorpion/lang/VirtualMachineStack>

class: GSP {

    /* ------------( Declare Constant Pin Numbers  )------------ */
     
	 loadi CN 14               ; COM IN pin
	 loadi CO 3               ; COM OUT pin
	 loadi MISO 15            ; Master slave data out
	 loadi MOSI 18            ; Master slave data in
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

     loadi SP32_RX_ADDR    0
     loadi SP32_TX_ADDR    0
     loadi SP32_PAYLOAD_JS     0
	 loadi SP32_OUT 0
	 
	 /* Public variables */
     loadi SP32_PAYLOAD     0
     loadi SP32_PAYLOAD_MASK   0
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
		    same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P0]
			ndo reg 
			     adr ref SP32_RX_ADDR_P0
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P1]
			ndo reg 
			     adr ref SP32_RX_ADDR_P1
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P2]
			ndo reg 
			     adr ref SP32_RX_ADDR_P2
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P3]
			ndo reg 
			     adr ref SP32_RX_ADDR_P3
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P4]
			ndo reg 
			     adr ref SP32_RX_ADDR_P4
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P5]
			ndo reg 
			     adr ref SP32_RX_ADDR_P5
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P6]
			ndo reg 
			     adr ref SP32_RX_ADDR_P6
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P7]
			ndo reg 
			     adr ref SP32_RX_ADDR_P7
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P0]
			ndo reg 
			     adr ref SP32_TX_ADDR_P0
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P1]
			ndo reg 
			     adr ref SP32_TX_ADDR_P1
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P2]
			ndo reg 
			     adr ref SP32_TX_ADDR_P2
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P3]
			ndo reg 
			     adr ref SP32_TX_ADDR_P3
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P4]
			ndo reg 
			     adr ref SP32_TX_ADDR_P4
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P5]
			ndo reg 
			     adr ref SP32_TX_ADDR_P5
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P6]
			ndo reg 
			     adr ref SP32_TX_ADDR_P6
				 inc ref 
				 rload SP32_OUT ref 
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P7]
			ndo reg 
			     adr ref SP32_TX_ADDR_P7
				 inc ref 
				 rload SP32_OUT ref 
			end 
		end 
		same cmd SP32_COMMAND[SP32_W_REGISTER]
		do cmd
		    same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P0]
			ndo reg 
			     adr ref SP32_RX_ADDR_P0
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P1]
			ndo reg 
			     adr ref SP32_RX_ADDR_P1
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P2]
			ndo reg 
			     adr ref SP32_RX_ADDR_P2
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P3]
			ndo reg 
			     adr ref SP32_RX_ADDR_P3
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P4]
			ndo reg 
			     adr ref SP32_RX_ADDR_P4
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P5]
			ndo reg 
			     adr ref SP32_RX_ADDR_P5
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P6]
			ndo reg 
			     adr ref SP32_RX_ADDR_P6
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_RX_ADDR_P7]
			ndo reg 
			     adr ref SP32_RX_ADDR_P7
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P0]
			ndo reg 
			     adr ref SP32_TX_ADDR_P0
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P1]
			ndo reg 
			     adr ref SP32_TX_ADDR_P1
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P2]
			ndo reg 
			     adr ref SP32_TX_ADDR_P2
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P3]
			ndo reg 
			     adr ref SP32_TX_ADDR_P3
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P4]
			ndo reg 
			     adr ref SP32_TX_ADDR_P4
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P5]
			ndo reg 
			     adr ref SP32_TX_ADDR_P5
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P6]
			ndo reg 
			     adr ref SP32_TX_ADDR_P6
				 inc ref 
				 r_load ref SP32_OUT
			end 
			same reg SP32_REGISTER_MASK[SP32_TX_ADDR_P7]
			ndo reg 
			     adr ref SP32_TX_ADDR_P7
				 inc ref 
				 r_load ref SP32_OUT
			end 
		end 
		same cmd SP32_COMMAND[SP32_FLUSH_TX]
		do cmd
		    loadi SP32_OUT 0
			adr ref SP32_TX_ADDR_P0
			inc ref 
	  	    r_load ref SP32_OUT
				 
		    adr ref SP32_TX_ADDR_P1
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_TX_ADDR_P2
			inc ref 
			r_load ref SP32_OUT
			 
			adr ref SP32_TX_ADDR_P3
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_TX_ADDR_P4
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_TX_ADDR_P5
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_TX_ADDR_P6
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_TX_ADDR_P7
			inc ref 
			r_load ref SP32_OUT
		end 
		same cmd SP32_COMMAND[SP32_FLUSH_RX]
		do cmd
		    loadi SP32_OUT 0
			adr ref SP32_RX_ADDR_P0
			inc ref 
	  	    r_load ref SP32_OUT
				 
		    adr ref SP32_RX_ADDR_P1
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_RX_ADDR_P2
			inc ref 
			r_load ref SP32_OUT
			 
			adr ref SP32_RX_ADDR_P3
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_RX_ADDR_P4
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_RX_ADDR_P5
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_RX_ADDR_P6
			inc ref 
			r_load ref SP32_OUT
				 
			adr ref SP32_RX_ADDR_P7
			inc ref 
			r_load ref SP32_OUT
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
		
	  extern GSP.shutdown  ; predefine shutwown() func
	  extern Analog.send   ; predefine Analog send() func
		
		/* TX Driver */
	  .Transmit:
	     loadi zero 0 
	     same isZero SP32_RX_ADDR,zero
		 ndo isZero
	   	      print 'GSP:  error: RX mode is enabled./nShutting down./n'
			  call shutdown
		 end 
		 same isZero SP32_TX_ADDR,zero
		 do isZero
			  print 'GSP:  error: TX mode is not enabled./nShutting down./n'
			  call shutdown
		 end 
	     loadi zero 0 
		 same hasPayload SP32_PAYLOAD,zero 
		 ndo hasPayload
		    ilt SP32_PAYLOAD_JS[SP32_PAYLOAD]
		         call Analog.send 	
				 inc SP32_PAYLOAD_JS
				 inlt SP32_PAYLOAD_JS[SP32_PAYLOAD]
				       loadi SP32_PAYLOAD_JS 0
					   cp gpio.SIG signal.ON
					   cp gpio.PIN GSP.IRQ
					   call gpio.write            ; payload delivered
					   print 'Shutting down./n'
					   call shutdown
					   return Transmit 1 
			     end 
			end
			inlt SP32_PAYLOAD_JS[SP32_PAYLOAD]
			      print 'GSP:  error: payload transmit error./nShutting down./n'
			      call shutdown
			end 
	     end 
         do hasPayload
              printf 'GSP:  error: payload not set!/nShutting down./n'
			  call shutdown
         end 		 
	     ret 
		 
		extern Analog.recieve
		 
		/* RX Driver */ 
	  .Recieve:
	     call Analog.recieve
	     ret 

	  .shutdown:
         cp gpio.PIN CN
		 call gpio.unexport
	     cp gpio.PIN MISO
		 call gpio.unexport
		 do SP32_RX_ADDR                 ; if(RXMODE) unexport(MOSI);
	         cp gpio.PIN MOSI
		     call gpio.unexport
		 end 
	     cp gpio.PIN CO 
		 call gpio.unexport
	     cp gpio.PIN IRQ
		 call gpio.unexport
		  
		 loadi SP32_RX_ADDR 0
		 loadi SP32_TX_ADDR 0
		 loadi SP32_PAYLOAD_JS 0
		 loadi SP32_OUT 0
		 loadi SP32_PAYLOAD 0
		 loadi SP32_REGISTER_MASK 0
		 loadi SP32_COMMAND 0 
        ret 	  
		  
      .setup:
	    cp gpio.PIN CN
		call gpio.export
	    cp gpio.PIN MISO
		call gpio.export
	    cp gpio.PIN MOSI
		call gpio.export
	    cp gpio.PIN CO 
		call gpio.export
	    cp gpio.PIN IRQ
		call gpio.export
		
		do SP32_RX_ADDR
			cp gpio.DIR signal.IN
			cp gpio.PIN CN
			call gpio.direction
			cp gpio.PIN IRQ
			call gpio.direction
			cp gpio.PIN MOSI
			call gpio.direction
	    	cp gpio.DIR signal.OUT
		    cp gpio.PIN CO
		    call gpio.direction
			cp gpio.PIN MISO
			call gpio.direction
			return setup 1
		end
		
		do SP32_TX_ADDR 
			cp gpio.DIR signal.OUT
		    cp gpio.PIN CO
			call gpio.direction
			cp gpio.PIN MISO
			call gpio.direction
			cp gpio.PIN IRQ
			call gpio.direction
			cp gpio.DIR signal.IN
			cp gpio.PIN CN
			call gpio.direction
			return setup 1
		end
		print 'GSP:  error: RX or TX mode not set./nShutting down./n'
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
	* The max allowable bin size
	*/
	loadi MAX_BIN_LEN 8
	
	/*
	* Our binary string
	*/
	string bin '00000000'
	
	.recieve:
	    loadbl SEND_PAYLOAD true			 
        wloop SEND_PAYLOAD SEND_PAYLOADb
			   cp gpio.PIN GSP.CN
			   call gpio.read
		   	   same isReady gpio.SIG[signal.ON] ; have the recieve device recieved the signal
		 	   do isReady
			      cp gpio.SIG signal.ON
				  cp gpio.PIN GSP.CO
			  	  call gpio.write
                  loadi time.SECS 0.015 ; sleep for 15 ms				  
				  call delay 
			      cp gpio.SIG signal.OFF
				  cp gpio.PIN GSP.CO
			  	  call gpio.write
			      loadbl SEND_PAYLOAD false     ; ready to send bits 
			   end 
		endwl  SEND_PAYLOAD SEND_PAYLOADb	
		loadi i 0
		adr ref bin
		inc ref 
		r_mv ip for 
		ilt i[bin]
		     loadbl GET_PAYLOAD true			 
             wloop GET_PAYLOAD GET_PAYLOADb
					cp gpio.PIN GSP.CN
			        call gpio.read
					same isReady gpio.SIG[signal.ON] ; next bit?
					do isReady
					    cp gpio.SIG signal.ON
						cp gpio.PIN GSP.CO
						call gpio.write 
                        loadi time.SECS 0.015 ; sleep for 15 ms				  
				        call delay 
					    loadbl SEND_PAYLOAD false     ; ready to send bits 
					end 
			 endwl  GET_PAYLOAD GET_PAYLOADb
			 cp gpio.PIN GSP.MOSI          ; read bit
			 call gpio.read
			 r_load ref gpio.SIG
			 rmov sdx for 
			 invoke 0xA 0
		end 
		loadbl GET_PAYLOAD true			 
        wloop GET_PAYLOAD GET_PAYLOADb
				cp gpio.PIN GSP.IRQ
			    call gpio.read
				same isReady gpio.SIG[signal.ON] ; next bit?
				do isReady
					printf 'packet recieved: <v,bin>'
					loadbl SEND_PAYLOAD false     ; ready to send bits 
				end 
		endwl  GET_PAYLOAD GET_PAYLOADb
	   ret
	
	.send:
	    cp Binary.BIN_NUM DATA
		adr Binary.BIN_START bin
		call Binary.e_bin
		loadi eight 8
		ilt bin,eight
		    sub i eight,bin ; i = 8 - bin.length;
			cp start i
			adr ref bin
            inc ref 			
			add ref ref,bin  ; fast forward
			cp bin eight
			r_mv ip for
			ilt i[bin]
			     loadc z '0'
			     r_load ref z
				 inc ref 
			     inc start 
				 rmov sdx for 
				 invoke 0xA 0
			end 
		end 
		printf 'transmitting: <str,bin>/n'
		ile bin[MAX_BIN_LEN]
			 cp gpio.SIG signal.ON
			 cp gpio.PIN GSP.CO
			 call gpio.write            ; sig input ready   
             loadbl SEND_PAYLOAD true			 
             wloop SEND_PAYLOAD SEND_PAYLOADb
					cp gpio.PIN GSP.CN
			        call gpio.read
					same isReady gpio.SIG[signal.ON] ; have the recieve device recieved the signal
					printf 'gpio.SIG = <v,gpio.SIG>/n'
					do isReady
					    cp gpio.SIG signal.OFF
						cp gpio.PIN GSP.CO
						call gpio.write 
					    loadbl SEND_PAYLOAD false     ; ready to send bits 
					end 
			 endwl  SEND_PAYLOAD SEND_PAYLOADb			 
			loadi i 0
			r_mv ip for 
			ilt i[bin]
				 adr VirtualMachineStack.stackValue bin
				 call VirtualMachineStack.push
				 cp String.index i
				 call String.at 
				 call VirtualMachineStack.pop
				 
			     cp gpio.SIG signal.ON
			     cp gpio.PIN GSP.CO
			     call gpio.write            ; sig input ready  
				 loadbl nextBit true
				 wloop nextBit nextBitb
					    cp gpio.PIN GSP.CN
			            call gpio.read
					    same isReady gpio.SIG[signal.ON] ; have the recieve device recieved the signal
					    do isReady
					       cp gpio.SIG signal.OFF
						   cp gpio.PIN GSP.CO
						   call gpio.write 
			               cp gpio.PIN GSP.MISO
			               cp gpio.SIG signal.OFF
				           call gpio.write 
					       loadbl nextBit false     ; send bit
						end 
						
				 endwl nextBit nextBitb
				 loadc chr '1' 
				 same is1 chr,VirtualMachineStack.stackValue
				 do is1
					cp gpio.PIN GSP.MISO
					cp gpio.SIG signal.ON
					call gpio.write
				 end 
				 
				 loadc chr '0' 
				 same is1 chr,VirtualMachineStack.stackValue
				 do is1
					cp gpio.PIN GSP.MISO
					cp gpio.SIG signal.OFF
					call gpio.write
				 end 
				 inc i 
				 rmov sdx for 
				 invoke 0xA 0 
			end 
		end 	
	    ret 
}
