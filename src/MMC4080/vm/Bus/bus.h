#ifndef BUS
#define BUS
extern int pstatus;
extern int STATUS_OPEN;
extern int STATUS_BUSY;
extern int STATUS_INPUT;
extern int STATUS_BROKEN;

extern int DEVICE_UNKNOWN;
extern int DEVICE_BUSY;
extern int PORT_ADDRESS_UNKNOWN;

extern int STD_OUT;
extern int _VHD;
class Bus {
    public:
     void channel(int,long,long,long *input);
     int pt();
     void accessport(int);
     void output(int);
     int status(); 

};

#endif

