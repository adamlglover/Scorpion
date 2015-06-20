/**
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
* Virtual Digital microprocessor Designed by Braxton Nunnally
*
* Core: 0
* Model: RMD 8208
* Production Date: 3-15
* IFT: 4
* Architecture: RMDv1
*
* The RMD 8208 Microproccessor features a simple
* single core, 1 thread execution channel with a very loose
* structure with no syatax checcking, data protection,
* security, ect.
*
* This microprocessor was designed as the foundation of
* developing the Scorpion VM as a whole.
* 
*
* For full info visit "https://github.com/AndroDevcd/RPVM/blob/master/LINEUP.md"
*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include "../../var.h"
#include "core0.h"
#include "../../Ram/ram.h"
#include "gate.h"
#include <sstream>
#include "../../program.h"
#include "../../System.h"
#include "cpuf.h"
#include "runtime_exception.h"
#include "../../Log/filter.h"
#include <string>
using namespace std;

long EAX, TMP, IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2, SCR, AI, IPI, I3, I4, I5, I6, I7, I8, I9, I10, I11, I12;

clock_t tStart;
bool _0Halted, pass = false, scmnd = false,
     ignore = false, if_ignore = false,
     waiting = false, debugging = false,
     in_loop = false, in_func = false;
int passed_if = 0;

long *id;
long auto_ipi;
long long cycles = 0;
long IPH, IPL;
void fetch();
void execute();

Disassembler disasm;
Log lg;

long L1_ICache_length = 1024000;// to be used else where
#define L1_Cache_Size 1024000 // 1024kb L1 Instruction Cache
string L1_ICache[ L1_Cache_Size ];

extern string *program;
extern long SIZE;
void ucache()
{
   for(int i = 0; i < L1_Cache_Size; i++)
   {
      if(i > SIZE)
         break;

      if(L1_ICache[i] != program[i])
        L1_ICache[i] = program[i];
   }
}

bool reverse(bool cstate)
{
    if(!cstate)
      return true;
    else
      return false;
}

double reg_check_ret(long addr)
{
   switch( addr )
      {
          case 20:
            return EAX;
          break;
          case 21:
            return EBX;
           break;
           case 22:
            return SDX;
           break;
           case 23:
            return BP;
           break;
           case 24:
            return EXC;
           break;
           case 25:
            return PS;
           break;
           case 26:
            return LG;
           break;
           case 27:
            return LSL;
           break;
           case 28:
            return SFC;
           break;
           case 29:
            return SCX;
           break;
           case 30:
            return I1;
           break;
           case 31:
            return I2;
           break;
           case 32:
            return TMP;
           break;
           case 33:
            return AI;
           break;
           case 34:
            return IPI;
           break;
           case 35:
            return IP;
           break;
           case 37:
            return I3;
           break;
           case 38:
            return I4;
           break;
           case 39:
            return I5;
           break;
           case 40:
            return I6;
           break;
           case 41:
            return I7;
           break;
           case 42:
            return I8;
           break;
           case 43:
            return I9;
           break;
           case 44:
            return I10;
           break;
           case 45:
            return I11;
           break;
           case 46:
            return I12;
           break;
           default:
            return core0.getr(0, addr);
           break;
      }
}

void reg_check_set(long addr, double data)
{
     switch( addr )
      {
          case 20:
            EBX = (long) data;
           break;
           case 22:
            SDX = (long) data;
           break;
           case 23:
            BP = (long) data;
           break;
           case 24:
            EXC = (long) data;
           break;
           case 25:
            PS = (long) data;
           break;
           case 26:
            LG = (long) data;
           break;
           case 27:
            LSL = (long) data;
           break;
           case 28:
            SFC = (long) data;
           break;
           case 29:
            SCX = (long) data;
           break;
           case 30:
            I1 = (long) data;
           break;
           case 31:
            I2 = (long) data;
           break;
           case 32:
            TMP = (long) data;
           break;
           case 33:
            AI = (long) data;
           break;
           case 34:
            IPI = (long) data;
           break;
           case 37:
            I3 = (long) data;
           break;
           case 38:
            I4 = (long) data;
           break;
           case 39:
            I5 = (long) data;
           break;
           case 40:
            I6 = (long) data;
           break;
           case 41:
            I7 = (long) data;
           break;
           case 42:
            I8 = (long) data;
           break;
           case 43:
            I9 = (long) data;
           break;
           case 44:
            I10 = (long) data;
           break;
           case 45:
            I11 = (long) data;
           break;
           case 46:
            I12 = (long) data;
           break;
           default:
            core0.setr(0, addr, data);
           break;
    }
}

void sfinterrupt()
{
  fetch();
}

bool C0::ACTIVE()
{
  return reverse(_0Halted);
}

extern void _sys_color_init();
void C0::Reset()
{
  lg.v("System","RMD Atrix X1 340K Cortex processor core boot");
  lg.i("System","Wiping  Registers..");

  EAX = 0;
  TMP = 0;
  EBX = 0;
  SDX = 0;
  SFC = 0;
  BP  = 0;
  EXC = 1;  // standard program close
  PS  = 0;
  IPI = 0;
  LG  = 1; // logging
  LSL = 2; // verbose
  I1  = 0;
  AI  = 0;
  I2  = 0;
  I3  = 0;
  I4  = 0;
  I5  = 0;
  I6  = 0;
  I7  = 0;
  I8  = 0;
  I9  = 0;
  I10  = 0;
  I11  = 0;
  I12  = 0;
  SCR = 0; // system call i/o response code

  cycles = 0;

  id =  new long[ 4 ];
  id[0] = 8008; // processor id
  id[1] = 1; // # of cores
  id[2] = 4; // IFT
  id[3] = 315; // Production date

  _sys_color_init();
}

void C0::Halt()
{
  _0Halted = true;
  lg.v("System","RMD Atrix X1 340K Cortex processor halt");
  lg.i("System","Wiping  Registers..");

  EAX = 0;
  TMP = 0;
  SDX  = 0;
  BP  = 0;
  PS  = 0;
  LG  = 0;
  IPI = 0;
  AI  = 0;
  LSL  = 0;
  SCX  = 0;
  I1  = 0;
  I2  = 0;
  I3  = 0;
  I4  = 0;
  I5  = 0;
  I6  = 0;
  I7  = 0;
  I8  = 0;
  I9  = 0;
  I10  = 0;
  I11  = 0;
  I1  = 0;
  SCR = 0;
  cycles = 0;
}

Ram _Ram;
/* Methods used to easily talk to the ram */
double C0::getr(short cell_switch, long _addr)
{
     _Ram.CB = 2; // E
     _Ram.addr((long) _addr, false);
     _Ram.cell(cell_switch);

     return _Ram.data(0.0); // get data from ram
}

