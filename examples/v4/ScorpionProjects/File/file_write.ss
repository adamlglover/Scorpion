
; this program will write to a file

string ofstream 'I have wrote to a file in scorpion!!/nBraxton Nunnally'
adr ofstream_adr ofstream              ; get the address of where the file will be stored

string file_name '//data//data.txt'    ; /data/data.txt
adr file_name_adr file_name            ; get the address of where the file name is located
					
rmov scx file_name_adr		
invoke 0x32 1                          ; is the file present?

r_mv scr response
loadi file_exists 1                    ; the response code we want back
same file_exists file_exists,response
do file_exists
   rmov scx ofstream_adr               ; set the addr to the stream of data to set to the file
   invoke 0x33 1                       ; open the file
   
   loadi is_open 1
   r_mv scr response
   same is_open is_open,response       ; check if the file is open 
   
   do is_open
      invoke 0x33 2                    ; write to the file(overwrites the previous stream of data in file)
      invoke 0x33 3                    ; close the file
	  halt
   end	  
   
   ndo is_open
       printf 'I//O err: file could not be open. Response code:<v,response>'
	   mov ebx 110
	   halt
   end
end
ndo file_exists
    printf 'I//O err: file not found err. Response code:<v,response>'
	mov ebx 110
	halt
end 
