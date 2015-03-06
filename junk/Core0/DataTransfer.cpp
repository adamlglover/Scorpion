#include "cpu.h"
#include "../System.h"
#include "../Bus/bus.h"
#include "../var.h"
#include "io.h"
#include "../Log/filter.h"
#include "../Ports/ports.h"
#include "cpuf.h"
#include "../Bus/bus.h"
#include "../Log/Log.h"
#include <sstream>
#include <iostream>
using namespace std;

CPU C;
Log d_log;
void loadi(long *pkg)
{
 if(!ignore){
      C.SetReg(pkg[0]);
    //checkreg(pkg[0]);
    //checktype(flag[ pkg[0] ],pkg[1]);
      reg[ pkg[0] ] = pkg[1];
 }
}

void loadr(long *pkg)
{
   if(!ignore){
      C.SetReg(pkg[0]);
      
       if(pkg[1] == 21)
          reg[ pkg[0] ] = EAX;
       else if(pkg[1] == 22)
          reg[ pkg[0] ] = IP;
      else if(pkg[0] == 22)
          IP = pkg[1];
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
      //checkreg(pkg[0]);
    //checktype(flag[ pkg[0] ],pkg[1]);
          reg[ pkg[0] ] = ibool(pkg[1]);
   }
}

void mv(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
       if(pkg[1] == 21){
          reg[ pkg[0] ] = EAX;
          EAX = null;
       }
       else{
          reg[ pkg[0] ] = reg[ pkg[1] ];
	  reg[ pkg[1] ] = null;
       }
   }
}

void mov(long *pkg)
{
  if(!ignore)
   {
      switch( pkg[0] )
      {
          case 0:
	    EBX = pkg[1];
           break;
  	   case 1:
	    SDX = pkg[1];
           break;
	   case 2:
	    BP = pkg[1];
           break;
 	   case 3:
	    EXC = pkg[1];
           break;
	   case 4:
	    PS = pstatus;
           break;
	   case 5:
	    LG = pkg[1];
           break;
  	   case 6:
	    LSL = pkg[1];
           break;
           case 7:
	    SFC = pkg[1];
           break;
           case 8:
            SCX = pkg[1];
           break;
           case 9:
            I1 = pkg[1];
           break;
           case 10:
            I2 = pkg[1];
           break;
      }
   }
}

void rmov(long *pkg)
{
  if(!ignore)
  {
     switch( pkg[0] )
     {
          case 0:
             if(pkg[1] == 21)
               EBX = EAX;
            else
            EBX = reg[ pkg[1] ];
           break;
           case 1:
            if(pkg[1] == 21)
               SDX = EAX;
            else
              SDX = reg[ pkg[1] ];
           break;
           case 2:
             if(pkg[1] == 21)
               BP = EAX;
            else
            BP = reg[ pkg[1] ];
           break;
           case 3:
	     if(pkg[1] == 21)
               EXC = EAX;
            else
            EXC = reg[ pkg[1] ];
           break;
           case 5:
	     if(pkg[1] == 21)
               LG = EAX;
            else
            LG = reg[ pkg[1] ];
           break;
           case 6:
             if(pkg[1] == 21)
               LSL = EAX;
            else
            LSL = reg[ pkg[1] ];
           break;
           case 7:
 	     if(pkg[1] == 21)
               SFC = EAX;
            else
            SFC = reg[ pkg[1] ];
           break;
           case 8:
	     if(pkg[1] == 21)
               SCX = EAX;
            else
            SCX = reg[ pkg[1] ];
           break;
           case 9:
             if(pkg[1] == 21)
               I1 = EAX;
            else
            I1 = reg[ pkg[1] ];
           break;
           case 10:
             if(pkg[1] == 21)
               I2 = EAX;
            else
            I2 = reg[ pkg[1] ];
           break;
     }
  }
}

void _init(long *pkg)
{
  if(!ignore)
  {
     switch( pkg[0] )
     {
       case 0: // std out
       	 InputOutput io;
        long data[3];
        data[0] = SDX;
        data[1] = 0;
        data[2] = 0;
        Bus b;
        b.accessport(BP);
    //    cout << "port " << BP << " SFC " << SFC << " SCX  " << SCX << endl;
        io.Write(STD_OUT,SFC,SCX,data);
       break;
       case 1: // VHD write
         InputOutput _io;
        long idata[3];
        idata[0] = SDX;
        idata[1] = I1;
        idata[2] = I2;
        Bus buss;
        buss.accessport(BP);
        _io.Write(_VHD,SFC,SCX,idata);
       break;
       case 2: // log
        Log _l;
        if(LG == 1)
          _l.On();
        else if(LG == 0)
          _l.Shutdown();

        SetPriority(LSL);
       break;
       default:
       stringstream ss;
       ss << pkg[0];
       Log ll;
       ll.v("System","System call failure: code is not a system call *^" + ss.str());
       break;

     }
  }
}

