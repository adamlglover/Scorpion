#ifndef VCPU
#define VCPU
#include <string>
using namespace std;
extern bool _0Halted;
extern bool scmnd;
extern bool pass;
extern long EAX,TMP,IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2;
extern bool ignore;
extern bool if_ignore;
extern bool waiting;
   class C0 {
      public:
        void Reset();
        bool ACTIVE();
        void Halt();
        void setr(short cell, long _addr, double data);
        double getr(short cell, long _addr);
        int GetVirturalAddress();
        void ExecuteInterrupt(long);
        void run0();
   };

#endif
