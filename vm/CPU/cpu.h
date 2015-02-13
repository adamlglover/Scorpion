#ifndef VCPU
#define VCPU
#include <string>
using namespace std;
extern bool Halted;
extern bool scmnd;
extern long reg[ 0x272C ];
extern long EAX,TMP,IP;
extern bool ignore;
extern bool if_ignore;
extern bool waiting;
   class CPU {
      public:
        void Reset();
        bool ACTIVE();
        void _EAX(long);
	void _TMP(long);
	void _IP(long);
        void Halt();
        int GetVirturalAddress();
        void ExecuteInterrupt(long);
        bool GetFlag(int flag);
	void SetFlag(int flag);
        void SetReg(int REG);
        void run();
   };

#endif
