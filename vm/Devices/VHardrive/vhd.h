#ifndef V_HARD_DRIVE
#define V_HARD_DRIVE

class VHD {
        public:
          int Write(int addr, long *input);
          int Process(int,long,long *input);

};

#endif

