
import <GPIO/gpio>

loadi PIN 14                 ; D1
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

/*
* We need 7 pins to create a number 
* for D1(Digit 1)
* Pins:
* 2,    A
* 3,    B
* 4,    C
* 17,   D
* 22,   E
* 27,   F
* 10,   G
*
*/
loadi PIN 2
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b


loadi PIN 3
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

loadi PIN 4
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

loadi PIN 17
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

loadi PIN 22
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

loadi PIN 27
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

loadi PIN 10
loadi DIR 1
call gpio_export            
cp gpio_export gpio_export_b
call gpio_direction
cp gpio_direction gpio_direction_b

; ---------------------------------------------------------
; Output number

loadi PIN 14
loadi SIG 1
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 2
loadi SIG 1
call gpio_write
cp gpio_write gpio_write_b


loadi PIN 3
loadi SIG 1
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 27
loadi SIG 1
call gpio_write
cp gpio_write gpio_write_b
print 'writing to seg-display!'
mov scx 5
sleep 0                              ; sleep for 5 seconds

; -----------------------------------------------------------------
; write 0 and Unexport all pins


loadi PIN 14
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 2
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 3
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 4
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 17
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 22
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 27
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

loadi PIN 10
loadi SIG 0
call gpio_write
cp gpio_write gpio_write_b

; unexport the pins

loadi PIN 14 
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 2
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 3
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 4
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 17
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 22
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 27
call gpio_unexport
cp gpio_unexport gpio_unexport_b

loadi PIN 10
call gpio_unexport
cp gpio_unexport gpio_unexport_b


halt
