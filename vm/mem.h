#ifndef MEMORY
#define MEMORY

#include <string>
using namespace std;

   class Memory {
          public:
             void wipe();
             long size();
             long prog(long);
	     void load(string);
             static int DONE;
             static int RUNNING;
	     static int UNKNOWN;
             int status(long);

   };

#endif
