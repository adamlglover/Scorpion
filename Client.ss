
import <scorpion/io/gpio>
import <scorpion/io/signal>
import <scorpion/io/Color>

/* Data Transmit register 
* 
* This register is used to 
* communicate with the server
*/
loadi TX 4

/*
* Data Recieve register 
*
* This register is used as 
* the response from the server
*/
loadi RX 14

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
   
   cp GPIO.PIN RX
   call GPIO.export
   cp GPIO.DIR signal.IN
   call GPIO.direction
   ret 
   
.clientShutdown:
   loadi CONNECTION 0 
   cp GPIO.PIN RX
   call GPIO.unexport
   cp GPIO.PIN TX
   cp GPIO.SIG signal.OFF
   call GPIO.write
   call GPIO.unexport
   ret 
   
/* Macros for testing server connection */   
.testConnection:
   cp GPIO.SIG signal.ON
   cp GPIO.PIN TX 
   call GPIO.write
   
   cp GPIO.PIN RX 
   loadbl cTest true
   wloop cTest cTestb
          call GPIO.read
		  same hasConnection GPIO.SIG[signal.ON]
		  do hasConnection
		      cp CONNECTION CONNECTION_GOOD
			  return testConnection 1
		  end 
   endwl cTest cTestb 
   ret    

.startClient:
   printf 'Setting up client [ .. ]/&'
   call clientSetup
   rmov sdx Color.REG_SH 
   printf '/b/b/b/b<col,Color.GREEN>done<col,Color.NORM> ]/n/&'
   print 'Connecting [ ... ]/&'
   call testConnection
   rmov sdx Color.REG_SH 
   printf '/b/b/b/b/b<col,Color.GREEN>done<col,Color.NORM> ]/n/&'
   call clientShutdown
   ret    

call startClient

halt   