void C0::setr(short cell_switch, long _addr, double data)
{
    _Ram.CB = 1; // S
    _Ram.addr((long) _addr, false);
    _Ram.cell(cell_switch);

    _Ram.data(data);   // set data to ram
}


int C0::GetVirturalAddress()
{
  return IP;
}

double C0::GetTime()
{
  return (double)(clock() - tStart)/CLOCKS_PER_SEC;
}

struct timeval ustart, uend;

unsigned long long utime, useconds;

unsigned long long C0::Get_UTime()
{
    gettimeofday(&uend, NULL);
    useconds = uend.tv_usec - ustart.tv_usec;

    utime = useconds;
    return utime;
}

void C0::resetTime()
{
  tStart = clock();
}

void C0::reset_UTime()
{
  gettimeofday(&ustart, NULL);
}

void C0::Interrupt(double offset)
{
    if(_0Halted){
       _0Halted = false;
       core0.Reset();
    }
    if(offset < 0)
      offset *= -1;
     IP = (long) offset;
}

string prog(int set_enable, long index, string data)
{
  if(index < L1_Cache_Size)
    return L1_ICache[ index ]; // super fast instruction fetching
  else {
     _Ram.CB = set_enable; // E
     _Ram.addr(index, true);
     prog_data = data;
     _Ram.cell(5);
     _Ram.data(0.0);
     return prog_data;
  }
}

int memstat;
extern long offset;
Gate gate;
double instruction;
void fetch() // Ive managed to smush the fetch, decode, execute cycle into one method
{
   if(AI != 0){
      if((cycles % AI) == 0){
         auto_ipi = IP; // store previous ip pos
         IP = IPI;    // tell cpu to scamper off and do something random(usually used in multitasking)
      }
   }

   memstat = _Ram.prog_status(IP);
   if(memstat == Ram::DONE){
      C0 core;
      printf("Time taken: %.3fs ", (double) core.GetTime());
      cout << "(" << core0.Get_UTime() << ")\n";
      p_exit();
   }
   else if(memstat == Ram::RUNNING){
      instruction = disasm.disassemble(prog(2, IP++, ""));
      if(_0Halted && (instruction == 35)) {
         if(ignore)
           ignore = false;
        gate.route( instruction, disasm.disassemble(prog(2, IP++, "")),
                     disasm.disassemble(prog(2, IP++, "")), disasm.disassemble(prog(2, IP++, "")));
      }
      else if(_0Halted)
         return;
      cycles++;

      gate.route(instruction, disasm.disassemble(prog(2, IP++, "")),
                     disasm.disassemble(prog(2, IP++, "")), disasm.disassemble(prog(2, IP++, "")));
      return;
   }
   else {
    RuntimeException re;
    re.introduce("ProgramStateUndetectableException","hardware faliure: cannot determine the current state of the program");
   }
}

void C0::run0()
{
 tStart = clock();
 gettimeofday(&ustart, NULL);
 while(System::Running)
       fetch();
}

