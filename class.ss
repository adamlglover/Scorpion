import <scorpion/lang/Boolean>

/*extern VirtualMachineStack.stackValue
extern VirtualMachineStack.push
extern Boolean.isBool
extern VirtualMachineStack.pop
extern VirtualMachineStack.create_stack
extern VirtualMachineStack.STACK_SIZE
*/

class: Main {
   .main:
     string str 'FalSE'
     adr VirtualMachineStack.stackValue str 
     call VirtualMachineStack.push
     call Boolean.isBool
     call VirtualMachineStack.pop
     printf 'bool isBool(<str,str>) -> <bl,VirtualMachineStack.stackValue>/n' 
	 
	 
     adr VirtualMachineStack.stackValue str 
     call VirtualMachineStack.push
	 loadi String.index 2
	 call String.at
     call VirtualMachineStack.pop
	 printf 'string: <str,str> at(2): <c,VirtualMachineStack.stackValue>/n'

	 string msg 'Hello'
	 string msg2 'Help'
	 adr VirtualMachineStack.stackValue msg
	 call VirtualMachineStack.push
	 adr VirtualMachineStack.stackValue msg2 
	 call VirtualMachineStack.push
	 call String.strcpy 
	 printf 'string msg = "<str,msg>";'
     ret
}

class: sys {
   .start_:
      loadi VirtualMachineStack.STACK_SIZE 1000
      call VirtualMachineStack.create_stack
      call Main.main
      ret
}

call sys.start_

halt
