

loadi goal 250000 ; 250,000,000
loadi i 0
r_mv ip for
ilt i goal 
    inc i
	rmov sdx for 
	invoke 0xA 0    ; loop back
end

printf '<v,i>'








