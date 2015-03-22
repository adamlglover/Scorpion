#include "bus.h"
#include <iostream>
#include "../Ports/ports.h"
#include "../Devices/VHardrive/vhd.h"
using namespace std;

long port = 0x0;
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

void Bus::channel(int addr, long device, double command, double *input)
{
  VHD vhd;
 if(command == 0){
      if(device == _VHD){ // Virtural Hardrive
          long linput[4];
          linput[0] = (long) input[0];
          linput[1] = (long) input[1];
          linput[2] = (long) input[2];
          linput[3] = (long) input[3];
          pstatus = vhd.Write(addr,linput);
      }
      else
          pstatus = DEVICE_UNKNOWN;
 }
 else {
    command--;
      if(device == _VHD){ // Virtural Hardrive
          long linput[4];
          linput[0] = (long) input[0];
          linput[1] = (long) input[1];
          linput[2] = (long) input[2];
          linput[3] = (long) input[3];
          pstatus = vhd.Process(addr,(long) command,linput);
      }
      else
          pstatus = DEVICE_UNKNOWN;
 }

 //  cout << "pstatus : " << pstatus  << " device " << device << " command " << command  << " addr " << addr << endl;
}

int Bus::status()
{
  return pstatus;
}

void Bus::output(long data)
{
  Ports pt;
  pt.seto(data);
}

long Bus::pt()
{
  return port; 
}

void Bus::accessport(long dest)
{
   port = dest;
}

