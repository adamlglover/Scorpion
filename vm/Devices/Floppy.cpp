#include "floppy.h"
#include "../Bus/bus.h"
#include <iostream>
using namespace std;

int Floppy::Write(int addr, long *input)
{
 cout << "writing to floppy" << endl;
 return STATUS_OPEN;
}

int Floppy::Process(int addr, long command,long *input)
{
  cout << "processing floppy" << endl;
  return STATUS_OPEN;
}

