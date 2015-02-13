#include "cpu.h"
#include "cpuf.h"
#include "../Log/Log.h"
#include <sstream>
CPUFlags flags;
CPU C;
Log d_log;
void loadi(long *pkg)
{
 if(!ignore){
      C.SetReg(pkg[0]);
      reg[ pkg[0] ] = pkg[1];
 }
}

void loadr(long *pkg)
{
   if(!ignore){
      C.SetReg(pkg[0]);
       if(pkg[1] == 11000)
          reg[ pkg[0] ] = EAX;
       else 
          reg[ pkg[0] ] = reg[ pkg[1] ];
   }
}

int ibool(long);
void loadbl(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
          reg[ pkg[0] ] = ibool(pkg[1]);
   }
}

void mv(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
       if(pkg[1] == 11000){
          reg[ pkg[0] ] = EAX;
          EAX = 0;
       }
       else{
          reg[ pkg[0] ] = reg[ pkg[1] ];
	  reg[ pkg[1] ] = 0;
       }
   }
}

void rm(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
      reg[ pkg[0] ] = 0;
   }
}

void func(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
          reg[ pkg[0] ] = 0;
          C.SetFlag(flags.FN);
   }
}

void push(long *pkg)
{
  if(!ignore)
   {
          C.SetReg(pkg[0]);
          reg[ pkg[0] ] = IP;
          ignore = true;
   }
}

void _return(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
        if(ignore)
            ignore = false;
        else
         IP = reg[ pkg[0] ];
   }
}

void call(long *pkg)
{
   if(!ignore)
   {
      C.SetReg(pkg[0]);
          TMP = IP;
          IP = reg[ pkg[0] ];
          reg[ pkg[0] ] = TMP;
   }
}

void swp(long *pkg)
{
 if(!ignore)
   {
      C.SetReg(pkg[0]);
          TMP = reg[ pkg[0] ];
          reg[ pkg[0] ] = reg[ pkg[1] ];
          reg[ pkg[1] ] = TMP;
   }
}

void eof(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
      C.SetFlag(flags.OI);
   }
}

void loop(long *pkg)
{
  if(!ignore)
  {
      C.SetReg(pkg[0]);
         C.SetFlag(flags.LP);
         reg[ pkg[0] ] = IP;
         reg[ pkg[1] ] = pkg[2];
         waiting = true;
  }
}

void end() // for do
{
      if(if_ignore){
          if_ignore = false;
          ignore = false;
      }
}

void endl(long *pkg)
{
 if(!ignore)
 {
   if(waiting){
      --reg[ pkg[1] ];
    if(reg[pkg[0]] <= 0)
        waiting = false;
    else {
      IP = reg[ pkg[0] ];
    }
   }
 }
}

void _do(long *pkg)
{
  if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(reg[ pkg[0] ] == 1){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void ilt(long *pkg)
{
  if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(reg[ pkg[0] ] < reg[ pkg[1] ]){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void igt(long *pkg)
{
 if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(reg[ pkg[0] ] > reg[ pkg[1] ]){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void iltoeq(long *pkg)
{
  if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(reg[ pkg[0] ] <= reg[ pkg[1] ]){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void igtoeq(long *pkg)
{
 if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(reg[ pkg[0] ] >= reg[ pkg[1] ]){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void ndo(long *pkg)
{
  if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(reg[ pkg[0] ] == 0){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void inlt(long *pkg)
{
 if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(!(reg[ pkg[0] ] < reg[ pkg[1] ])){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void ingt(long *pkg)
{
 if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(!(reg[ pkg[0] ] > reg[ pkg[1] ])){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void inltoeq(long *pkg)
{
 if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(!(reg[ pkg[0] ] <= reg[ pkg[1] ])){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void ingtoeq(long *pkg)
{
 if(!ignore)
  {
    C.SetReg(pkg[0]);
    if(!(reg[ pkg[0] ] >= reg[ pkg[1] ])){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}
