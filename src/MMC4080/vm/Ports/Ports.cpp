#include "ports.h"
#include "../Bus/bus.h"
#include <iostream>
using namespace std;

int ports[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
* DATA
* 0 : reg1
* 1 : reg2
* 2 : reg3
*
* 3 : device
* 4 : format
* 5 : command
*/
void Ports::feed(long *data)
{
  Bus sbus;
  int usedport = sbus.pt();
  long input[4];
  input[0] = data[0];
  input[1] = data[1];
  input[2] = data[2];
  input[3] = data[4];
  sbus.channel(usedport, data[3], data[5],input);
}

void Ports::seto(int data)
{
 Bus _sbus;
 int port_n = _sbus.pt();
  switch( port_n ){
     case 0x80:  // V-HD
       ports[0] = data;
     break;
    case 0x30:
       ports[1] = data;
    break;
    case 0x32:
       ports[2] = data;
    break;
    case 0x36:
       ports[3] = data;
    break;
    case 0x39:
       ports[4] = data;
    break;
  }
}

int Ports::geto()
{
  Bus sbus;
  switch( sbus.pt() ){
     case 128:  // V-HD
       return ports[0];
     break;
    case 48:
       return ports[1];
    break;
    case 50:
       return ports[2];
    break;
    case 54:
       return ports[3];
    break;
    case 57:
       return ports[4];
    break;
    default:
       return -21937856; // null
    break;
  }
}

void Ports::port(long dest)
{
  Bus sysbus;
  sysbus.accessport(dest);
}
