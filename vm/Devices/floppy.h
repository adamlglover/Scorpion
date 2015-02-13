#ifndef VM__FLOPPY_DRIVE
#define VM_FLOPPY_DRIVE

class Floppy {
        public:
          int Write(int addr, long *input);
          int Process(int,long,long *input);

};

#endif

