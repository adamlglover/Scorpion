/*
* signal.ss 
* Library module
* 
* This file contains a series 
* of reference variables that you can
* use in your code for GPIO I/O requests
*/

/*
* IN is used for setting the 
* direction for a GPIO pin.
*
* IN signifies that the specified GPIO 
* pin will read the current state of the pin.
* [How much voltage is being applied to the pin]
*
* Voltage at 0v or less signifies OFF
* Voltage at 3.5v or more signifies ON
*
* A stable voltage of 3.5v will produce an accurate 
* reading of ON, any voltage higher may skew the reading
* of the pin state
*/
loadi IN 0

/*
* OUT is used for setting the direction
* of a GPIO pin.
*
* OUT signifies that the specified GPIO 
* pin will output a signal of both a high and 
* low voltage.
* [high: ~3.5v  low: ~0v]
*
* High and low voltage output is not constant and 
* may vary depending on a few conditions. However the
* average voltage is what is depicted above.
*/
loadi OUT 1

/*
* ON represents a digital high voltage signal 
* of ~3.5v
*
* This high voltage signal represents the digital 
* signal of 1. When the microprocessor receives this
* signal, it will determine the digital signal value
* based on the voltage.
* 
*   ~0v = 0
* ~3.5v = 1
*/
loadi ON 1

/*
* OFF represents a digital low voltage signal 
* of 0v 
*
* This low voltage signal represents the digital 
* signal of 0. This occurs usually when the computer
* blocks off sending a signal to the pin and it results 
* as the digital signal 0.
*/
loadi OFF 0 
