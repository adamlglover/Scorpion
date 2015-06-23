; This is a standard math lib file
; Calculate the power of a number

; ****Variables****
; POW_NUM : the number
; POW_P : the power
; POW_RESULT : the calculated answer


.do_pow:
    r_mv ip do_pow_b
    wloop multiply math_wloop_b           ; while(multiply)
      same calc_pow pow_counter POW_P
      ndo calc_pow
        inc pow_counter
        mult POW_RESULT POW_RESULT POW_NUM
      end
      do calc_pow
        loadbl multiply 0   ; break;
      end
    endwl multiply math_wloop_b   
    ret

.pow:                       ; pow(x,num)
   r_mv ip pow_b
   loadi pow_number_check 0
   loadbl multiply 1        ; bool multiply = true
   loadi POW_RESULT 1
   loadi pow_counter 1

     same doPow POW_NUM pow_number_check      ; if(x == 0)
     do doPow
        loadi POW_RESULT 1
		return pow 1
     end

     igt  POW_NUM pow_number_check      ; if(x > 0)
        inc pow_number_check
        cp POW_RESULT POW_NUM  ; result = num
        same is1 POW_RESULT,pow_number_check   ; bool is1 = (x == 1) ? true : false;

        ; if(is1) 
        ; // do nothing

        ndo is1             ; if(!is1)
          call do_pow
          cp do_pow math_do_pow_b
        end
     end
    ret

	 