void _port(long *pkg)
{
  if(!ignore) {
   Ports p;
     switch( pkg[1] ) {
        case 0:
         if(pkg[0] == 22)
           EAX = p.geto();
         else
           reg[pkg[0]] = p.geto();
        break;
        case 1:
           if(pkg[0] == 22)
              p.seto(EAX);
         else
           p.seto(reg[pkg[0]]);
        break;
       case 2:
      Bus b;
         if(pkg[0] == 22)
           EAX = b.status();
         else
           reg[pkg[0]] = b.status();
        break;
     }
  }
}

void mlock(long *pkg)
{
  if(!ignore)
   {
      for(int i = 0; i < REG_SIZE; i++){
            if(x_reg[i] == 0)
		lreg[ i ] = reg[ i ];
      }
      for(int i = 0; i < REG_SIZE; i++){
            if(x_reg[i] == 0)
                lflag[ i ] = flag[ i ];
      }
   }

}

void lock(long *pkg)
{
  if(!ignore)
   {
      if(x_reg[ pkg[0] ] == 0) {
          lreg[ pkg[0] ] = reg[ pkg[0] ];
          lflag[ pkg[0] ] = flag[ pkg[0] ];
      } // else log cannot cock excluded register #{r}
   }
}

void xreg(long *pkg)
{
   if(!ignore)
   {
     if(x_reg[ pkg[0] ] == 0)
        x_reg[ pkg[0] ] == 1;
     else if(x_reg[ pkg[0] ] == 1)
        x_reg[ pkg[0] ] == 0;
   }
}

void mulock(long *pkg)
{
  if(!ignore)
   {
      for(int i = 0; i < REG_SIZE; i++){
            if(x_reg[i] == 0)
                 reg[ i ] = lreg[ i ];
      }

      for(int i = 0; i < REG_SIZE; i++){
            if(x_reg[i] == 0)
                 flag[ i ] = lflag[ i ];
      }
   }
}

void clx(long *pkg)
{
  if(!ignore)
  {
     for(int i = 0; i < REG_SIZE; i++)
           x_reg[ i ] = 0;
  }
}

int tibool(bool val)
{
   if(val)
      return 1;
  else
      return 0;
}

void same(long *pkg)
{
    if(!ignore)
    {
       if((reg[1] == 21) || (reg[2] == 21))
         reg[ pkg[0] ] = tibool(EAX == reg[ pkg[2] ]);
       else
         reg[ pkg[0] ] = tibool(reg[ pkg[1] ] == reg[ pkg[2] ]);
    }
}

void ulock(long *pkg)
{
  if(!ignore)
   {
      if(x_reg[ pkg[0] ] == 0) {
         reg[ pkg[0] ] = lreg[ pkg[0] ];
        flag[ pkg[0] ] = lflag[ pkg[0] ];
      }
   }
}

void rm(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
      reg[ pkg[0] ] = null;
   }
}

void func(long *pkg)
{
  if(!ignore)
   {
      C.SetReg(pkg[0]);
          reg[ pkg[0] ] = null;
          C.SetFlag(FN);
   }
}

void push(long *pkg)
{
          C.SetReg(pkg[0]);
          reg[ pkg[0] ] = IP;
          ignore = true;
}

void _return(long *pkg)
{
    //  C.SetReg(pkg[0]);
        if(ignore)
            ignore = false;
        else
         IP = reg[ pkg[0] ];
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
      C.SetFlag(OI);
   }
}

void loop(long *pkg)
{
  if(!ignore)
  {
      C.SetReg(pkg[0]);
         C.SetFlag(LP);
         reg[ pkg[0] ] = IP;
         reg[ pkg[1] ] = pkg[2];
         waiting = true;
  }
}

void wloop(long *pkg)
{
  if(!ignore)
  {
      if(reg[ pkg[0] ] == 1)
         reg[ pkg[1] ] = IP;
      else {
         pass = true;  // do not run the contents in the loop
         ignore = true;
      }
  }
}

void endwl(long *pkg)
{
  if(pass){
     ignore = false;
     pass = false;
  }
  else if(!ignore && (reg[ pkg[0] ] == 1)) // loop again
       IP = reg[ pkg[1] ];
}

void rloop(long *pkg)
{
  if(!ignore)
  {
      C.SetReg(pkg[0]);
         C.SetFlag(LP);
         reg[ pkg[0] ] = IP;
         reg[ pkg[1] ] = reg[ pkg[2] ];
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
      reg[ pkg[1] ] -= 1;
    if(reg[pkg[1]] <= 0)
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
    if((reg[ pkg[0] ] >= reg[ pkg[1] ]) == false){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}

void neg(long *pkg)
{
  if(!ignore)
  {
    reg[ pkg[0] ] *= -1;
  }
}
