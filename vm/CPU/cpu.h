#ifndef VCPU
#define VCPU
#include <string>
using namespace std;
extern bool Halted;
   class CPU {
      public:
        void Reset();
        bool ACTIVE();
        long _EAX();
	long _TMP();
	long _IP();
        void Halt();
        int GetVirturalAddress();
        void ExecuteInterrupt(long);
        bool GetFlag(int flag);
	void SetFlag(int flag);
        void SetReg(int REG);
        void run();
   };

#endif
