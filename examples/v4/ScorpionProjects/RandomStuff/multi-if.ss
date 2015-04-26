; This file will test out nesting if statements

loadbl run0 false
;loadbl run2 true
;loadbl run3 true
do run0
   print 'in run0/n'
   do run2
     print 'in run2/n'
   end
   do run3
      print 'in run3/n'
      do run4
	     print 'in run4/n'
	  end
	  do run5 
	  ;{
	     print 'in run5/n'
		 do run6 
		 ;{
	        print 'in run6/n'
			do run7 
			;{
	          print 'in run7/n'
			;}  
	        end
		 ;}
	     end
	  ;} 
	  end
	  print 'endof run5/n'
   end
   print 'end of run3/n'
end

print 'out of run0/n'

halt

