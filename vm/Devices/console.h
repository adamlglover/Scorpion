#ifndef VM_CONSOLE
#define VM_CONSOLE

class Console {
	public:
 	  int Write(int addr, long *input);
          int Process(int,long,long *input);
          void Setup();

};

#endif
