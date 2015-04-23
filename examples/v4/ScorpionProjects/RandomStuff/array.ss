; This file will express creatung an array

import <util/array-builder>

loadi num 0           ; int num[] = { 2, 3, 6, 1 };

; Build array
adr num num           ; set the address of num into num(its stupid, but we need the address to use to ref the array)
cp ARRAY_REF num   ; set the address for refrencing the array 
loadi ARRAY_SIZE 4    ; allocate 4 addresses for array
loadi ARRAY_TYPE 1    ; specify type int 
call build_array
cp build_array build_array_b
&&idx_offset: 5                    ; offset the assembler for setting unique variable id's to 5 units(prevents data collision)

; Set each element in the array
adr ref num           ; set the addr of num again( we use different var to keep array size in num)
cp ARRAY_REF ref      ; set the array ref
loadi ARRAY_INDEX 0
loadi ARRAY_VALUE 2   ; num[0] = 2;
call next_element
cp next_element next_element_b

cp ARRAY_REF ref      ; set the array ref
loadi ARRAY_INDEX 1
loadi ARRAY_VALUE 3   ; num[1] = 3;
call next_element
cp next_element next_element_b

cp ARRAY_REF ref      ; set the array ref
loadi ARRAY_INDEX 2
loadi ARRAY_VALUE 6   ; num[2] = 6;
call next_element
cp next_element next_element_b

cp ARRAY_REF ref      ; set the array ref
loadi ARRAY_INDEX 3
loadi ARRAY_VALUE 1   ; num[3] = 1;
call next_element
cp next_element next_element_b


; Print each element in the array
cp ARRAY_REF ref
loadi ARRAY_INDEX 0
call read_element
cp read_element read_element_b
printf 'int num[] = { <r,ARRAY_VALUE>, '

cp ARRAY_REF ref
loadi ARRAY_INDEX 1
call read_element
cp read_element read_element_b
printf '<r,ARRAY_VALUE>, '

cp ARRAY_REF ref
loadi ARRAY_INDEX 2
call read_element
cp read_element read_element_b
printf '<r,ARRAY_VALUE>, '

cp ARRAY_REF ref
loadi ARRAY_INDEX 3
call read_element
cp read_element read_element_b
printf '<r,ARRAY_VALUE> };'

; destroy array
cp ARRAY_REF ref
call destroy_array        
cp build_array build_array_b

halt
