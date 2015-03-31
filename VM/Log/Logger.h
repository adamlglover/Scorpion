#ifndef LOGGER
#define LOGGER

#include <string>
using namespace std;
 class Logger {
    public:
      void init(bool tofile);
      int println(int priority,string tag,string message);
      void printStackTrace();
 };
#endif
