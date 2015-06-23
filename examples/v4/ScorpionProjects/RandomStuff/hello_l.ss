

string hello 'Hello World!'
cp str_len hello

adr ref hello 
inc ref 

loadi i 0
loadc l 'l'
r_mv ip for
ilt i str_len
    rload char ref 
	same sdx char,l 
	do sdx
	   print 'l, '   
	end 
	
	inc ref
	inc i
	rmov sdx for
	invoke 0xA 0
end 

halt

