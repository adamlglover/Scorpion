#include "core0.h"
#include "runtime_exception.h"
#include "../../System.h"
#include "../../Bus/bus.h"
#include "../../program.h"
#include "../../var.h"
#include "io.h"
#include "../../Log/filter.h"
#include "../../Ports/ports.h"
#include "cpuf.h"
#include "../../Bus/bus.h"
#include "../../Log/Log.h"
#include "../../Ram/ram.h"
#include <sstream>
#include <iostream>
using namespace std;

C0 C;
Log d_log;
void loadi(long *pkg)
{
    //checkreg(pkg[0]);
    //checktype(flag[ pkg[0] ],pkg[1]);
      C.setr(0, pkg[0], pkg[1]);
}

void loadr(long *pkg)
{
       if(pkg[1] == 21)
          C.setr(0, pkg[0], EAX);
       else if(pkg[1] == 22)
          C.setr(0, pkg[0], IP);
      else if(pkg[0] == 22)
          IP = pkg[1];
       else
          C.setr(0, pkg[0], C.getr(0, pkg[1]));
}

int ibool(long);
void loadbl(long *pkg)
{
      //checkreg(pkg[0]);
    //checktype(flag[ pkg[0] ],pkg[1]);
          C.setr(0, pkg[0], ibool(pkg[1]));
}

void mv(long *pkg)
{
       if(pkg[1] == 21){
          C.setr(0, pkg[0], EAX);
          EAX = null;
       }
       else{
          C.setr(0, pkg[0], C.getr(0, pkg[1]));
          C.setr(0, pkg[1], null);
       }
}

void mov(long *pkg)
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

void rmov(long *pkg)
{
     switch( pkg[0] )
     {
          case 0:
             if(pkg[1] == 21)
               EBX = EAX;
            else
            EBX = C.getr(0, pkg[1]);
           break;
           case 1:
            if(pkg[1] == 21)
               SDX = EAX;
            else
              SDX = C.getr(0, pkg[1]);
           break;
           case 2:
             if(pkg[1] == 21)
               BP = EAX;
            else
            BP = C.getr(0, pkg[1]);
           break;
           case 3:
	     if(pkg[1] == 21)
               EXC = EAX;
            else
            EXC = C.getr(0, pkg[1]);
           break;
           case 5:
	     if(pkg[1] == 21)
               LG = EAX;
            else
            LG = C.getr(0, pkg[1]);
           break;
           case 6:
             if(pkg[1] == 21)
               LSL = EAX;
            else
            LSL =  C.getr(0, pkg[1]);
           break;
           case 7:
 	     if(pkg[1] == 21)
               SFC = EAX;
            else
            SFC = C.getr(0, pkg[1]);
           break;
           case 8:
	     if(pkg[1] == 21)
               SCX = EAX;
            else
            SCX = C.getr(0, pkg[1]);
           break;
           case 9:
             if(pkg[1] == 21)
               I1 = EAX;
            else
            I1 = C.getr(0, pkg[1]);
           break;
           case 10:
             if(pkg[1] == 21)
               I2 = EAX;
            else
            I2 = C.getr(0, pkg[1]);
           break;
     }
}

void _init(long *pkg)
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
       RuntimeException re;
       re.introduce("IllegalSystemCallExcpetion", "code is not a system call [" + ss.str() + "]");
       break;

     }
}

void _port(long *pkg)
{
   Ports p;
     switch( pkg[1] ) {
        case 0:
         if(pkg[0] == 22)
           EAX = p.geto();
         else
           C.setr(0, pkg[0], p.geto());
        break;
        case 1:
           if(pkg[0] == 22)
              p.seto(EAX);
         else
           p.seto(C.getr(0, pkg[0]));
        break;
       case 2:
      Bus b;
         if(pkg[0] == 22)
           EAX = b.status();
         else
           C.setr(0, pkg[0], b.status());
        break;
     }
}

Ram r;
void mlock(long *pkg)
{
      for(int i = 0; i < r.info(0); i++){
            if(C.getr(3, i) == 0){
	//	lreg[ i ] = reg[ i ];
                C.setr(2, i, C.getr(0, i));
            }
      }
      for(int i = 0; i < r.info(0); i++){
            if(C.getr(3, i) == 0){
          //      lflag[ i ] = flag[ i ];
                C.setr(4, i, C.getr(1, i));
            }
      }

}

void lock(long *pkg)
{
      if(C.getr(3, pkg[0]) == 0) {
          C.setr(2, pkg[0], C.getr(0, pkg[0]));
          C.setr(2, pkg[0], C.getr(0, pkg[0]));
         // lreg[ pkg[0] ] = reg[ pkg[0] ];
         // lflag[ pkg[0] ] = flag[ pkg[0] ];
      } // else log cannot lock excluded register #{r}
      else {
       stringstream ss;
       ss << pkg[0];
       d_log.v("System","warning Ram: lock err cannot lock excluded address into ram #{" + ss.str() + "}");
       EBX = 2;
      }
}

