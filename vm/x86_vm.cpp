/*
* MMC4080 Virtural Machine 
* Designed and developed by Braxton Nunnally
*
* Manufacturer: RMD
* Microprocessor: RMD 8208
* RAM: DM3 101
* SRam: DM3 100(standard)
* Additional Hardware: Lx 2000
*
* For full info visit "https://github.com/AndroDevcd/RPVM/blob/master/LINEUP.md"
*/

#include <string>
#include <algorithm>
#include <iostream>
#include "ctime.h"
#include "help.h"
#include "program.h"
#include "CPU/cpu.h"
#include "bv.h"
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

int main( int argc, const char **file )
{
  
  prepargs();
  string arg = "";
  if(argc == 2){
    arg = file[1];
  }
  else if(argc == 1){
    if(isarg("-help"))
     handleargs();
  }

  status = mkdir("/usr/share/scorpion", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  status = mkdir("/usr/share/scorpion/disks", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  status = mkdir("/usr/share/scorpion/lib/src", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  if(isarg(arg))
     handleargs();
  else
    x86_log.prepare(VERBOSE,true);

  if(OK(argc, file))
      Start();
  else
     cout << "scorpion: fatal err occured!...check '/usr/share/scorpion/log.txt' for error and system information\nuse -help for a list of options." << endl;

    return 0;
}

