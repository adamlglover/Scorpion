#include "io.h"
#include "core0.h"
#include "../../Ports/ports.h"
#include <string>
#include <iostream>
using namespace std;

void InputOutput::Write(int device, int format, int command, long *pkg)
{
   if(!ignore){
       Ports ports;
       long data[6];
       for(int i = 0; i < 3; i++)
          data[i] = pkg[i];
       data[3] = device;
       data[4] = format;
       data[5] = command;
       ports.feed(data);
   }
}
