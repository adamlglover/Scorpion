#ifndef SYS_CACHE
#define SYS_CACHE

#include <string>
using namespace std;

   class Cache {
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
