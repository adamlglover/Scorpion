/*
* time.ss
* Library module
*
* This library module holds a simple function
* for delaying time
*/

/*
* SECS is used for determining how long will the 
* delay function wait before continuing execution
*/
dload SECS 0.000

/*
* delay is used for delaying a thread's execution.
* this function is an alternative to the sleep instruction.
*
* Unlike sleep, this function dosent actually stop the thread for 
* a specified ammount of time, but rather, it pre-occupies it(delays it)
* for a specified ammount of time.
*/
.delay:
   r_mv ip delay_b
   adr sdx time_before
   invoke 0xfa 0
   
   loadbl delay_time true
   adr sdx time
   mov i1 12
   wloop delay_time delay_time_b
         invoke 0xfa 0
		 sub time time,time_before
		 ige time SECS
             loadbl delay_time false
		     return delay 1
		 end
   endwl delay_time delay_time_b
   ret
	
	