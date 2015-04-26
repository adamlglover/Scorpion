; This is a standard math lib file
; Calculate Factorial of a number

; ****Variables****
; ABS_NUM : The number to take the abs() of 
; ABS_RESULT : the absolute value of the number 

.abs:
   r_mv ip abs_b
   t_cast ABS_NUM 1          ;  num = ((int) num)
   loadi ABS_ZERO 0
   loadi ABS_ONE 1
   ilt ABS_NUM ABS_ZERO      ; result = (num < 0) ? num*1 : num;
      mult ABS_RESULT ABS_NUM,ABS_ONE
	  return abs 1
   end
   cp ABS_RESULT ABS_NUM
   ret

   