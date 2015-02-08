#include <iostream>
#include "cpu.h"
#include "cpuf.h"
#include "../Log/Log.h"

#define  NUM_REGS 29
long EAX, TMP, IP;
long reg[ NUM_REGS ];
long flag[ NUM_REGS ];

bool Halted;
using namespace std;
int accessedReg;

CPUFlags flagger;
Log log;

void inf(string);

bool CPU::ACTIVE()
{
  return Halted;
}

long CPU::_EAX()
{
  return EAX;
}

long CPU::_TMP()
{
   return TMP;
}

long CPU::_IP()
{
   return IP;
}

void CPU::Reset()
{
  log.v("System","Arm I-4 CPU core boot");
  log.v("System","Wiping  Registers..");
 
  EAX = 0;
  TMP = 0;
  IP  = 0;

  for(int i = 0; i < NUM_REGS; i++)
     reg[i] = 0;
   log.v("System","Wiping flags..");
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
