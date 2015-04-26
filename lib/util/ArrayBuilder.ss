; Native Array building module

; This module currently does not support string arrays
; Supported Arrays:
; short
; int
; char
; bool
; float
; double

; Basically all numeric types
; When assigning data to an array element
; the data will be casted based upon the given type 

; using ArrayBuilder module:
;
; 1: build array               (build_array)
; 2: assign array values       (next_element)
; 3: retrieve array values     (read_element)
; 4: destroy array(if needed)  (destroy_array) 
;
; note: if memory in your application is a concern DO_NOT use this module for 
; small arrays of 1 - 10 elements, as this module will take up alot more space 
; to build the array than just creating the variables manually.
            
; DO_NOT attempt to use this module without creating an array first as it may lead 
; to an app crash or data interference

; Important: 
; After building an array you MUST use &&idx_offset: <value> to offset the assembler 
; for assigning unique addresses for your variables(only offset assembler to the size of your array + 2)

; If this is not done, you WILL experience data interfierence

			            ; ****ARRAY-BUILDER-VARIABLES****
loadi ARRAY_REF 0       ; the ref address for the array
loadi ARRAY_SIZE 0      ; the size of the array
loadi ARRAY_TYPE 0      ; the element type for the array
loadi ARRAY_INDEX 0     ; the index of a specific element 
loadi ARRAY_VALUE 0     ; the value of an element agt the specified index 

                        ; ****ARRAY-TYPES****
loadi ARRAY_TYPE 0      ; the current array type(used for allocating resources for the array)						
loadi ARRAY_TYPE_SHORT 1  ; int array type
loadi ARRAY_TYPE_INT 2  ; int array type
loadi ARRAY_TYPE_CHAR 3  ; int array type
loadi ARRAY_TYPE_BOOL 4  ; int array type
loadi ARRAY_TYPE_FLOAT 5  ; int array type
loadi ARRAY_TYPE_DOUBLE 6  ; int array type


                                ; ****ARRAY-RESTRICTIONS****
loadi ARRAY_MAX_SIZE 1000000	; the max allocated size for each array
					    
.build_array: ; build an array
    r_mv ip build_array_b
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  igt ARRAY_SIZE ARRAY_MAX_SIZE
	   print 'ArraySizeOverloadExecption: the size of the array exceeds that max allowable size of 1 million units'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
	  end
	  r_load ARRAY_REF ARRAY_SIZE            ; dynamically set the refrenced address to the size of the array
	  inc ARRAY_REF
	  r_load ARRAY_REF ARRAY_TYPE_INT
	  return build_array 1
	end
	
	same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_SHORT
	do ARRAY_TYPE
	  igt ARRAY_SIZE ARRAY_MAX_SIZE
	   print 'ArraySizeOverloadExecption: the size of the array exceeds that max allowable size of 1 million units'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
	  end
	  r_load ARRAY_REF ARRAY_SIZE            ; dynamically set the refrenced address to the size of the array
	  inc ARRAY_REF
	  r_load ARRAY_REF ARRAY_TYPE_SHORT
	  return build_array 1
	end
	
	same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_CHAR
	do ARRAY_TYPE
	  igt ARRAY_SIZE ARRAY_MAX_SIZE
	   print 'ArraySizeOverloadExecption: the size of the array exceeds that max allowable size of 1 million units'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
	  end
	  r_load ARRAY_REF ARRAY_SIZE            ; dynamically set the refrenced address to the size of the array
	  inc ARRAY_REF
	  r_load ARRAY_REF ARRAY_TYPE_CHAR
	  return build_array 1
	end
	
	same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_BOOL
	do ARRAY_TYPE
	  igt ARRAY_SIZE ARRAY_MAX_SIZE
	   print 'ArraySizeOverloadExecption: the size of the array exceeds that max allowable size of 1 million units'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
	  end
	  r_load ARRAY_REF ARRAY_SIZE            ; dynamically set the refrenced address to the size of the array
	  inc ARRAY_REF
	  r_load ARRAY_REF ARRAY_TYPE_BOOL
	  return build_array 1
	end
	
	same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_FLOAT
	do ARRAY_TYPE
	  igt ARRAY_SIZE ARRAY_MAX_SIZE
	   print 'ArraySizeOverloadExecption: the size of the array exceeds that max allowable size of 1 million units'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
	  end
	  r_load ARRAY_REF ARRAY_SIZE            ; dynamically set the refrenced address to the size of the array
	  inc ARRAY_REF
	  r_load ARRAY_REF ARRAY_TYPE_FLOAT
	  return build_array 1
	end
	
	same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_DOUBLE
	do ARRAY_TYPE
	  igt ARRAY_SIZE ARRAY_MAX_SIZE
	   print 'ArraySizeOverloadExecption: the size of the array exceeds that max allowable size of 1 million units'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
	  end
	  r_load ARRAY_REF ARRAY_SIZE            ; dynamically set the refrenced address to the size of the array
	  inc ARRAY_REF
	  r_load ARRAY_REF ARRAY_TYPE_DOUBLE
	  return build_array 1
	end
	
	print 'ArrayTypeNotFoundExecption: the type of the array was not found'
	   mov ebx 1                             ; throw an exception(very bad, will change to exception throw module later)
	   halt
    ret
	
	
