;import 'util/time'
string password 'fe2ab7dee93'
loadi usr_passwd 0                            ; will be our passwd string for later
&&idx_offset: 500
loadi attempts 0
loadbl HasPassword false
loadi lightGreen 32
loadi noColor 38

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

.handleFault:
   inc attempts
   loadi FAULT_SIZE 5    
   same firstAttempt FAULT_SIZE,attempts
   do firstAttempt 
      print 'Error, Locking for 30 seconds '
	  print '[ ... ]/&'
	  dload SECS 30.000
      call delay  
      mov sdx 1
      printf '/b/b/b/b/b<col,lightGreen>done<col,noColor> ]/n'	   
   end 
   
   loadi FAULT_SIZE 10    
   same secondAttempt FAULT_SIZE,attempts
   do secondAttempt 
      print 'Error, Locking for 1 min '
	  print '[ ... ]/&'
	  dload SECS 60.000
      call delay  
      mov sdx 1
      printf '/b/b/b/b/b<col,lightGreen>done<col,noColor> ]/n'	  
   end 
   
   loadi FAULT_SIZE 15   
   same thirdAttempt FAULT_SIZE,attempts
   do thirdAttempt 
      print 'Error, Locking for 1 min and 30 seconds '
	  print '[ ... ]/&'
	  dload SECS 90.000
      call delay  
      mov sdx 1
      printf '/b/b/b/b/b<col,lightGreen>done<col,noColor> ]/n'	  
   end 
   
   loadi FAULT_SIZE 20
   
   same fourthAttempt FAULT_SIZE,attempts
   do fourthAttempt 
      print 'Error, Locking for 5 min '
	  print '[ ... ]/&'
	  dload SECS 300.000
      call delay  
      mov sdx 1
      printf '/b/b/b/b/b<col,lightGreen>done<col,noColor> ]/n'	  
   end 
   
   loadi FAULT_SIZE 25    
   igt attempts,FAULT_SIZE 
      print 'Error, too many attempts!/nShutting down application.'
      halt	  
   end 
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
	   call handleFault 
	   breakp
	   rmov sdx SEAL_RETURN
	   cp take_measures take_measuresb      ; preserve method
	   invoke 0xA 0 
   end
   ret    

