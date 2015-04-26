#include <string>
#include <stdlib.h>
#include "program.h"
#include "Ram/ram.h"
#include "bv.h"
#include "CPU/cpu.h"
#include "CPU/core0/core0.h"
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
     cpu.Run();
 runnable = false;
}

void p_exit()
{
  x86Shutdown();
  if(EXC == 1){
    string pname = getname();
    printf("\nThe program %s exited with code %d\n", pname.c_str(), EBX);
  }
  exit(EBX);
}

void Program::Main() // entry point of application
{
  Ram Mem;
  Mem.prog_wipe();
  Mem.prog_load(PROG);
  PROG = "";
  Program Application;
  Application.Run();
}

