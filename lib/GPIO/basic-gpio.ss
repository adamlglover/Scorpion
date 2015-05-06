/*
* basic-gpio.ss
* Libary module
*
* This file provides a few simple set 
* of functions that allows you to 
* control a raspberry pi's GPIO pins.
*
* The internal details are hidden. 
*/

/*
* PIN is used for specifying which pin to 
* import/export or to send a signal to.
*
* Raspberry's GPIO pins range from 0 - 27 that you 
* can control signal I/O
*
* When performing GPIO I/O, you must export and set 
* the direction to the desired pin before using it. Otherwise
* the operating system will reject your I/O request.
*
* If you attempt to make an I/O request for a pin that is not
* in conjunction with the set direction, then the os will reject
* the I/O request.
*
* Example: 
* pin 4 DIR = IN 
*
* pin 4 can only handle I/O requests for receiving signals of a pin.
*/
loadi PIN 0

/*
* SIG represents the signal that was received from a specified 
* GPIO pin. This element will only hold data if a pin's DIR=IN.
*
* once gpio_read has been called, SIG will then be populated with the 
* calculated digital signal received.
*
* SIG also represents the signal that is being sent to a specified 
* GPIO pin. This will only work id the specified GPIO pin's DIR=OUT
*/
loadi SIG 0 

/*
* WAIT represents the time that an I/O request runs. 
* The time is calculated in seconds.
*/
loadi WAIT 0 

/*
* Alike gpio_write in "GPIO/gpio", gpio_out is a function that outputs a 
* digital signal of either a high or low voltage.
*
* For more information on high and low digital signals, see "GPIO/signal"
* for more information on GPIO I/O requests, see "GPIO/gpio"
*/
.gpio_out:   
     r_mv ip gpio_out_b
     rmov sdx PIN
     mov sfc 2
     invoke 0x6 0      
 
    mov tmp 1
    mov sfc 0
    invoke 0x6 0      

    rmov tmp SIG
    mov sfc 1
    invoke 0x5 0  
    rmov scx WAIT      

    sleep 0
    mov tmp 0
    invoke 0x5 0      

    mov sfc 1
    invoke 0x6 0     
    ret

/*
* Alike gpio_read in "GPIO/gpio", gpio_in is a function that reads a 
* digital signal of either a high or low voltage.
*
* For more information on high and low digital signals, see "GPIO/signal"
* for more information on GPIO I/O requests, see "GPIO/gpio"
*/
.gpio_in:
    r_mv ip gpio_in_b
    rmov sdx PIN
    mov sfc 2
    invoke 0x6 0      

    mov tmp 0
    mov sfc 0
    invoke 0x6 0    

    mov sfc 0
    invoke 0x5 0     
    rmov scx WAIT     
    sleep 0
    r_mv scr SIG 

    mov sfc 1
    invoke 0x6 0     
    ret
	
	