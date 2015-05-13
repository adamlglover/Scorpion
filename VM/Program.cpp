/*
* Copyright 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/
#include <string>
#include <stdlib.h>
#include "program.h"
#include "Ram/ram.h"
#include "bv.h"
#include "CPU/cpu.h"
#include "CPU/core0/core0.h"
#include <stdio.h>
#include <iostream>
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
 else
  cout << "scorpion: fatal err: something went wrong wile attempting to run the program." << endl;
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

