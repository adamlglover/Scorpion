#include <string>
#include <stdlib.h>
#include "program.h"
#include "cache.h"
#include "rules.h"
#include "CPU/cpu.h"
#include <stdio.h>
using namespace std;

string PROG = "";
bool runnable = false;
void x86Shutdown();
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
 runnable = false;
}

void p_exit()
{
  if(EXC == 1){
    x86Shutdown();
    string pname = getname();
    printf("\nThe program %s exited with code %d\n", pname.c_str(), EBX);
    exit(1);
  }
}

void Program::Main() // entry point of application
{
  Cache Mem;
  Mem.wipe();
  Mem.load(PROG);
  Program Application;
  Application.Run();
}

