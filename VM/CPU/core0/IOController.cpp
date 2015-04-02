#include "io.h"
#include "core0.h"
#include "../../GPIO/gpio.h"
#include <string>
#include <iostream>
using namespace std;

long InputOutput::Write(int device,  long *data)
{
   switch( device ) {
      case 0:  // GPIO
        return GPIOWrite(data[0], data[1]);
      break;
  }
   return 0;
}

long InputOutput::Read(int device,  long *data)
{
   switch( device ) {
      case 0:  // GPIO
        return GPIORead(data[0]);
      break;
  }
   return 0;
}
