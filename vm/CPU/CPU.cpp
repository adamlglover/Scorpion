#include <iostream>
#include "cpu.h"
#include "cpuf.h"
#include "gate.h"
#include <sstream>
#include "../System.h"
#include "../mem.h"
#include "../Log/filter.h"
#include "../x86Disasm/disassembler.h"
#include "../Log/Log.h"

#define  NUM_REGS 0x272C  /* 10,028 */
long EAX, TMP, IP;
long reg[ NUM_REGS ];
long flag[ NUM_REGS ];

bool Halted;
bool scmnd = false;
bool ignore = false;
bool if_ignore = false;
bool waiting = false;
using namespace std;
int accessedReg;
int fetch();
int decode();
int execute();
void x86Shutdown();

CPUFlags flagger;
Disassembler disasm;
Log log;

void inf(string);

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

  for(int i = 0; i < NUM_REGS; i++)
     reg[i] = 0;
   log.i("System","Wiping flags..");
   for(int i = 0; i < NUM_REGS; i++)
     flag[i] = 0;
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

  for(int i = 0; i < NUM_REGS; i++)
     reg[i] = 0;
   log.i("System","Wiping flags..");
   for(int i = 0; i < NUM_REGS; i++)
     flag[i] = 0;
}

long *ProcessedOperands()
{
   Memory m;
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
   cout<< "processing operands {0:" << instruction << "} {1:" << reg1 << "} {2:" << reg2 << "} {3:" << reg3 << "}" << endl;
   Gate gate;
   return gate.route(instruction, reg1, reg2, reg3);
}

int memstat;
int fetch()
{
  if(Halted)
    return 0;
   Memory mem;
   memstat = mem.status(IP);
   if(memstat == Memory::DONE)
           System::Running = false;
   else {
      instruction   = mem.prog(IP++);
      reg1          = mem.prog(IP++);
      reg2          = mem.prog(IP++);
      reg3          = mem.prog(IP++);
   }

   return mem.status(IP);
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
