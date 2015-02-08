#include <string>
#include <iostream>
#include "ctime.h"
#include "CPU/cpu.h"
#include "rules.h"
#include "System.h"
#include "Log/Log.h"
#include "Log/Logger.h"

using namespace std;
//using namespace CPU;

string bo_prog = "";
void x86(string prog)
{
  bo_prog = prog;
}
Log vm_log;
Logger logger1;
void Restart()
{
    System::Running = false;
    CPU mprocessor;
    vm_log.prepare(7,false);
    mprocessor.Reset();
    System::Running = true;
    System::SetupSystem();
}

void Start()
{
   CPU mprocessor;
   System::Running = true;
   vm_log.prepare(7,false);
   mprocessor.Reset();
   System::SetupSystem();
}

int main( int argc, const char **file )
{
  if(OK(argc, file)){
      Start();
     logger1.printStackTrace();
  }
  else
     logger1.printStackTrace();
   return 0;
}

