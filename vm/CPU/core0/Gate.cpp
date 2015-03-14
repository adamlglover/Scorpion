#include "core0.h"
#include "alu.h"
#include "gate.h"
#include "../../Bus/bus.h"
#include "lu.h"
#include "datatrans.h"
#include "io.h"
#include "runtime_exception.h"
#include "../../program.h"
#include "../../Ports/ports.h"
#include <sstream>
#include <iostream>
#include "../../Log/Log.h"
#include "../../System.h"
using namespace std;

int Gate::route(long instr, long r1,long r2, long r3)
{
   long pkg [3];
   pkg[0] = r1;
   pkg[1] = r2;
   pkg[2] = r3;

   C0 _cpu;
   switch( instr )
   {
  /*---System Control---*/
      case 0: // halt
       if(!ignore)
       p_exit();
       if(scmnd && (!ignore))
      cout << "halt" << endl;
       break;
      case 1: // scmnd
       if(!scmnd)
         scmnd = true;
       else 
         scmnd = false;
      cout << "scmnd" << endl;
       break;
      case 2: // rhalt
       if(!ignore)
          _cpu.Reset();
       if(scmnd && (!ignore))
       cout << "rhalt" << endl;
        break;
       case 3: // chalt
       if(!ignore)
	  _cpu.Halt();
       if(scmnd && (!ignore))
       cout << "chalt" << endl;
        break;

   /*---ALU---*/
       case 4:
       if(!ignore)
         add(pkg);
       if(scmnd && (!ignore)) 
       cout << "add" << endl;
        break;
       case 5:
       if(!ignore)
         sub(pkg);
       if(scmnd && (!ignore))
       cout << "sub" << endl;
        break;
       case 6:
       if(!ignore)
	 mult(pkg);
       if(scmnd && (!ignore))
       cout << "mult" << endl;
        break;
       case 7:
       if(!ignore)
	 div(pkg);
       if(scmnd && (!ignore))
       cout << "div" << endl;
        break;
       case 8:
       if(!ignore)
	 rem(pkg);
       if(scmnd && (!ignore))
       cout << "rem" << endl;
 	break;
       case 9:
       if(!ignore)
         inc(pkg);
       if(scmnd && (!ignore))
       cout << "inc" << endl;
       break;
       case 10:
       if(!ignore)
	 dec(pkg);
       if(scmnd && (!ignore))
       cout << "dec" << endl;
       break;

   /*---Logic Unit---*/
       case 11:
       if(!ignore)
         and_l(pkg);
       if(scmnd && (!ignore))
       cout << "and" << endl;
       break;
       case 12:
       if(!ignore)
         or_l(pkg);
       if(scmnd && (!ignore))
       cout << "or" << endl;
       break;
       case 13:
       if(!ignore)
         xor_l(pkg);
       if(scmnd && (!ignore))
       cout << "xor" << endl;
       break;
       case 14:
       if(!ignore)
         not_l(pkg);
       if(scmnd && (!ignore))
       cout << "not" << endl;
       break;
       case 15:
       if(!ignore)
         nand_l(pkg);
       if(scmnd && (!ignore))
       cout << "nand" << endl;
       break;
       case 16:
       if(!ignore)
         nor_l(pkg);
       if(scmnd && (!ignore))
       cout << "nor" << endl;
       break;
       case 17:
       if(!ignore)
         xnor_l(pkg);
       if(scmnd && (!ignore))
       cout << "xnor" << endl;
       break;

  /*---Data Transfer---*/
        case 18:
       if(!ignore)
         loadi(pkg);
       if(scmnd && (!ignore))
       cout << "loadi" << endl;
       break;
	 case 19:
       if(!ignore)
         loadbl(pkg);
       if(scmnd && (!ignore))
       cout << "loadbl" << endl;
       break;
	 case 20:
       if(!ignore)
         loadr(pkg);
       if(scmnd && (!ignore))
       cout << "loadr" << endl;
       break;
         case 21:
       if(!ignore)
         mv(pkg);
       if(scmnd && (!ignore))
       cout << "mv" << endl;
       break;
	 case 22:
       if(!ignore)
         rm(pkg);
       if(scmnd && (!ignore))
       cout << "rm" << endl;
       break;
	 case 23:
       if(!ignore)
         func(pkg);
       if(scmnd && (!ignore))
       cout << "func" << endl;
       break;
	 case 24:
         push(pkg);
       if(scmnd && (!ignore))
       cout << "push" << endl;
       break;
	 case 25:
         _return(pkg);
       if(scmnd && (!ignore))
       cout << "return" << endl;
       break;
	 case 26:
       if(!ignore)
         call(pkg);
       if(scmnd && (!ignore))
       cout << "call" << endl;
       break;
	 case 27:
       if(!ignore)
         swp(pkg);
       if(scmnd && (!ignore))
       cout << "swp" << endl;
       break;
	 case 28:
       if(!ignore)
         eof(pkg);
       if(scmnd && (!ignore))
       cout << "eof" << endl;
       break;
	 case 29:
       if(!ignore)
         loop(pkg);
       if(scmnd && (!ignore))
       cout << "loop" << endl;
       break;
	 case 30:
         end();
       if(scmnd && (!ignore))
       cout << "end" << endl;
       break;
	 case 31:
       if(!ignore)
         endl(pkg);
       if(scmnd && (!ignore))
       cout << "endl" << endl;
       break;
	 case 32:
       if(!ignore)
         _do(pkg);
       if(scmnd && (!ignore))
       cout << "do" << endl;
       break;
   /*---Special commands---*/
        case 33: // mov
       if(!ignore)
          mov(pkg);
       if(scmnd && (!ignore))
       cout << "mov" << endl;
         break;
        case 34: // rmov
       if(!ignore)
	  rmov(pkg);
       if(scmnd && (!ignore))
       cout << "rmov" << endl;
        break;
        case 35: // init
       if(!ignore) 
         _init(pkg);
       if(scmnd && (!ignore))
       cout << "init" << endl;
        break;
        case 36:
       if(!ignore)
          ilt(pkg);
       if(scmnd && (!ignore))
       cout << "ilt" << endl;
        break;
        case 37:
       if(!ignore)
        igt(pkg);
       if(scmnd && (!ignore))
       cout << "igt" << endl;
        break;
        case 38:
       if(!ignore)
	 iltoeq(pkg);
       if(scmnd && (!ignore))
       cout << "iltoeq" << endl;
        break;
        case 39:
       if(!ignore)
	igtoeq(pkg);
       if(scmnd && (!ignore))
       cout << "igtoeq" << endl;
        break;
        case 40:
       if(!ignore)
        ndo(pkg);
       if(scmnd && (!ignore))
       cout << "ndo" << endl;
        break;
        case 41:
       if(!ignore)
        inlt(pkg);
       if(scmnd && (!ignore))
	cout << "inlt" << endl;
	break;
        case 42:
       if(!ignore)
	ingt(pkg);
       if(scmnd && (!ignore))
        cout << "ingt" << endl;
	break;
 	case 43:
       if(!ignore)
	inltoeq(pkg);
       if(scmnd && (!ignore))
 	cout << "inltoeq" << endl;
	break;
	case 44:
       if(!ignore)
 	ingtoeq(pkg);
       if(scmnd && (!ignore))
	cout << "ingtoeq" << endl;
	break;
        case 45:
       if(!ignore)
        neg(pkg);
       if(scmnd && (!ignore))
        cout << "neg" << endl;
        break;
        case 46:
       if(!ignore)
         cadd(pkg);
       if(scmnd && (!ignore))
       cout << "cadd" << endl;
        break;
       case 47:
       if(!ignore)
         csub(pkg);
       if(scmnd && (!ignore))
       cout << "csub" << endl;
        break;
       case 48:
       if(!ignore)
         cmult(pkg);
       if(scmnd && (!ignore))
       cout << "cmult" << endl;
        break;
       case 49:
       if(!ignore)
         cdiv(pkg);
       if(scmnd && (!ignore))
       cout << "cdiv" << endl;
        break;
       case 50:
       if(!ignore)
         crem(pkg);
       if(scmnd && (!ignore))
       cout << "crem" << endl;
        break;
       case 51:
       if(!ignore)
          mlock(pkg);
       if(scmnd && (!ignore))
       cout << "mlock" << endl;
        break;
       case 52:
       if(!ignore)
	  lock(pkg);
       if(scmnd && (!ignore))
       cout << "lock" << endl;
        break;
       case 53:
       if(!ignore)
	  mulock(pkg);
       if(scmnd && (!ignore))
       cout << "mulock" << endl;
        break;
      case 54:
       if(!ignore)
	  ulock(pkg);
       if(scmnd && (!ignore))
       cout << "ulock" << endl;
	break;
      case 55:
       if(!ignore)
	  xreg(pkg);
       if(scmnd && (!ignore))
       cout << "xreg" << endl;
        break;
      case 56:
       if(!ignore)
          clx(pkg);
       if(scmnd && (!ignore))
       cout << "clx" << endl;
        break;
       case 57:
       if(!ignore)
	  rloop(pkg);
       if(scmnd && (!ignore))
       cout << "rloop" << endl;
        break;
       case 58:
       if(!ignore)
          wloop(pkg);
       if(scmnd && (!ignore))
	cout << "wloop" << endl;
        break;
       case 59:
       if(!ignore)
          endwl(pkg);
       if(scmnd && (!ignore))
	cout << "endwl" << endl;
	break;
       case 60:
       if(!ignore)
           _port(pkg);
       if(scmnd && (!ignore))
	cout << "port" << endl;
        break;
       case 61:
       if(!ignore)
           same(pkg);
       if(scmnd && (!ignore))
        cout << "same" << endl;
        break;
       case 62: // nac
       if(scmnd && (!ignore))
        cout << "nac" << endl;
       break;
       default:
         Log lg;
         cout << "Segmentation Fault" << endl;
         stringstream ss;
         ss << "unknown command at {IP:" << _cpu.GetVirturalAddress() << "}. Shutting Down System...";
         RuntimeException re;
         re.introduce("CPULogicException", ss.str());
        break;
   }
   return 0;
}

