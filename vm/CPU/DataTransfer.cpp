#include "cpu.h"
#include "../Bus/bus.h"
#include "io.h"
#include "../Log/filter.h"
#include "cpuf.h"
#include "../Bus/bus.h"
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
       if(pkg[1] == 21)
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
       if(pkg[1] == 21){
          reg[ pkg[0] ] = EAX;
          EAX = 0;
       }
       else{
          reg[ pkg[0] ] = reg[ pkg[1] ];
	  reg[ pkg[1] ] = 0;
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
           case 4:
	     if(pkg[1] == 21)
               LG = EAX;
            else
            LG = reg[ pkg[1] ];
           break;
           case 5:
             if(pkg[1] == 21)
               LSL = EAX;
            else
            LSL = reg[ pkg[1] ];
           break;
           case 6:
 	     if(pkg[1] == 21)
               SFC = EAX;
            else
            SFC = reg[ pkg[1] ];
           break;
           case 7:
	     if(pkg[1] == 21)
               SCX = EAX;
            else
            SCX = reg[ pkg[1] ];
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
       case 1: // VUSB write
         InputOutput _io;
        long idata[3];
        idata[0] = SDX;
        idata[1] = 0;
        idata[2] = 0;
        Bus buss;
        buss.accessport(BP);
        _io.Write(VDISK,SFC,SCX,idata);
       break;
       case 2: // log 
        Log _l;
        if(LG == 1)
          _l.On();
        else if(LG == 0) 
          _l.Shutdown();

        SetPriority(LSL);
       break;
       case 3:
        Log _lg;
        stringstream ss;
        ss << "program exited with code " << EBX;
        _lg.v("System",ss.str());
       break;
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
    if(!(reg[ pkg[0] ] >= reg[ pkg[1] ])){}
    else {
      if_ignore = true;
      ignore = true;
    }
  }
}
