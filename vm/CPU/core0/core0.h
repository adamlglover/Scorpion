#ifndef VCPU 
#define VCPU 
#include <string>
using namespace std;
extern bool _0Halted;
extern bool scmnd;
extern bool pass;
extern long EAX,TMP,IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2;
extern long *id;
extern string prog_data;
extern long L1_ICache_length;
extern string L1_ICache[ 1024000 ];
extern double L1_DCache[ 1024000 ];
extern double L1_fCache[ 1024000 ];

struct clock_s {
   long ticks;
   int nanos;
   short sec;
   short min;
   int hrs;
} ;
extern clock_s t_clock;
extern bool ignore;
extern bool if_ignore;
extern string prog(int set_enable, long index, string data);
extern bool waiting;
   class C0 {
      public:
        void Reset();
        bool ACTIVE();
        void Halt();
        void setr(short cell, long _addr, double data);
        double getr(short cell, long _addr);
        int GetVirturalAddress();
        void ExecuteInterrupt(double);
        void run0();
   };

#endif
