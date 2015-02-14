#include "cpu.h"
#include <sstream>

CPU c;
void add(long *pckg)
{
 if(!ignore){
  if(pckg[0] == 21)
       EAX = pckg[1] + pckg[2];
   else
   {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ] = reg[ pckg[1] ] + reg[ pckg[2] ];
   }
  }
}

void sub(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
       EAX = pckg[1] / pckg[2];
   else
   {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ] = reg[ pckg[1] ] / reg[ pckg[2] ];
   }
 }
}

void inc(long *pckg)
{
 if(!ignore){
    if(pckg[0] == 21)
       EAX++;
   else
    {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ]++;
    }
  }
}

void dec(long *pckg)
{
  if(!ignore){
   if(pckg[0] == 21)
       EAX--;
   else
    {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ]--;
    }
  }
}

void mult(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
       EAX = pckg[1] * pckg[2];
   else
   {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ] = reg[ pckg[1] ] * reg[ pckg[2] ];
   }
  }
}

void div(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
       EAX = pckg[1] / pckg[2];
   else
   {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ] = reg[ pckg[1] ] / reg[ pckg[2] ];
   }
 }
}

void rem(long *pckg)
{
 if(!ignore){
   if(pckg[0] == 21)
       EAX = pckg[1] % pckg[2];
   else
   {
      c.SetReg(pckg[0]);
      reg[ pckg[0] ] = reg[ pckg[1] ] % reg[ pckg[2] ];
   }
 }
}

