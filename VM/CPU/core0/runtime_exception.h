#ifndef RUNTIME_EXCEPTION
#define RUNTIME_EXCEPTION

#include <string>
using namespace std;

class RuntimeException {
       public:
         void introduce(string exception, string message);
};

#endif
