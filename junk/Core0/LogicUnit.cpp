#include "cpu.h"
#include <sstream>

CPU _CPU;
long _xor(int,int);
long _or(int,int);
long _and(int,int);
long _not(int);
long _nand(int,int);
long _nor(int,int);
long _xnor(int,int);

long _xor(int a, int b)
{
    if((_and(_not(a),b)) || (_and(a,_not(b))))
       return 1;
    else
       return 0;
}

long _or(int a, int b)
{
    if((a == 1) || (b == 1))
      return 1;
    else
      return 0;
}

long _and(int a, int b)
{
  if(a == b)
     return 1;
  else
     return 0;
}

long _not(int a)
{
   if(a == 1)
      return 0;
   else
      return 1;
}


long _nand(int a, int b)
{
    if(_and(a,b))
        return 0;
    else
        return 1;
}

long _nor(int a,int b)
{
   if(_or(a,b))
       return 0;
   else
       return 1;
}

long _xnor(int a, int b)
{
   if(_xor(a,b))
      return 0;
   else
      return 1;
}

int ibool(long num)
{
     if((num == 1) || (num == 0))
        return num;
     else if(num > 1)
        return 1;
     else
        return 0;
}


void nand_l(long *pckg)
{
  if(!ignore){
   if(pckg[0] == 21)
       EAX = _nand(ibool(pckg[1]),ibool(pckg[2]));
   else
   {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _nand(ibool(reg[ pckg[1] ]),ibool(reg[ pckg[2] ]));
   }
  }
}

void nor_l(long *pckg)
{
  if(!ignore){
   if(pckg[0] == 21)
     EAX = _nor(ibool(pckg[1]),ibool(pckg[2]));
   else
   {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _nor(ibool(reg[ pckg[1] ]),ibool(reg[ pckg[2] ]));
  }
 }
}

void xnor_l(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
       EAX = _xnor(ibool(pckg[1]),ibool(pckg[2]));
   else {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _xnor(ibool(reg[pckg[1]]),ibool(reg[pckg[2]]));
   }
 }
}

void and_l(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
       EAX = _and(ibool(pckg[1]),ibool(pckg[2]));
   else
   {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _and(ibool(reg[ pckg[1] ]),ibool(reg[ pckg[2] ]));
   }
 }
}

void or_l(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
     EAX = _or(ibool(pckg[1]),ibool(pckg[2]));
   else
   {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _or(ibool(reg[ pckg[1] ]),ibool(reg[ pckg[2] ]));
   }
 }
}

void xor_l(long *pckg)
{
 if(ignore){
   if(pckg[0] == 21)
       EAX = _xor(ibool(pckg[1]),ibool(pckg[2]));
   else {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _xor(ibool(reg[pckg[1]]),ibool(reg[pckg[2]]));
   }
 }
}

void not_l(long *pckg)
{
  if(!ignore){
     if(pckg[0] == 21)
       EAX = _not(ibool(pckg[1]));
   else {
      _CPU.SetReg(pckg[0]);
      reg[ pckg[0] ] = _not(ibool(reg[pckg[0]]));
   }
  }
}
