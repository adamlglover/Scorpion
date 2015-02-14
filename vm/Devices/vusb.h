#ifndef VM_USB_DRIVE
#define VM_USB_DRIVE

class VUSB {
        public:
          int Write(int addr, long *input);
          int Process(int,long,long *input);

};

#endif

