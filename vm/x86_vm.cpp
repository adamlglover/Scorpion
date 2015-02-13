#include <string>
#include <iostream>
#include "ctime.h"
#include "CPU/cpu.h"
#include "rules.h"
#include "System.h"
#include "Log/Log.h"
#include "Log/Logger.h"
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;
//using namespace CPU;

int status;
int STACK_LEVEL = 2;

Log x86_log;
Logger logger1;

void Restart()
{
    System::Running = false;
    CPU mprocessor;
    mprocessor.Reset();
    System::Running = true;
    System::SetupSystem();
}

void x86Shutdown()
{
  System::Running = false;
  CPU mprocessor;
  mprocessor.Halt();
  Log lg;
  lg.Shutdown();
}

void Start()
{
   CPU mprocessor;
   System::Running = true;
   mprocessor.Reset();
   System::SetupSystem();
}

void help()
{
  cout << "Usage: svm [FILE]\n\n" << "[FILE]\nThe file must be in .bo format containing " <<
  "1's 0's and .'s this is considered an executable file define by the virtural machine." << endl;
}

int main( int argc, const char **file )
{
  status = mkdir("/usr/share/svm", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  x86_log.prepare(VERBOSE,true);
  string arg = "";

  if(argc == 2)
    arg = file[1];
  if((argc == 2) && (arg == "--help"))
       help();
  else if(OK(argc, file)){
      Start();
  }
  else
     cout << "svm: fatal err occured!...check '/usr/share/svm/log.txt' for error and system information or use svm --help for help on using this virtural machiene" << endl;

    return 0;
}

