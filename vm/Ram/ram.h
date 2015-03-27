#ifndef RAM
#define RAM

class Ram {
     public:
       static long CB;
       static short CS;
	   static int DONE;
       static int RUNNING;
	   static int UNKNOWN;
       int addr(long);
       int cell(short);
       double data(double);
       long info(int);
	   void prog_wipe();
	   void prog_load(string);
       int prog_status(long);
};

#endif 
