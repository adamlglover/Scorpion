#ifndef SYS_CLOCK
#define SYS_CLOCK

#include <string>
using namespace std;

class SystemClock {
       public:
        int prep(string name, int runtime);
        int begin(string name);

};

#endif
