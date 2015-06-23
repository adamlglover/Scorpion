; This will be a simple file that will retrive some simple cpu information 

; Here we declare some global variables that will be used to 
; hold the cpu info
loadi PID 0         ; The processor Id
loadi NCORES 0      ; How many cores?
loadi IFT 0         ; Whats the Instruction Filter Type?(Usually 4)
loadi PDATE 0       ; When was the last Production date(m|day)
.cpu_info:
    cpuid           ; simply set some internal cpu values to the ebx,sdx,sfc, and eax registers
	r_mv eax PID
	r_mv sdx NCORES
	r_mv sfc IFT
	r_mv scx PDATE
    ret




