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
#include "../../Log/filter.h"
#include "../../x86Disasm/disassembler.h"
#include "../../Log/Log.h"
#include <string>
using namespace std;

long EAX, TMP, IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2;

//clock_t tStart;
bool _0Halted;
bool pass = false;
bool scmnd = false;
bool ignore = false;
bool if_ignore = false;
bool waiting = false;

int fetch();
int decode();
int execute();

void x86Shutdown();

Disassembler disasm;
Log log;


/* Instruction Set 4 */
   int instruction = 0;
   int reg1 = 0;
   int reg2 = 0;
   int reg3 = 0;

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

string *ProcessedOperands()
{
   SRam m;
   string *operands;
   operands = new string [ m.size() ];
  for(int i = 0; i < m.size(); i++)
        operands[ i ] = m.prog(i);

   return operands;
}

/* Methods used to easily talk to the ram */
double C0::getr(long cell, long _addr)
{
  Ram ram;
  ram.CB = 2; // E
  ram.addr(_addr);

  return ram.data(cell,0.0); // get data from ram
}

void C0::setr(int cell, long _addr, double data)
{
  Ram ram;
  ram.CB = 1; // S
  ram.addr(_addr);

  ram.data(cell,data); // set data to ram
}


int C0::GetVirturalAddress()
{
  return IP;
}

int DisassemblerRead(string operand)
{
   return disasm.disassemble(operand);
}

void C0::ExecuteInterrupt(long offset)
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
//  cout<< "processing operands {0:" << instruction << "} {1:" << reg1 << "} {2:" << reg2 << "} {3:" << reg3 << "}" << endl;
   Gate gate;
   return gate.route(instruction, reg1, reg2, reg3);
}

int memstat;
int fetch()
{
  if(_0Halted)
    return 0;
   SRam sram;
   memstat = sram.status(IP);
   if(memstat == SRam::DONE){
  //        printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
          p_exit();
  }
   else {
      i1          = sram.prog(IP++);
      i2          = sram.prog(IP++);
      i3          = sram.prog(IP++);
      i4          = sram.prog(IP++);
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

  return ProcessOperands();
}

void C0::run0()
{ 
 //tStart = clock();
 while(System::Running){
       fetch();
       decode();
       execute();
 }
}
