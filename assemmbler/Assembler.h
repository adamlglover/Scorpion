#ifndef _NATIVE_SCORPION_ASSEMBELR_
#define _NATIVE_SCORPION_ASSEMBLER_

#include <iostream>
#include <string>
using namespace std;

class Assembler {
    public:
      static bool compilation_terminated;
      static bool compile_only;

};

struct lmap {
    string name;
    string module;
    string _class;
    long index;
} ;

#endif
