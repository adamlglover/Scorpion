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
#include "../../System.h"
#include "cpuf.h"
#include "runtime_exception.h"
#include "../../Log/filter.h"
#include "../x86Disassm/disassembler.h"
#include "../../Log/Log.h"
//#include "thread.h"
#include <string>
using namespace std;

long EAX, TMP, IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2, SCR, AI, IPI;

clock_t tStart;
clock_s t_clock;
bool _0Halted;
bool pass = false;
bool run = false;
bool scmnd = false;
bool ignore = false;
bool if_ignore = false;
bool waiting = false;

long *id;
long auto_ipi;
long IPH, IPL;
int fetch();
int decode();
int execute();

void x86Shutdown();

Disassembler disasm;
Log log;

long L1_ICache_length = 128000;// to be used else where
#define L1_Cache_Size 128000 // 128kb L1 Instruction Cache
string L1_ICache[ L1_Cache_Size ];

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
  SCR = 0; // system call i/o response code

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
}

void C0::Halt()
{
  _0Halted = true;
  log.v("System","Arm I-4 CPU halt");
  log.i("System","Wiping  Registers..");

  EAX = 0;
  TMP = 0;
  SDX  = 0;
  BP  = 0;
  PS  = 0;
  LG  = 0;
  IPI = 0;
  AI  = 0;
  LSL = 0;
  SCX = 0;
  SCR = 0;
  //Thread t;
  //t.Shutdown(); // shutdown all threads(except main)
}

/* Methods used to easily talk to the ram */
double C0::getr(short cell_switch, long _addr)
{
     Ram ram;
     ram.CB = 2; // E
     ram.addr((long) _addr, false);
     ram.cell(cell_switch);

     return ram.data(0.0); // get data from ram
}

void C0::setr(short cell_switch, long _addr, double data)
{
    Ram ram;
    ram.CB = 1; // S
    ram.addr((long) _addr, false);
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

void C0::Interrupt(double offset)
{
    if(_0Halted){
       _0Halted = false;
	   C0 cpu;
	   cpu.Reset();
    }
     IP = (long) offset;
     fetch();
     decode();
     execute();
}

int ProcessOperands()
{
   if(scmnd)
   cout << "processing operands {0:" << instruction << "} {1:" << reg1 << "} {2:" << reg2 << "} {3:" << reg3 << "}" << endl;
   Gate gate;
   return gate.route(instruction, reg1, reg2, reg3);
}

string prog(int set_enable, long index, string data)
{
     //   Thread t;
        RuntimeException re; // are we accessing restricted cpu instructions outside of the current thread?
    //    if(!(IP > IPH) || !(IP < IPL))
    //           re.introduce("ThreadAccesOutOfBoundsException", "failure to access instructions outside of thread");

        if(index < L1_Cache_Size)
           return L1_ICache[ index ]; // super fast instruction fetching
        else {
           Ram ram;
           ram.CB = set_enable; // E
           ram.addr(index, true);
           prog_data = data;
           ram.cell(5);
           ram.data(0.0);
           return prog_data;
        }
}

int memstat;
int fetch()
{
   if(AI != 0){
      if((t_clock.ticks % AI) == 0){
         auto_ipi = IP; // store previous ip pos
         IP = IPI;    // tell cpu to scamper off and do something random(usually used in multitasking)
      }
   }
   //Thread t;
   //t.notify();
   Ram ramm;
   memstat = ramm.prog_status(IP);
   if(memstat == Ram::DONE){
          if(!run){
             printf("Time taken: %.3fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
             p_exit();
          }
          else {
             while(true)
             {
               // do not shut down
               // run forever
             }
          }
   }
   else if(memstat == Ram::RUNNING){
      i1          = prog(2, IP++, "");
      i2          = prog(2, IP++, "");
      i3          = prog(2, IP++, "");
      i4          = prog(2, IP++, "");
   }
   else {
    RuntimeException re;
    re.introduce("ProgramStateUndetectableException","hardware faliure: cannot determine the current state of the program");
   }

   return ramm.prog_status(IP);
}

int decode()
{
   instruction = DisassemblerRead(i1);
   reg1        = DisassemblerRead(i2);
   reg2        = DisassemblerRead(i3);
   reg3        = DisassemblerRead(i4);
}

int execute()
{
	if(_0Halted && ((instruction >= 0 && instruction <= 3) || instruction == 35)) { }
    else if(_0Halted)
       return 0;
  t_clock.ticks++;
  return ProcessOperands();
}

void C0::run0()
{
 tStart = clock();
 Ram r;
// Thread t;
// t.create(0, 0, r.info(5));
// t.start(0);
 while(System::Running){
       fetch();
       decode();
       execute();
 }
}
