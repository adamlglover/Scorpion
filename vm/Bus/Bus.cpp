#include "bus.h"
#include <iostream>
#include "../Devices/vusb.h"
#include "../Devices/console.h"
using namespace std;

int port = 0x0;
int pstatus = 0;

// ststus codes
int STATUS_OPEN = 0x000000000;
int STATUS_BUSY = 0x000000001;
int STATUS_INPUT = 0x000000002;
int STATUS_BROKEN = 0x000000003;

int DEVICE_UNKNOWN = 0x000000004;
int DEVICE_BUSY = 0x000000005;
int PORT_ADDRESS_UNKNOWN = 0x000000006;

int STD_OUT = 0x0000000059;
int VDISK = 0x0000000068;

void Bus::channel(int addr, long device, long command, long *input)
{
  Console console;
  VUSB vir_usb;
 if(command == 0){
      if(device == STD_OUT)  // std out
          pstatus = console.Write(addr,input);
      else if(device == VDISK) // Digital USB
          pstatus = vir_usb.Write(addr,input);
      else
          pstatus = DEVICE_UNKNOWN;
 }
 else {
    if(device == STD_OUT)  // std out
          pstatus = console.Process(addr,command,input);
      else if(device == VDISK) // Digital USB
          pstatus = vir_usb.Process(addr,command,input);
      else
          pstatus = DEVICE_UNKNOWN;
 }

  // cout << "pstatus : " << pstatus << endl;
}

int Bus::pt()
{
  return port; 
}

void Bus::accessport(int dest)
{
   port = dest;
}

