#ifndef SEC_RAM
#define SEC_RAM

#include <string>
using namespace std;

   class SRam {
          public:
             void wipe();
             long size();
             string prog(long);
	     void load(string);
             static int DONE;
             static int RUNNING;
	     static int UNKNOWN;
             int status(long);

   };

#endif
