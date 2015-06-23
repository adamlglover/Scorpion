; This is a standard math lib file
; Calculate Factorial of a number

; ****Variables****
; FACT_NUM : the number to calc factorial
; FACT_RESULT : the calculated answer

.fact:
    r_mv ip fact_b
    t_cast FACT_NUM 1          ;  num = ((int) num)
    loadi FACT_RESULT 1
	loadi fact_num_check 0
	same fact_num_is_zero FACT_NUM,fact_num_check
	do fact_num_is_zero
	   return fact 1
	end 
	
	loadi fact_num_check 1
	same fact_num_is_zero FACT_NUM,fact_num_check
	do fact_num_is_zero
	   return fact 1
	end 
	
	loadi fact_num_check 0
	same fact_num_is_zero FACT_NUM,fact_num_check
	ilt FACT_NUM fact_num_check
	   print 'math lib err: cannot calculate factorial of a number /< 0/n'
	   return fact 1
	end 
	loadi fact_num 1
	loadi fact_temp 1
	cp fact_count FACT_NUM
    dec fact_count
    rloop fact_loop fact_count fact_count   ; FACT_RESULT = fact_num * (fact_num + 1)
	    cp fact_temp fact_num
		inc fact_temp
		mult FACT_RESULT fact_num,fact_temp
		inc fact_num
	endl fact_loop fact_count
    t_cast FACT_RESULT 1         
    ret
	
	