void xreg(long *pkg)
{
     if(C.getr(3, pkg[0]) == 0)
        C.setr(2, pkg[0], 1);
     else if(C.getr(3, pkg[0]) == 1)
        C.setr(0, pkg[0], 0);
}

void mulock(long *pkg)
{
      for(int i = 0; i < r.info(0); i++){
            if(C.getr(3, i) == 0)
                 C.setr(0, i, C.getr(2, i));
      }

      for(int i = 0; i < r.info(0); i++){
            if(C.getr(3, i) == 0)
                 C.setr(1, i, C.getr(4, i));
      }
}

void clx(long *pkg)
{
     for(int i = 0; i < r.info(0); i++)
           C.setr(3, i, 0);
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
       if(C.getr(0, pkg[1]) == 21)
         C.setr(0, pkg[0], tibool(EAX == C.getr(0, pkg[2])));
       else if(C.getr(0, pkg[2]) == 21)
         C.setr(0, pkg[0], tibool(C.getr(0, pkg[1]) == EAX));
       else
         C.setr(0, pkg[0], tibool(C.getr(0, pkg[1]) == C.getr(0, pkg[2])));
}

void ulock(long *pkg)
{
      if(C.getr(3, pkg[0]) == 0) {
         C.setr(0, pkg[0], C.getr(2, pkg[0]));
         C.setr(1, pkg[0], C.getr(4, pkg[0]));
      }
}

void rm(long *pkg)
{
      C.setr(0, pkg[0], null);
}

void func(long *pkg)
{
          C.setr(0, pkg[0], null);
          C.setr(1, pkg[0], FN);
}

void push(long *pkg)
{
          C.setr(0, pkg[0], IP);
          ignore = true;
}

void _return(long *pkg)
{
        if(ignore)
            ignore = false;
        else
         IP = (long) C.getr(0, pkg[0]);
}

void call(long *pkg)
{
          TMP = IP;
          IP = (long) C.getr(0, pkg[0]);
          C.setr(0, pkg[0], TMP);
}

void swp(long *pkg)
{
          TMP = C.getr(0, pkg[0]);
          C.setr(0, pkg[0], C.getr(0, pkg[1]));
          C.setr(0, pkg[1], TMP);
}

void eof(long *pkg)
{
      C.setr(1, pkg[0], OI);
}

void loop(long *pkg)
{
         C.setr(1, pkg[0], LP);
         C.setr(0, pkg[0], IP);
         C.setr(0, pkg[1], pkg[2]);
         waiting = true;
}

void wloop(long *pkg)
{
      if(C.getr(0, pkg[0]) == 1)
         C.setr(0, pkg[1], IP);
      else {
         pass = true;  // do not run the contents in the loop
         ignore = true;
      }
}

void endwl(long *pkg)
{
  if(pass){
     ignore = false;
     pass = false;
  }
  else if(!ignore && (C.getr(0, pkg[0]) == 1)) // loop again
       IP = C.getr(0, pkg[1]);
}

void rloop(long *pkg)
{
         C.setr(1, pkg[0], LP);
         C.setr(0, pkg[0], IP);
         C.setr(0, pkg[1], C.getr(0, pkg[2]));
         waiting = true;
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
   if(waiting){
      C.setr(0, pkg[0], (C.getr(0, pkg[1]) - 1));
    if(C.getr(0, pkg[1]) <= 0)
        waiting = false;
   else {
      IP = C.getr(0, pkg[0]);
   }
  }
}

void _do(long *pkg)
{
    if(C.getr(0, pkg[0]) == 1){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void ilt(long *pkg)
{
    if(C.getr(0, pkg[0]) < C.getr(0, pkg[1])){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void igt(long *pkg)
{
    if(C.getr(0, pkg[0]) > C.getr(0, pkg[1])){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void iltoeq(long *pkg)
{
    if(C.getr(0, pkg[0]) <= C.getr(0, pkg[1])){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void igtoeq(long *pkg)
{
    if(C.getr(0, pkg[0]) >= C.getr(0, pkg[1])){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void ndo(long *pkg)
{
    if(C.getr(0, pkg[0]) == 0){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void inlt(long *pkg)
{
    if(!(C.getr(0, pkg[0]) < C.getr(0, pkg[1]))){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void ingt(long *pkg)
{
    if(!(C.getr(0, pkg[0]) > C.getr(0, pkg[1]))){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void inltoeq(long *pkg)
{
    if(!(C.getr(0, pkg[0]) <= C.getr(0, pkg[1]))){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void ingtoeq(long *pkg)
{
    if((C.getr(0, pkg[0]) >= C.getr(0, pkg[1])) == false){}
    else {
      if_ignore = true;
      ignore = true;
    }
}

void neg(long *pkg)
{
    C.setr(0, pkg[0], (C.getr(0, pkg[0]) * -1));
}
