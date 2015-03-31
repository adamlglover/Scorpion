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
