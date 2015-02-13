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

InputOutput IO;
Ports _port;
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
       System::Running = false;
       break;
      case 1: // scmnd
         scmnd = true;
       break;
      case 2: // rhalt
          _cpu.Reset();
        break;
       case 3: // chalt
	  _cpu.Halt();
        break;

   /*---ALU---*/
       case 4:
         add(pkg); 
        break;
       case 5:
         sub(pkg);
        break;
       case 6:
	 mult(pkg);
        break;
       case 7:
	 div(pkg);
        break;
       case 8:
	 rem(pkg);
 	break;
       case 9:
         inc(pkg);
       break;
       case 10:
	 dec(pkg);
       break;

   /*---Logic Unit---*/
       case 11:
         and_l(pkg);
       break;
       case 12:
         or_l(pkg);
       break;
       case 13:
         xor_l(pkg);
       break;
       case 14:
         not_l(pkg);
       break;
       case 15:
         nand_l(pkg);
       break;
       case 16:
         nor_l(pkg);
       break;
       case 17:
         xnor_l(pkg);
       break;

  /*---Data Transfer---*/
        case 18:
         loadi(pkg);
       break;
	 case 19:
         loadbl(pkg);
       break;
	 case 20:
         loadr(pkg);
       break;
         case 21:
         mv(pkg);
       break;
	 case 22:
         rm(pkg);
       break;
	 case 23:
         func(pkg);
       break;
	 case 24:
         push(pkg);
       break;
	 case 25:
         _return(pkg);
       break;
	 case 26:
         call(pkg);
       break;
	 case 27:
         swp(pkg);
       break;
	 case 28:
         eof(pkg);
       break;
	 case 29:
         loop(pkg);
       break;
	 case 30:
         end();
       break;
	 case 31:
         endl(pkg);
       break;
	 case 32:
         _do(pkg);
       break;
   /*---IO---*/
        case 33: // dout
         IO.Write(STD_OUT,0,0,pkg);
       break;
	case 34: // size
         IO.Write(STD_OUT,1,0,pkg);
       break;
	case 35: // bout
         IO.Write(STD_OUT,2,0,pkg);
       break;
        case 36: // write to disk
	 IO.Write(VDISK,0,0,pkg);
       break;
        case 37:  // port
         _port.port(pkg[0]);
       break;
       default:
         Log lg;
         cout << "Segmentation Fault" << endl;
         stringstream ss;
         ss << "cpu logic err: unknown command at {IP:" << _cpu.GetVirturalAddress() << "}. Shutting Down System...";
         lg.v("System", ss.str());
         System::Running = false;
        break;
   }
   return 0;
}