.array_cast:
    r_mv ip array_cast_b
	inc ARRAY_REF
	
	rload ARRAY_TYPE ARRAY_REF
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  t_cast ARRAY_VALUE 0              ; cast to short
	  dec ARRAY_REF
	  return array_cast 1
	end
	
	rload ARRAY_TYPE ARRAY_REF
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  t_cast ARRAY_VALUE 1              ; cast to int
	  dec ARRAY_REF
	  return array_cast 1
	end
	
	rload ARRAY_TYPE ARRAY_REF
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  t_cast ARRAY_VALUE 2              ; cast to float
	  dec ARRAY_REF
	  return array_cast 1
	end
	
	rload ARRAY_TYPE ARRAY_REF
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  t_cast ARRAY_VALUE 3              ; cast to double
	  dec ARRAY_REF
	  return array_cast 1
	end
	
	rload ARRAY_TYPE ARRAY_REF
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  t_cast ARRAY_VALUE 4              ; cast to char
	  dec ARRAY_REF
	  return array_cast 1
	end
	
	rload ARRAY_TYPE ARRAY_REF
    same ARRAY_TYPE ARRAY_TYPE,ARRAY_TYPE_INT
	do ARRAY_TYPE
	  t_cast ARRAY_VALUE 5              ; cast to bool
	  dec ARRAY_REF
	  return array_cast 1
	end
    ret 
	 
.destroy_array:
    r_mv ip destroy_array_b
	rload ARRAY_SIZE ARRAY_REF
	cp TMP_ARRAY_REF ARRAY_REF
	loadi ARRAY_INDEX 0
	loadi ELEMENT_DATA 0
	loadbl ELEMENT_EMPTY true
	inc ARRAY_REF
	inc ARRAY_SIZE                ; we do this to also empty the last element in the array
	wloop ELEMENT_EMPTY ELEMENT_EMPTY_B
	ige ARRAY_INDEX ARRAY_SIZE
	   loadbl ELEMENT_EMPTY false
	end
	inge ARRAY_INDEX ARRAY_SIZE ; empty element in array
	    r_load ARRAY_REF ELEMENT_DATA        ; dynamicly load the data at the curr index to 0
	    inc ARRAY_REF
		inc ARRAY_INDEX
	end
	endwl ELEMENT_EMPTY ELEMENT_EMPTY_B
	r_load TMP_ARRAY_REF ELEMENT_DATA
    ret	
	
.next_element: ; load data to an element in an array
    r_mv ip next_element_b
	call array_cast
    cp array_cast array_cast_b
    rload ARRAY_SIZE ARRAY_REF
	ige ARRAY_INDEX ARRAY_SIZE
	   print 'ArrayIndexOutOfBoundsExecption: array_index >= array size '
	   mov ebx 1
	   halt
	end
	
	loadi array_index_1 #0
	same array_index_1 ARRAY_INDEX,array_index_1
	do array_index_1
		inc ARRAY_REF
		inc ARRAY_REF
		r_load ARRAY_REF ARRAY_VALUE              ; load array at index with specified value 
		return next_element 1
	end
	loadi array_index_1 #1
	same array_index_1 ARRAY_INDEX,array_index_1
	do array_index_1
		inc ARRAY_REF
		inc ARRAY_REF
		inc ARRAY_REF
		r_load ARRAY_REF ARRAY_VALUE              ; load array at index with specified value 
		return next_element 1
	end
    ndo array_index_1
	    cp idx ARRAY_INDEX
		inc idx
		inc ARRAY_REF
		rloop element_search element_search_b idx
		   inc ARRAY_REF                         ; inc array ref to get to element index
		endl element_search element_search_b
		r_load ARRAY_REF ARRAY_VALUE              ; load array at index with specified value 
    end
    ret

.read_element: ; read an element from an array ref
    r_mv ip read_element_b
	call array_cast
    cp array_cast array_cast_b
    rload ARRAY_SIZE ARRAY_REF
	ige ARRAY_INDEX ARRAY_SIZE
	   print 'ArrayIndexOutOfBoundsExecption: array_index >= array size '
	   mov ebx 1
	   halt
	end
	
	loadi array_index_1 #0
	same array_index_1 ARRAY_INDEX,array_index_1
	do array_index_1
	    inc ARRAY_REF
		inc ARRAY_REF
		rload ARRAY_VALUE ARRAY_REF              ; load array at index with specified value
		return read_element 1
	end
	loadi array_index_1 #1
	same array_index_1 ARRAY_INDEX,array_index_1
	do array_index_1
	    inc ARRAY_REF
		inc ARRAY_REF
		inc ARRAY_REF
		rload ARRAY_VALUE ARRAY_REF              ; load array at index with specified value
		return read_element 1
	end
	ndo array_index_1
	    cp idx ARRAY_INDEX
		inc idx
		inc ARRAY_REF
		rloop element_search element_search_b idx
		   inc ARRAY_REF                         ; inc array ref to get to element index
		endl element_search element_search_b
		rload ARRAY_VALUE ARRAY_REF              ; load array at index with specified value 
	end	
    ret

	