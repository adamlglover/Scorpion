#include "cpu.h"
#include "alu.h"
#include "gate.h"
#include "../Bus/bus.h"
#include "lu.h"
#include "datatrans.h"
#include "io.h"
#include "../program.h"
#include "../Ports/ports.h"
#include <sstream>
#include <iostream>
#include "../Log/Log.h"
#include "../System.h"
using namespace std;

void x86Shutdown();
int Gate::route(long instr, long r1,long r2, long r3)
{
   long pkg [3];
   pkg[0] = r1;
   pkg[1] = r2;
   pkg[2] = r3;

   CPU _cpu;
   switch( instr )
   {
  /*---System Control---*/
      case 0: // halt
       p_exit();
       if(scmnd)
      cout << "halt" << endl;
       break;
      case 1: // scmnd
         scmnd = true;
      cout << "scmnd" << endl;
       break;
      case 2: // rhalt
          _cpu.Reset();
       if(scmnd)
       cout << "rhalt" << endl;
        break;
       case 3: // chalt
	  _cpu.Halt();
       if(scmnd)
       cout << "chalt" << endl;
        break;

   /*---ALU---*/
       case 4:
         add(pkg);
       if(scmnd) 
       cout << "add" << endl;
        break;
       case 5:
         sub(pkg);
       if(scmnd)
       cout << "sub" << endl;
        break;
       case 6:
	 mult(pkg);
       if(scmnd)
       cout << "mult" << endl;
        break;
       case 7:
	 div(pkg);
       if(scmnd)
       cout << "div" << endl;
        break;
       case 8:
	 rem(pkg);
       if(scmnd)
       cout << "rem" << endl;
 	break;
       case 9:
         inc(pkg);
       if(scmnd)
       cout << "inc" << endl;
       break;
       case 10:
	 dec(pkg);
       if(scmnd)
       cout << "dec" << endl;
       break;

   /*---Logic Unit---*/
       case 11:
         and_l(pkg);
       if(scmnd)
       cout << "and" << endl;
       break;
       case 12:
         or_l(pkg);
       if(scmnd)
       cout << "or" << endl;
       break;
       case 13:
         xor_l(pkg);
       if(scmnd)
       cout << "xor" << endl;
       break;
       case 14:
         not_l(pkg);
       if(scmnd)
       cout << "not" << endl;
       break;
       case 15:
         nand_l(pkg);
       if(scmnd)
       cout << "nand" << endl;
       break;
       case 16:
         nor_l(pkg);
       if(scmnd)
       cout << "nor" << endl;
       break;
       case 17:
         xnor_l(pkg);
       if(scmnd)
       cout << "xnor" << endl;
       break;

  /*---Data Transfer---*/
        case 18:
         loadi(pkg);
       if(scmnd)
       cout << "loadi" << endl;
       break;
	 case 19:
         loadbl(pkg);
       if(scmnd)
       cout << "loadbl" << endl;
       break;
	 case 20:
         loadr(pkg);
       if(scmnd)
       cout << "loadr" << endl;
       break;
         case 21:
         mv(pkg);
       if(scmnd)
       cout << "mv" << endl;
       break;
	 case 22:
         rm(pkg);
       if(scmnd)
       cout << "rm" << endl;
       break;
	 case 23:
         func(pkg);
       if(scmnd)
       cout << "func" << endl;
       break;
	 case 24:
         push(pkg);
       if(scmnd)
       cout << "push" << endl;
       break;
	 case 25:
         _return(pkg);
       if(scmnd)
       cout << "return" << endl;
       break;
	 case 26:
         call(pkg);
       if(scmnd)
       cout << "call" << endl;
       break;
	 case 27:
         swp(pkg);
       if(scmnd)
       cout << "swp" << endl;
       break;
	 case 28:
         eof(pkg);
       if(scmnd)
       cout << "eof" << endl;
       break;
	 case 29:
         loop(pkg);
       if(scmnd)
       cout << "loop" << endl;
       break;
	 case 30:
         end();
       if(scmnd)
       cout << "end" << endl;
       break;
	 case 31:
         endl(pkg);
       if(scmnd)
       cout << "endl" << endl;
       break;
	 case 32:
         _do(pkg);
       if(scmnd)
       cout << "do" << endl;
       break;
   /*---Special commands---*/
        case 33: // mov
          mov(pkg);
       if(scmnd)
       cout << "mov" << endl;
         break;
        case 34: // rmov
	  rmov(pkg);
       if(scmnd)
       cout << "rmov" << endl;
        break;
        case 35: // init 
         _init(pkg);
       if(scmnd)
       cout << "init" << endl;
        break;
        case 36:
          ilt(pkg);
       if(scmnd)
       cout << "ilt" << endl;
        break;
        case 37:
        igt(pkg);
       if(scmnd)
       cout << "igt" << endl;
        break;
        case 38:
	 iltoeq(pkg);
       if(scmnd)
       cout << "iltoeq" << endl;
        break;
        case 39:
	igtoeq(pkg);
       if(scmnd)
       cout << "igtoeq" << endl;
        break;
        case 40:
        ndo(pkg);
       if(scmnd)
       cout << "ndo" << endl;
        break;
        case 41:
        inlt(pkg);
       if(scmnd)
	cout << "inlt" << endl;
	break;
        case 42:
	ingt(pkg);
       if(scmnd)
        cout << "ingt" << endl;
	break;
 	case 43:
	inltoeq(pkg);
       if(scmnd)
 	cout << "inltoeq" << endl;
	break;
	case 44:
 	ingtoeq(pkg);
       if(scmnd)
	cout << "ingtoeq" << endl;
	break;
        case 45:
        neg(pkg);
       if(scmnd)
        cout << "neg" << endl;
        break;
        case 46:
         cadd(pkg);
       if(scmnd)
       cout << "cadd" << endl;
        break;
       case 47:
         csub(pkg);
       if(scmnd)
       cout << "csub" << endl;
        break;
       case 48:
         cmult(pkg);
       if(scmnd)
       cout << "cmult" << endl;
        break;
       case 49:
         cdiv(pkg);
       if(scmnd)
       cout << "cdiv" << endl;
        break;
       case 50:
         crem(pkg);
       if(scmnd)
       cout << "crem" << endl;
        break;
       case 51:
          mlock(pkg);
       if(scmnd)
       cout << "mlock" << endl;
        break;
       case 52:
	  lock(pkg);
       if(scmnd)
       cout << "lock" << endl;
        break;
       case 53:
	  mulock(pkg);
       if(scmnd)
       cout << "mulock" << endl;
        break;
      case 54:
	  ulock(pkg);
       if(scmnd)
       cout << "ulock" << endl;
	break;
      case 55:
	  xreg(pkg);
       if(scmnd)
       cout << "xreg" << endl;
        break;
      case 56:
          clx(pkg);
       if(scmnd)
       cout << "clx" << endl;
        break;
       case 57:
	  rloop(pkg);
       if(scmnd)
       cout << "rloop" << endl;
        break;
       case 58:
          wloop(pkg);
       if(scmnd)
	cout << "wloop" << endl;
        break;
       case 59:
          endwl(pkg);
       if(scmnd)
	cout << "endwl" << endl;
	break;
       case 60:
           _port(pkg);
       if(scmnd)
	cout << "port" << endl;
        break;
       case 61:
           same(pkg);
       if(scmnd)
        cout << "same" << endl;
        break;
       case 62: // nac
       if(scmnd)
        cout << "nac" << endl;
       break;
       default:
         Log lg;
         cout << "Segmentation Fault" << endl;
         stringstream ss;
         ss << "cpu logic err: unknown command at {IP:" << _cpu.GetVirturalAddress() << "}. Shutting Down System...";
         lg.v("System", ss.str());
         x86Shutdown();
        break;
   }
   return 0;
}

