; This library module will write ti a file

; methods
; write(string file, string  ofstream)                  ; write a output stream to a file
; close()                                  ; close the file

; Handling Errors
; If there is a falal error while writing to the file, a ScorpionFileWriteExecption 
; will be thrown 

; If an error happens that is not fatal then the FResponsewill have the file write srsponse code to be handled

; Possible errors:
; -1 : file does not exist <fatal>
;  0/-1 : file open failure

                  ;****Variables****
loadi OFSTREAM 0  ; Hold the addr to the ofstream to be sent to the file
loadi FILE 0      ; The address to the filename

.write:
    rmov scx FILE		
    invoke 0x32 1                          ; is the file present?

    r_mv scr response
    loadi file_exists 1                   ; the response code we want back
    same file_exists file_exists,response
    do file_exists
      rmov scx OFSTREAM                   ; set the addr to the stream of data to set to the file
      invoke 0x33 1                       ; attempt to open the file
   
      loadi is_open 1
      r_mv scr response
      same is_open is_open,response       ; check if the file is open 
   
      do is_open
        invoke 0x33 2                     ; write to the file(overwrites the previous stream of data in file)
        invoke 0x33 3                     ; close the file
	    return write 1
      end	  
   
      ndo is_open
          print 'Scorpion I//O err: file: '
          call io_error                   ; print file_name
		  cp io_error io_error_b
		  printf' could not be open. Response code:<v,response>'
	      mov ebx 110
	      halt
      end
    end
    ndo file_exists
        print 'Scorpion I//O err: file not found err. File: '
         call io_error
		 cp io_error io_error_b
	    printf ' was not found. Response code:<v,response>'
	    mov ebx 110
	    halt
    end 
   ret

.io_error:
    r_mv ip io_error_b
    loadi i 0                       ; int i = 0;
	rload file_name FILE
	inc FILE
	r_mv ip for
	
	ilt i file_name                 ; i < file_name.length;
    	rload char FILE
	    printf '<c,char>'           ; System.print(file_name.at(i));
	    inc FILE
		inc i                       ; i++;
        rmov sdx for
        invoke 0xA 0                ; loop back up
	end		  
    ret   


    /* Assembler commands */
    &&rm_label: for 
    &&rm_label: file_name
    &&rm_label: char 
    &&rm_label: i
    &&rm_label: response
    &&rm_label: file_exists
    &&rm_label: is_open
