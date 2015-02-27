#ifndef VCPU
#define VCPU
#include <string>
using namespace std;
extern bool Halted;
extern bool scmnd;
extern bool pass;
extern long REG_SIZE;
extern long reg[ 1200000 ];
extern long lreg[ 1200000 ];
extern long x_reg[ 1200000 ];
extern long flag[ 1200000 ];
extern long lflag[ 1200000 ];
extern long EAX,TMP,IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2;
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
        void _EBX(long);
        void _SDX(long);
        void _BP(long);
        void _EXC(long);
        void _PS(long);
        void _LG(long);
        void _LSL(long);
        void Halt();
        int GetVirturalAddress();
        void ExecuteInterrupt(long);
        bool GetFlag(int flag);
	void SetFlag(int flag);
        void SetReg(int REG);
        void run();
   };

#endif
