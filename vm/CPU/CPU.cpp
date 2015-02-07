#include <iostream>
#include "cpu.h"
#include "cpuf.h"

#define  NUM_REGS 29
long EAX, TMP, IP;
long reg[ NUM_REGS ];
long flag[ NUM_REGS ];

bool Halted;
using namespace std;
int accessedReg;

CPUFlags flagger;

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
  inf("Arm I-4 CPU core boot");
  inf("Wiping  Registers..");
 
  EAX = 0;
  TMP = 0;
  IP  = 0;

  for(int i = 0; i < NUM_REGS; i++)
     reg[i] = 0;
   inf("Wiping flags..");
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
