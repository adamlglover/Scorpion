
string password 'dk3o399e3e'
loadi usr_passwd 0                            ; will be our passwd string for later
&&idx_offset: 500
loadbl HasPassword false

.passwd_request: ; fix assembler func bactracking
   adr ref usr_passwd
   loadi KEY 0
   loadi ENTER 13
   loadi ESCAPE 27
   loadi PASSWD_SIZE 0
   loadi usr_passwd 0
   loadi MAX_PASSWD_SIZE 500 
   
   loadbl has_key true
   mov i1 int                             ; do not display chars
   
   wloop has_key has_key_b
         invoke 0xC 0 
		 r_mv sdx KEY
		 same is_enter KEY,ENTER
		 do is_enter
		    print '/b /b/n'
		    return passwd_request 1 
		 end 
		 ndo is_enter
		     inc PASSWD_SIZE
			 inc usr_passwd
             inc ref
			 ilt PASSWD_SIZE MAX_PASSWD_SIZE
			     same is_excape KEY,ESCAPE
				 do is_excape
		            print '/b /b'
				 end 
				 ndo is_excape
			         r_load ref KEY              ; load passwd to string
                 end 					 
			 end
             inlt PASSWD_SIZE MAX_PASSWD_SIZE
                  print 'Access Denied!/n Password is too big! Exiting.'
				  mov ebx 1932013
				  neg ebx 
				  halt
             end 			 
		 end 
   endwl has_key has_key_b
   ret
   
.verify_passwd:
   strcp HasPassword usr_passwd,password
   ret   

.take_measures:
   do HasPassword
       return take_measures 1                ; do nothing
   end 
   ndo HasPassword
       print '/nAccess Denied./n'
	   breakp
	   rmov sdx SEAL_RETURN
	   cp take_measures take_measures_b      ; preserve method
	   invoke 0xA 0 
   end
   ret    

&&rm_label: ref
&&rm_label: KEY 
&&rm_label: ENTER   
&&rm_label: has_key
&&rm_label: is_enter
&&rm_label: has_key_b
&&rm_label: PASSWD_SIZE
&&rm_label: MAX_PASSWD_SIZE
