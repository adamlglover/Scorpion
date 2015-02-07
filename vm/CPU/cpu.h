#ifndef VCPU
#define VCPU

   class CPU {
      public:
        void Reset();
        bool ACTIVE();
        long _EAX();
	long _TMP();
	long _IP();
        bool GetFlag(int flag);
	void SetFlag(int flag);
        void SetReg(int REG);
   };

#endif
