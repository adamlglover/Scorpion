#include "ports.h"
#include "../Bus/bus.h"
using namespace std;

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

void Ports::port(long dest)
{
  Bus sysbus;
  sysbus.accessport(dest);
}
