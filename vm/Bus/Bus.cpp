#include "bus.h"
#include <iostream>
#include "../Ports/ports.h"
#include "../Devices/VHardrive/vhd.h"
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
int _VHD = 0x0000000068;

void Bus::channel(int addr, long device, long command, long *input)
{
  Console console;
  VHD vhd;
 if(command == 0){
      if(device == STD_OUT)  // std out
          pstatus = console.Write(addr,input);
      else if(device == _VHD) // Virtural Hardrive
          pstatus = vhd.Write(addr,input);
      else
          pstatus = DEVICE_UNKNOWN;
 }
 else {
    command--;
    if(device == STD_OUT)  // std out
          pstatus = console.Process(addr,command,input);
      else if(device == _VHD) // Virtural Hardrive
          pstatus = vhd.Process(addr,command,input);
      else
          pstatus = DEVICE_UNKNOWN;
 }

 //  cout << "pstatus : " << pstatus  << " device " << device << " command " << command  << " addr " << addr << endl;
}

int Bus::status()
{
  return pstatus;
}

void Bus::output(int data)
{
  Ports pt;
  pt.seto(data);
}

int Bus::pt()
{
  return port; 
}

void Bus::accessport(int dest)
{
   port = dest;
}

