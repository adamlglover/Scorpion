

loadi file 0
&&idx_offset: 259                  ; allocate 259 addresses for file
loadi fcont 0                 
&&idx_offset: 100000               ; allocate 100,000 addresses for file's contents
loadi input 10 
&&idx_offset: 10 
loadi iostream 0
loadi in 1
loadi fmax 100000
loadbl contin false
loadi out 0
loadi response 0

.cat:
    r_mv ip cat_b   
    call assign_file
    cp assign_file assign_file_b
    rmov scx file_adr
    invoke 0x32 1
    r_mv scr response
    call request_iostream
    cp request_iostream request_iostream_b
    call handle_iostream
    cp handle_iostream handle_iostream_b
    ret
	
.assign_file:
    r_mv ip assign_file_b
    print 'file: '
	loadi file 259
	rln file '/n'
	adr file_adr file
    ret	
	
.handle_iostream:
    r_mv ip handle_iostream_b 
	same is_in iostream,in
	do is_in
	   print '(! -> exit) >  '
	   loadi fcont 100000
	   rln fcont '!'
       ilt fcont fmax                      ; input contents
	      adr fcont_adr fcont
	      rmov scx fcont_adr
	      invoke 0x33 1
		  invoke 0x33 2
		  invoke 0x33 3
		  return handle_iostream 1 
	   end 	   
	   print 'input err: input size too big!!'	   
	end
    same is_out iostream,out	
	do is_out ; --------------------------------------------------------------
	   adr fcont_adr fcont
	   
	   loadi file_exists 1 
	   same file_exists file_exists,response

	   do file_exists
		  rmov sdx fcont_adr
		  invoke 0x32 2               ; read to a file and store its contents in a temporary location
									
		  ilt file fmax               ; print file contents
	          invoke 0x32 6           ; load its contents to the ram 
		      invoke 0x32 3           ; clear the temporarily stored file
				     			      ; The VM can only handle 1 file at a time(unless you use a thread)
			  printf '<str,fcont>/n'
	          return handle_iostream 1
		  end

		  inlt file fmax
			   print 'err file size too big!!/n'
	           return handle_iostream 1
		  end
	   end
			
	   ndo file_exists
		   printf 'I//O err: file open failure. Response code:<v,response>'
		   mov ebx 110
	   end 
	end 
    ret 	
	
.request_iostream:
    r_mv ip request_iostream_b
    printf 'iostream for file: /'<str,file>/' (in//out) '
	loadi input 5
	rln input '/n'
	
	loadi hash 0                      ; the hash equavilent of istream 
	loadi ref 0
	adr ref input 
	inc ref 
	rloop hash_lp hash_lp_b input 
	    rload char ref
        add hash hash,char         ; hash += char;		
		inc ref
	endl hash_lp hash_lp_b
;	printf 'hash: <v,hash>/n'
	loadi i 215                        ; hash eq of 'in'
	same is_in i,hash
	do is_in
	   loadi iostream 1
	   return request_iostream 1
	end 
	loadi i 344                        ; hash eq of 'out'
	same is_out i,hash
	do is_out
	   loadi iostream 0
	   return request_iostream 1
	end 
	print 'input err, exting!/n'
	;rmov sdx request_iostream_b      
	;invoke 0xA 0 
	halt 
    ret	
	
