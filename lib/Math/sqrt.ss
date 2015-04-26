; This is a standard math lib file
; Calculate the square root of a number

; ****Variables****
; SQRT_NUM : the number
; SQRT_RESULT : the calculated answer

.math_sqrt:
   r_mv ip math_sqrt_b
   dload sqrt_t 2.0
   mov i1 11
   div SQRT_RESULT SQRT_NUM,sqrt_t
   dload sqrt_t 0.0
   
   loadbl sqrt_inz 1
   dload sqrt_tmp2 0.0
   loadi sqrt_tmp3 2
   mov i1 14
   wloop sqrt_inz sqrt_lp
      dload sqrt_tmp 0.0
      mov i1 11
      sub sqrt_tmp sqrt_t,SQRT_RESULT
      mov i1 14
	  same sqrt_inz sqrt_tmp,sqrt_tmp2
	  
	  mov i1 14
	  ndo sqrt_inz
	     cp sqrt_t SQRT_RESULT
         mov i1 12
		 div SQRT_RESULT SQRT_NUM,sqrt_t
		 add SQRT_RESULT SQRT_RESULT,sqrt_t
		 div SQRT_RESULT SQRT_RESULT,sqrt_tmp3
	  end
      mov i1 14
	  do sqrt_inz
	     loadbl sqrt_inz 0 
	  end
   endwl sqrt_inz sqrt_lp
   ret
   
   