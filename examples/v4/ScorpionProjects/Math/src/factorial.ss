; Thisnprogram will calculate factorial

%include <Math/sqrt>

.main:
   loadi FACT_NUM 14
   call fact
   printf 'The factorial of <r,FACT_NUM> is <r,FACT_RESULT>/n'
   loadi POW_P 3
   loadi POW_NUM 4
   call pow
   printf '<r,POW_RESULT>/n'
   ret
   
call main

halt