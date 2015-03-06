#include <iostream>
#include "../var.h"
#include "cpu.h"
#include "cpuf.h"
#include "gate.h"
#include <sstream>
#include "../program.h"
#include "../Ports/ports.h"
#include "../System.h"
#include "../cache.h"
#include "../Log/filter.h"
#include "../x86Disasm/disassembler.h"
#include "../Log/Log.h"
#include <string>
using namespace std;

#define  NUM_REGS 1200000  /* 1.2mb of ram */
long EAX, TMP, IP, EBX, SDX, SFC, SCX, BP, EXC, PS, LG, LSL, I1, I2;
long REG_SIZE = NUM_REGS;
long reg[ NUM_REGS ];
long x_reg[ NUM_REGS ];
long lreg[ NUM_REGS ];
long flag[ NUM_REGS ];
long lflag[ NUM_REGS ];

bool Halted;
bool pass = false;
bool scmnd = false;
bool ignore = false;
bool if_ignore = false;
bool waiting = false;
int accessedReg;

int fetch();
int decode();
int execute();

void x86Shutdown();

Disassembler disasm;
Log log;


bool CPU::ACTIVE()
{
  return Halted;
}

void CPU::_EAX(long data)
{
   EAX = data;
}

void CPU::_TMP(long data)
{
   TMP = data;
}

void CPU::_EBX(long data)
{
   EBX = data;
}

void CPU::_SDX(long data)
{
   SDX = data;
}

void CPU::_BP(long data)
{
  BP = data;
}

void CPU::_EXC(long data)
{
  EXC = data;
}

void CPU::_PS(long data)
{
  PS = data;
}

void CPU::_LG(long data)
{
  LG = data;
}

void CPU::_LSL(long data)
{
  LSL = data;
}


/* Instruction Set 4 */
   int instruction = 0;
   int reg1 = 0;
   int reg2 = 0;
   int reg3 = 0;

void CPU::_IP(long addr)
{
   IP = addr;
}

void CPU::Reset()
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

  for(int i = 0; i < NUM_REGS; i++)
     reg[i] = null;
  for(int i = 0; i < NUM_REGS; i++)
     lreg[i] = null;
   log.i("System","Cleaning flags..");
   for(int i = 0; i < NUM_REGS; i++)
     flag[i] = 0;
    for(int i = 0; i < NUM_REGS; i++)
     lflag[i] = 0;
}

bool CPU::GetFlag(int _flag)
{
  return (flag[ accessedReg ]) == _flag;
}

void CPU::SetFlag(int _flag)
{
  flag[ accessedReg ] = _flag;
}

void CPU::SetReg(int REG)
{
  accessedReg = REG;
}

void CPU::Halt()
{
  Halted = true;
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

  for(int i = 0; i < NUM_REGS; i++)
     reg[i] = null;
   log.i("System","Wiping flags..");
   for(int i = 0; i < NUM_REGS; i++)
     flag[i] = null;
}

long *ProcessedOperands()
{
   Cache m;
   long *operands;
   operands = new long [ m.size() ];
  for(int i = 0; i < m.size(); i++)
        operands[ i ] = m.prog(i);

   return operands;
}

int CPU::GetVirturalAddress()
{
  return IP;
}

int DisassemblerRead(long operand)
{
   return disasm.disassemble(operand);
}

void CPU::ExecuteInterrupt(long offset)
{
    if(Halted)
       Halted = false;

     IP = offset;
     fetch();
     decode();
     execute();
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
  if(Halted)
    return 0;
   Cache cache;
   memstat = cache.status(IP);
   if(memstat == Cache::DONE)
          p_exit();
   else {
      instruction   = cache.prog(IP++);
      reg1          = cache.prog(IP++);
      reg2          = cache.prog(IP++);
      reg3          = cache.prog(IP++);
   }

   return cache.status(IP);
}

int decode()
{
   if(Halted)
      return 0;

   instruction = DisassemblerRead(instruction);
   reg1        = DisassemblerRead(reg1);
   reg2        = DisassemblerRead(reg2);
   reg3        = DisassemblerRead(reg3);
}

int execute()
{
  if(Halted)
     return 0;

  return ProcessOperands();
}

void CPU::run()
{
 while(System::Running){
       fetch();
       decode();
       execute();
 }
}
