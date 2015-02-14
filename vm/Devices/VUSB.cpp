#include "vusb.h"
#include "../Bus/bus.h"
#include <iostream>
using namespace std;

int loadBIOS(int);
int usbaddrs[1] = { 0x80 };
bool mounted[1] = { false };
int VUSB::Write(int addr, long *input)
{
 cout << "writing to usb" << endl;
 return STATUS_OPEN;
}


/* COMMANDS */
#define mount 1

// status codes
int USB_READY = 0x0000000012;
int BIOS_FAULT = 0x0000000013;
int DEVICE_NOT_MOUNTED = 0x0000000014;
int DEVICE_CORRUPTED = 0x0000000015;

int VUSB::Process(int addr, long command,long *input)
{
  if(addr == 0x80){
      switch( command ){
          case mount:
            return loadBIOS(addr);
          break;
      }
  }
  return STATUS_OPEN;
}
