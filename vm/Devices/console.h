#ifndef SVM_CONSOLE
#define SVM_CONSOLE

class Console {
	public:
 	  int Write(int addr, double *input);
          int Process(int,double,double *input);
          void Setup();

};

#endif
