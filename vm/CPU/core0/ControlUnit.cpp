/**
* Virtural CPU Designed by Braxton Nunnally
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
#include <iostream>
#include "../../var.h"
#include "core0.h"
#include "../../Ram/ram.h"
#include "gate.h"
#include <sstream>
#include "../../program.h"
#include "../../Ports/ports.h"
#include "../../System.h"
#include "../../sram.h"
#include "cpuf.h"
#include "runtime_exception.h"
#include "../../Log/filter.h"
#include "../../x86Disasm/disassembler.h"
#include "../../Log/Log.h"
#include <string>
using namespace std;

long EAX, TMP, IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2;

clock_t tStart;
clock_s t_clock;
bool _0Halted;
bool pass = false;
bool scmnd = true;
bool ignore = false;
bool if_ignore = false;
bool waiting = false;

long *id;
int fetch();
int decode();
int execute();

void x86Shutdown();

Disassembler disasm;
Log log;


/* Instruction Set 4 */
   double instruction = 0;
   double reg1 = 0;
   double reg2 = 0;
   double reg3 = 0;

   string i1 = "";
   string i2 = "";
   string i3 = "";
   string i4 = "";

bool reverse(bool cstate)
{
    if(!cstate)
      return true;
    else 
      return false;
}

bool C0::ACTIVE()
{
  return reverse(_0Halted);
}

void C0::Reset()
{
  log.v("System","Arm I-4 CPU core boot");
  log.i("System","Wiping  Registers..");

  EAX = 0;
  TMP = 0;
  IP  = 0;
  EBX = 0;
  SDX = 0;
  SFC = 0;
  BP  = 0;
  EXC = 1;  // standard program close
  PS  = 0;
  I1  = 0;
  I2  = 0;

  t_clock.ticks = 0;
  t_clock.nanos = 0;
  t_clock.sec = 0;
  t_clock.min = 0;
  t_clock.hrs = 0;

  id =  new long[ 4 ];
  id[0] = 8008; // processor id
  id[1] = 1; // # of cores
  id[2] = 4; // IFT
  id[3] = 315; // Production date
  Ram rm;
  C0 C;
   for(long i = 0; i < rm.info(0); i++)
         C.setr(1, i, OI); // allow all ram memory addresses to be open for input
}

void C0::Halt()
{
  _0Halted = true;
  log.v("System","Arm I-4 CPU halt");
  log.i("System","Wiping  Registers..");

  EAX = 0;
  TMP = 0;
  IP  = 0;
  SDX  = 0;
  BP  = 0;
  PS  = 0;
  LG  = 0;
  LSL = 0;
  SCX = 0;
}

/* Methods used to easily talk to the ram */
double C0::getr(short cell_switch, long _addr)
{
  Ram ram;
  ram.CB = 2; // E
  ram.addr((long) _addr);
  ram.cell(cell_switch);

  return ram.data(0.0); // get data from ram
}

void C0::setr(short cell_switch, long _addr, double data)
{
  Ram ram;
  ram.CB = 1; // S
  ram.addr((long) _addr);
  ram.cell(cell_switch);

  ram.data(data); // set data to ram
}


int C0::GetVirturalAddress()
{
  return IP;
}

double DisassemblerRead(string operand)
{
   return disasm.disassemble(operand);
}

void C0::ExecuteInterrupt(double offset)
{
    if(_0Halted)
       _0Halted = false;
     long tmp = IP;
     IP = offset;
     fetch();
     decode();
     execute();
     IP = tmp;
}

int ProcessOperands()
{
   cout<< "processing operands {0:" << instruction << "} {1:" << reg1 << "} {2:" << reg2 << "} {3:" << reg3 << "}" << endl;
   Gate gate;
   return gate.route(instruction, reg1, reg2, reg3);
}

string prog(int set_enable, long index, string data)
{
        SRam sr;
        sr.s_e(set_enable);
        sr.addr(index);

        return sr.modify(data);
}

int memstat;
int fetch()
{
  if(_0Halted)
    return 0;
   SRam sram;
   memstat = sram.status(IP);
   if(memstat == SRam::DONE){
          printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
          p_exit();
   }
   else if(memstat == SRam::RUNNING){
      i1          = prog(2, IP++, "");
      i2          = prog(2, IP++, "");
      i3          = prog(2, IP++, "");
      i4          = prog(2, IP++, "");
   }
   else {
    RuntimeException re;
    re.introduce("ProgramStateUndetectableException","hardware faliure: cannot determine the current state of the program");
   }

   return sram.status(IP);
}

int decode()
{
   if(_0Halted)
      return 0;

   instruction = DisassemblerRead(i1);
   reg1        = DisassemblerRead(i2);
   reg2        = DisassemblerRead(i3);
   reg3        = DisassemblerRead(i4);
}

int execute()
{
  if(_0Halted)
     return 0;
  t_clock.ticks++;
  return ProcessOperands();
}

void C0::run0()
{ 
 tStart = clock();
 while(System::Running){
       fetch();
       decode();
       execute();
 }
}
