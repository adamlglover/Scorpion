#include "cpu.h"
#include "core0/core0.h"
#include <iostream>
using namespace std;

C0 core0;
void CPU::Reset()
{
  core0.Reset();
}

void CPU::Halt()
{
  core0.Halt();
}

void CPU::Run()
{
  core0.run0();
}

