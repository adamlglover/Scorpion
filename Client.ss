
import <scorpion/io/gpio>
import <scorpion/io/signal>
import <scorpion/io/Color>
import <util/time>

/* Data Transmit register 
* 
* This register is used to 
* communicate with the server
*/
loadi TX 15

/*
* Data Recieve register 
*
* This register is used as 
* the response from the server
*/
loadi RX 14

/*
* Data Recieve register
*
* This register is used to
* send commands to the server
*/
loadi CS 17

/* Connection response codes */
loadi CONNECTION_GOOD 0x23
loadi CONNECTION_LOST 0xFa

/* COnnection status */
loadi CONNECTION 0

.clientSetup:
   cp GPIO.PIN TX
   call GPIO.export
   cp GPIO.DIR signal.OUT
   call GPIO.direction
   
   cp GPIO.PIN CS
   call GPIO.export
   cp GPIO.DIR signal.OUT
   call GPIO.direction
   
   cp GPIO.PIN RX
   call GPIO.export
   cp GPIO.DIR signal.IN
   call GPIO.direction
   ret 
   
.clientShutdown:
   loadi CONNECTION 0 
   cp GPIO.PIN RX
   call GPIO.unexport
   cp GPIO.PIN CS
   call GPIO.unexport
   cp GPIO.PIN TX
   cp GPIO.SIG signal.OFF
   call GPIO.write
   call GPIO.unexport
   ret 

/* 
* Max ammount in seconds for 
* attempting to connect to server 
*/
loadi connection_time_max 15
   
/* Macros for testing server connection */   
.testConnection:
   adr sdx time_before_
   mov sfc 0
   invoke 0xfa 0 
   
   print 'Connecting [ ... ]/&'
   cp GPIO.SIG signal.OFF
   cp GPIO.PIN TX 
   call GPIO.write
   
   cp GPIO.PIN RX 
   loadbl cTest true
   wloop cTest cTestb
          call GPIO.read
		  same hasConnection GPIO.SIG[signal.ON]
		  do hasConnection
		      cp CONNECTION CONNECTION_GOOD
              cp GPIO.SIG signal.ON
			  cp GPIO.PIN TX 
			  call GPIO.write
             rmov sdx Color.REG_SH 
             printf '/b/b/b/b/b<col,Color.GREEN>done<col,Color.NORM> ]/n/&'
			  return testConnection 1
		  end 
		  ndo hasConnection
			   adr sdx time_after_
			   mov sfc 0
			   invoke 0xfa 0 
			   mov sfc double
			   sub connection_time time_after_,time_before_
			   same connection_timeout connection_time,connection_time_max
			   do connection_timeout
                   rmov sdx Color.REG_SH 
                   printf '/b/b/b/b/b<col,Color.RED>failed<col,Color.NORM> ]/n/&'
				   print 'Connection timed out.'
                   call clientShutdown
				   halt
			   end 
		  end 
   endwl cTest cTestb 
   ret    

.getIp:
   print 'Getting IP Address.../n'
   call testConnection
   loadi USECS 510
   call Time.udelay
   cp GPIO.SIG signal.ON
   cp GPIO.PIN CS
   call GPIO.write
   ret 
   
.activateClient:
   ; get device name
   call getIp
   ret   
   
.startClient:
   printf 'Setting up client [ .. ]/&'
   call clientSetup
   rmov sdx Color.REG_SH 
   printf '/b/b/b/b<col,Color.GREEN>done<col,Color.NORM> ]/n/&'
   call activateClient
   call clientShutdown
   ret    

call startClient

halt   
