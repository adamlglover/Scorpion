#ifndef SEC_RAM
#define SEC_RAM

#include <string>
using namespace std;

   class SRam {
          public:
             void wipe();
             long size();
             void s_e(int);
             int addr(long index);
             string modify(string);
	     void load(string);
             static int DONE;
             static int RUNNING;
	     static int UNKNOWN;
             static int CB;
             int status(long);

   };

#endif
