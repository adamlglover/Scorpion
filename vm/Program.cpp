#include <string>
#include "program.h"
#include "mem.h"
#include "CPU/cpu.h"
using namespace std;

string PROG = "";
bool runnable = false;
void Program::Save(string prog)
{
   PROG = prog;
}

void Program::Runnable(bool run)
{
    runnable = run;
} 

void Program::Run()
{
  CPU cpu;
 if(runnable)
     cpu.run();
}

void Program::Main() // entry point of application
{
  Memory Mem;
  Mem.wipe();
  Mem.load(PROG);
  Program Application;
  Application.Run();
}
