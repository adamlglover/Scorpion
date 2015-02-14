#include "cpu.h"
#include "alu.h"
#include "gate.h"
#include "../Bus/bus.h"
#include "lu.h"
#include "datatrans.h"
#include "io.h"
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
       x86Shutdown();
      cout << "halt" << endl;
       break;
      case 1: // scmnd
         scmnd = true;
       cout << "scmnd" << endl;
       break;
      case 2: // rhalt
          _cpu.Reset();
       cout << "rhalt" << endl;
        break;
       case 3: // chalt
	  _cpu.Halt();
       cout << "chalt" << endl;
        break;

   /*---ALU---*/
       case 4:
         add(pkg); 
       cout << "add" << endl;
        break;
       case 5:
         sub(pkg);
       cout << "sub" << endl;
        break;
       case 6:
	 mult(pkg);
       cout << "mult" << endl;
        break;
       case 7:
	 div(pkg);
       cout << "div" << endl;
        break;
       case 8:
	 rem(pkg);
       cout << "rem" << endl;
 	break;
       case 9:
         inc(pkg);
       cout << "inc" << endl;
       break;
       case 10:
	 dec(pkg);
       cout << "dec" << endl;
       break;

   /*---Logic Unit---*/
       case 11:
         and_l(pkg);
       cout << "and" << endl;
       break;
       case 12:
         or_l(pkg);
       cout << "or" << endl;
       break;
       case 13:
         xor_l(pkg);
       cout << "xor" << endl;
       break;
       case 14:
         not_l(pkg);
       cout << "not" << endl;
       break;
       case 15:
         nand_l(pkg);
       cout << "nand" << endl;
       break;
       case 16:
         nor_l(pkg);
       cout << "nor" << endl;
       break;
       case 17:
         xnor_l(pkg);
       cout << "xnor" << endl;
       break;

  /*---Data Transfer---*/
        case 18:
         loadi(pkg);
       cout << "loadi" << endl;
       break;
	 case 19:
         loadbl(pkg);
       cout << "loadbl" << endl;
       break;
	 case 20:
         loadr(pkg);
       cout << "loadr" << endl;
       break;
         case 21:
         mv(pkg);
       cout << "mv" << endl;
       break;
	 case 22:
         rm(pkg);
       cout << "rm" << endl;
       break;
	 case 23:
         func(pkg);
       cout << "func" << endl;
       break;
	 case 24:
         push(pkg);
       cout << "push" << endl;
       break;
	 case 25:
         _return(pkg);
       cout << "return" << endl;
       break;
	 case 26:
         call(pkg);
       cout << "call" << endl;
       break;
	 case 27:
         swp(pkg);
       cout << "swp" << endl;
       break;
	 case 28:
         eof(pkg);
       cout << "eof" << endl;
       break;
	 case 29:
         loop(pkg);
       cout << "loop" << endl;
       break;
	 case 30:
         end();
       cout << "end" << endl;
       break;
	 case 31:
         endl(pkg);
       cout << "endl" << endl;
       break;
	 case 32:
         _do(pkg);
       cout << "do" << endl;
       break;
   /*---Special commands---*/
        case 33: // mov
          mov(pkg);
       cout << "mov" << endl;
         break;
        case 34: // rmov
	  rmov(pkg);
       cout << "rmov" << endl;
        break;
        case 35: // int 
         _init(pkg);
       cout << "init" << endl;
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
