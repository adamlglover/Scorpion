; control gpio pins

reg 1000 _export_b
reg 1001 status
reg 1002 _unexport_b
reg 1003 _direction_b
reg 1004 gpio_data
reg 1005 direction
reg 1006 pin
reg 1007 _io_value
reg 1008 _gpio_write_b
reg 1009 _gpio_read_b
reg 1010 _io_read_b
reg 1011 _io_read
reg 1012 _export
reg 1013 _unexport
reg 1014 _direction
reg 1015 _gpio_write
reg 1016 _gpio_read


loadi _export_b 0
loadi status 0
loadi _unexport_b 0
loadi _direction_b 0
loadi gpio_data 0
loadi direction 0
loadi pin 0
loadi _io_value 0
loadi _gpio_write_b 0
loadi _gpio_read_b 0
loadi _io_read_b 0
loadi _io_read 0

%func _export
%func _unexport
%func _direction
%func _gpio_write
%func _gpio_read

push _export
  loadr _export_b ip
  rmov sdx pin
  mov sfc 4
  invoke 0x5

  r_mv scr status       ; store status code
return _export

push _unexport
  loadr _unexport_b ip
  rmov sdx pin
  mov sfc 3
  invoke 0x5

  r_mv scr status       ; store status code
return _unexport

push _direction
  loadr _direction_b ip
  rmov sdx pin
  rmov tmp direction
  mov sfc 2
  invoke 0x5

  r_mv scr status       ; store status code
return _direction

push _gpio_write
  loadr _gpio_write_b ip
  rmov sdx pin
  rmov tmp _io_value
  mov sfc 1
  invoke 0x5

  r_mv scr status       ; store status code
return _gpio_write

push _gpio_read
   loadr _gpio_read_b ip
   rmov sdx _io_read
   mov sfc 0
   invoke 0x5

   r_mv scr gpio_data     ; store read pin data
return _gpio_read

; The program will simply read a signal input via raspberry pi's GPIO
reg 26 GPIO_IN ; these two will represent our GPIO i/o pins
reg 4 GPIO_OUT
reg 62 _export_pins
reg 160 _unexport_pins
reg 39 _main

include "GPIOController.ss"

loadi GPIO_IN 26               ; Here we assign the ram locations the physical GPIO(s)
loadi GPIO_OUT 4

loadi IN 0
loadi OUT 1

loadr PIN GPIO_IN
loadr POUT GPIO_OUT

loadi HIGH 1
loadi LOW 0

; Functions
%func _export_pins
%func _main
%func _gpio_direction
%func _unexport_pins

reg 10 err
reg 329 result
reg 929 repeat
loadi err 1
loadbl result
neg err                        ; convert err to -1

push _export_pins
	loadr pin PIN
	call _export                   ; export pin 26
	loadr _export _export_b              ; store backtrack
	same result err,status  ; export_status from gpio controller

	do result    ; if(-1 == Export(PIN))
	; print status err and close
           mov ebx 1
	   halt
	end

	loadr pin POUT
	call _export
	loadr _export _export_b             ; store backtrack
	same result err,status  ; export_status from sys/stat

	do result    ; if(-1 == Export(PIN))
	; print status err and close
            mov ebx 1
	    halt
	end
return _export_pins

push _unexport_pins
	loadr pin PIN
	call _unexport                   ; unexport pin 26
        loadr _unexport _unexport_b
	same result err,status  ; unexport_status from sys/stat

	do result    ; if(-1 == GPIOUNExport(PIN))
	; print status err and close
           mov ebx 4
	   halt
	end

	loadr pin POUT
	call _unexport
	same result err,status  ; export_status from sys/stat

	do result    ; if(-1 == GPIOUNExport(PIN))
	; print status err and close
           mov ebx 4
	   halt
	end
return _unexport_pins

push _gpio_direction
    loadr pin PIN
	loadr direction IN
	call _direction                   ; set direction pin 26
	loadr _direction _direction_b             ; store backtrack
	same result err,status  ; export_status from sys/stat

	do result    ; if(-1 == GPIODirection(PIN,IN))
	; print status err and close
           mov ebx 3
	   halt
	end

    loadr pin POUT
	loadr direction POUT
	call _direction
	loadr _direction _direction_b             ; store backtrack
	same result err,status  ; export_status from sys/stat

	do result    ; if(-1 == GPIODirection(POUT,OUT))
	; print status err and close
           mov ebx 3
	   halt
	end
return _gpio_direction

reg 200 io_write
reg 201 io_write_b
%func io_write

push io_write
    loadr _io_write_b ip
	loadr pin POUT
	loadi r20391 2
	rem r2193 repeat,r20391
	loadr _io_value r2193
	call _gpio_write                    ; write to pin 26
	loadr _gpio_write _gpio_write_b                  ; store backtrack
	same result err,status  ; write_status from sys/stat

	do result    ; if(-1 == GPIOWrite(POUT, repeat % 2))
	; print status err and close
           mov ebx 3
	   halt
	end
return io_write

reg 200 io_read
reg 201 io_read_b
%func io_read

push io_read
    loadr _io_read_b ip
	loadr _io_read PIN
	call _gpio_read                    ; read pin 26
	loadr _gpio_read _gpio_read_b                  ; store backtrack
return io_read

reg 190 _printf
reg 191 _printf_b

%func _printf

reg 100 length
push _printf
    loadr _printf_b ip
	str length "I'm reading " + gpio_data + " in GPIO " + PIN + "\n"     ; Assembler comand to get length of string
	printf length "I'm reading " + gpio_data + " in GPIO " + PIN + "\n"
return _printf

push _main
    call _export_pins
  call _gpio_direction
  loadr repeat 10
  mov sdx 1000
  rloop r50 r40 repeat
     call _io_write
	 loadr _io_write _io_write_b

     call _io_read
	 loadr _io_read _io_read_b

     call _printf
	 loadr _printf _printf_b

	 sleep                         ; sleap current thread for however mills in sdx
  endl r50 r40

  call _unexport_pins
return _main

call _main

halt
