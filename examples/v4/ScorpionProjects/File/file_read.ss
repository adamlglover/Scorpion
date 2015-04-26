
; This program will print out a file's contents


loadi file 0                ; This will be the pointer for the file
&&idx_offset: 100000        ; allocate 100,000 addresses for the file 
adr file_adr file           ; get the address of where the file will be stored
loadi file_max 100000

string file_name '//data//data.txt' ; /data/data.txt
adr file_name_adr file_name ; get the address of where the file name is located
					
rmov scx file_name_adr		
invoke 0x32 1               ; is the file present?

r_mv scr response           ; get the i/o response from attempting to open the file 
loadi file_exists 1 
same file_exists file_exists,response

do file_exists

    rmov sdx file_adr
    invoke 0x32 2           ; read to a file and store its contents in a temporary location
	invoke 0x32 6           ; load its contents to the ram 
	invoke 0x32 3           ; clear the temporarily stored file
                            ; The VM can only handle 1 file at a time(unless you use a thread)
							
    ilt file file_max       ; print file contents
	    print 'file: '
		
		loadi i 0           ; int i = 0;
		inc file_name_adr
		r_mv ip for
		ilt i file_name     ; i < file_name.length;
		    rload char file_name_adr
			printf '<c,char>'; System.print(file_name.at(i));
		    inc file_name_adr
			inc i           ; i++;
			rmov sdx for
			invoke 0xA 0    ; loop back up
		end
		
	    print '/n'
	    loadi i 0           ; int i = 0;
		inc file_adr
		r_mv ip for
		ilt i file          ; i < file.length;
		    rload char file_adr
			printf '<c,char>'; System.print(file.at(i));
		    inc file_adr
			inc i           ; i++;
			rmov sdx for
			invoke 0xA 0    ; loop back up
		end
    end

    inlt file file_max
        print 'err file size too big, extitig/n'
		halt
    end
end
	
ndo file_exists
    printf 'I//O err: file open failure. Response code:<v,response>'
	mov ebx 110
	halt
end 

halt
