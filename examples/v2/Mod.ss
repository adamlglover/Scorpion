reg 0 main
reg 1 x
reg 2 y
reg 3 result

%func main

push main
  loadi x 10
  loadi y 3
  loadi result 0

  rem result x,y
  printf 10 "result = " + (r,result)
return main

call main

halt
