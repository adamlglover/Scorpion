#include "core0.h"
#include "alu.h"
#include "gate.h"
#include "lu.h"
#include "datatrans.h"
#include "io.h"
#include "runtime_exception.h"
#include "../../program.h"
#include <sstream>
#include <iostream>
#include "../../Log/Log.h"
#include "../../System.h"
#include "debug_interface.h"
using namespace std;

double pkg[3];
C0 _cpu;
void Gate::route(double instr)
{
   switch( (long) instr )
   {
  /*---System Control---*/
      case 0: // halt
       if(debugging && !ignore)
         debugger(IP,"halt");

       if(!ignore)
       p_exit();
       else
        IP += 3;
       break;
      case 1: // breakp
      {
        if(DEBUG_STATE == 0x43 || DEBUG_STATE == 0x54 || DEBUG_STATE == 0x55)
        {
           debugging = true;
        }
        IP++;
        IP++;
        IP++;
      }
      break;
      case 2: // rhalt
       if(debugging && !ignore)
         debugger(IP,"rhalt");

        IP++;
        IP++;
        IP++;

       if(!ignore)
          _cpu.Reset();
       else
        IP += 3;
       break;
       case 3: // chalt
       if(debugging && !ignore)
         debugger(IP,"chalt");

       IP++;
       IP++;
       IP++;

       if(!ignore)
	  _cpu.Halt();
       else
        IP += 3;
        break;

   /*---ALU---*/
       case 4:
       if(debugging && !ignore)
         debugger(IP,"add");

       if(!ignore)
         add();
       else
        IP += 3;
       
        break;
       case 5:
       if(debugging && !ignore)
         debugger(IP,"sub");

       if(!ignore)
         sub();
       else
        IP += 3;
       
        break;
       case 6:
       if(debugging && !ignore)
         debugger(IP,"mult");

       if(!ignore)
	 mult();
       else
        IP += 3;
        break;
       case 7:
       if(debugging && !ignore)
         debugger(IP,"div");

       if(!ignore)
	 div();
       else
        IP += 3;
        break;
       case 8:
       if(debugging && !ignore)
         debugger(IP,"rem");

       if(!ignore)
	 rem();
       else
        IP += 3;
 	break;
       case 9:
       if(debugging && !ignore)
         debugger(IP,"inc");

       if(!ignore)
         inc();
       else
        IP += 3;
       break;
       case 10:
       if(debugging && !ignore)
         debugger(IP,"dec");

       if(!ignore)
	 dec();
       else
        IP += 3;
       break;

   /*---Logic Unit---*/
       case 11:
       if(debugging && !ignore)
         debugger(IP,"and");
       
       if(!ignore)
         and_l();
       else
        IP += 3;
       break;
       case 12:
       if(debugging && !ignore)
         debugger(IP,"or");
       
       if(!ignore)
         or_l();
       else
        IP += 3;
       break;
       case 13:
       if(debugging && !ignore)
         debugger(IP,"xor");
       
       if(!ignore)
         xor_l();
       else
        IP += 3;
       break;
       case 14:
       if(debugging && !ignore)
         debugger(IP,"not");
       
       if(!ignore)
         not_l();
       else
        IP += 3;
       break;
       case 15:
       if(debugging && !ignore)
         debugger(IP,"nand");
       
       if(!ignore)
         nand_l();
       else
        IP += 3;
       break;
       case 16:
       if(debugging && !ignore)
         debugger(IP,"nor");
       
       if(!ignore)
         nor_l();
       else
        IP += 3;
       break;
       case 17:
       if(debugging && !ignore)
         debugger(IP,"xnor");
       
       if(!ignore)
         xnor_l();
       else
        IP += 3;
       break;

  /*---Data Transfer---*/
        case 18:
       if(debugging && !ignore)
         debugger(IP,"loadi");
       
       if(!ignore)
         loadi();
       else
        IP += 3;
       return;
       break;
	 case 19:
       if(debugging && !ignore)
         debugger(IP,"loadbl");
       
       if(!ignore)
         loadbl();
       else
        IP += 3;
       break;
       case 24:
       if(debugging && !ignore)
         debugger(IP,"push");
       push();
       break;
       case 25:
       if(debugging && !ignore)
         debugger(IP,"return");
         _return();
       break;
       case 26:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"call");
       if(!ignore)
         call();
       else
        IP += 3;
       break;
       case 27:
       if(debugging && !ignore)
         debugger(IP,"swp");
       
       if(!ignore)
         swp();
       else
        IP += 3;
       break;
       case 29:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"loop");
       
       if(!ignore)
         loop();
       else
        IP += 3;
       break;
       case 30:
       if(debugging && !ignore)
         debugger(IP,"end");
       
         end();
       break;
	 case 31:
       if(debugging && !ignore)
         debugger(IP,"endl");
       
       if(!ignore)
         endl();
       else
        IP += 3;
       break;
	 case 32:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"do");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
         _do();
       else
        IP += 3;
       break;
   /*---Special commands---*/
        case 33: // mov
       if(debugging && !ignore)
         debugger(IP,"mov");
       
       if(!ignore)
          mov();
       else
        IP += 3;
         break;
        case 34: // rmov
       if(debugging && !ignore)
         debugger(IP,"rmov");
       
       if(!ignore)
	  rmov();
       else
        IP += 3;
        break;
        case 35: // init
       if(debugging && !ignore)
         debugger(IP,"invoke");
       
       if(!ignore) 
         invoke();
       else
        IP += 3;
        break;
        case 36:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"ilt");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
          ilt();
       else
        IP += 3;
        break;
        case 37:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"igt");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
        igt();
       else
        IP += 3;
        break;
        case 38:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"ile");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
	 ile();
       else
        IP += 3;
        break;
        case 39:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"ige");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
	ige();
       else
        IP += 3;
        break;
        case 40:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"ndo");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
        ndo();
       else
        IP += 3;
        break;
        case 41:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"inlt");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
        inlt();
       else
        IP += 3;
	break;
        case 42:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"ingt");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
	ingt();
       else
        IP += 3;
	break;
 	case 43:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"inle");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
	inle();
       else
        IP += 3;
	break;
	case 44:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"inge");
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
 	inge();
       else
        IP += 3;
	break;
        case 45:
       if(debugging && !ignore)
         debugger(IP,"neg");
       
       if(!ignore)
        neg();
       else
        IP += 3;
        break;
       case 52:
       if(debugging && !ignore)
         debugger(IP,"lock");
       
       if(!ignore)
	  lock();
       else
        IP += 3;
        break;
      case 54:
       if(debugging && !ignore)
         debugger(IP,"ulock");
       
       if(!ignore)
	  ulock();
       else
        IP += 3;
	break;
      case 55:
       if(debugging && !ignore)
         debugger(IP,"xreg");
       
       if(!ignore)
	  xreg();
       else
        IP += 3;
        break;
      case 56:
       if(debugging && !ignore)
         debugger(IP,"clx");
       
       if(!ignore)
          clx();
       else
        IP += 3;
        break;
       case 57:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore){
         in_loop = true;
         debugger(IP,"rloop");
       }
       if(!ignore)
	  rloop();
       else
        IP += 3;
        break;
       case 58:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore){
         in_loop = true;
         debugger(IP,"wloop");
       }
       if(!ignore)
          wloop();
       else
        IP += 3;
       break;
       case 59:
       if(debugging && !ignore){
         in_loop = false;
         debugger(IP,"endwl");
       }
       if(!ignore)
          endwl();
       else if(pass)
          endwl();
       else
        IP += 3;
	break;
       case 61:
       if(debugging && !ignore)
         debugger(IP,"same");
       
       if(!ignore)
          same();
       else
        IP += 3;
        break;
       case 62: // nac
       if(debugging && !ignore)
         debugger(IP,"nac");
       
       break;
       case 63:
       if(debugging && !ignore)
         debugger(IP,"sr");
       
       if(!ignore)
          sr();
       else
        IP += 3;
        break;
       case 64:
       if(debugging && !ignore)
         debugger(IP,"sl");
       
       if(!ignore)
          sl();
       else
        IP += 3;
        break;
        case 65:
       if(debugging && !ignore)
         debugger(IP,"r_mv");
       
       if(!ignore)
          r_mv();
       else
        IP += 3;
        break;
        case 66:
       if(debugging && !ignore)
         debugger(IP,"cpuid");
       
       if(!ignore)
          cpuid();
       else
        IP += 3;
        break;
        case 67:
       if(debugging && !ignore)
         debugger(IP,"rdtsc");
       
       if(!ignore)
           rdtsc();
        break;
       case 69:
       if(debugging && !ignore)
         debugger(IP,"print");
       
          _print();
        break;
        case 70:
       if(debugging && !ignore)
         debugger(IP,"rand_1");
       
       if(!ignore)
          rand_1();
       else
        IP += 3;
        break;
        case 71:
       if(debugging && !ignore)
         debugger(IP,"rand_2");
       
       if(!ignore)
          rand_2();
       else
        IP += 3;
        break;
        case 72:
       if(debugging && !ignore)
         debugger(IP,"rand_3");
       
       if(!ignore)
          rand_3();
       else
        IP += 3;
        break;
        case 77:
       if(debugging && !ignore)
         debugger(IP,"printf");
       
          _printf();
        break;
        case 78:
       if(debugging && !ignore)
         debugger(IP,"loadc");
       
       if(!ignore)
          loadc();
       else
        IP += 3;
         break;
         case 79:
       if(debugging && !ignore)
         debugger(IP,"dload");
       
       if(!ignore)
          dload();
       else
        IP += 3;
       break;
         case 80:
       if(debugging && !ignore)
         debugger(IP,"t_cast");
       
       if(!ignore)
         t_cast();
       else
        IP += 3;
       break;
        case 81:
       if(debugging && !ignore)
         debugger(IP,"sload");
       
       if(!ignore)
         sload();
       else
        IP += 3;
       break;
        case 82:
       if(debugging && !ignore)
         debugger(IP,"loadf");
       
       if(!ignore)
         loadf();
       else
        IP += 3;
       break;
       case 84:
       if(debugging && !ignore)
         debugger(IP,"rln");
       
       if(!ignore)
         rln();
       else
        IP += 3;
       break;
       case 85:
       if(debugging && !ignore)
         debugger(IP,"rload");
       
       if(!ignore)
         rload();
       else
        IP += 3;
       break;
       case 90:
       if(debugging && !ignore)
         debugger(IP,"ct_int");
       
       if(!ignore)
         ct_int();
       else
        IP += 3;
       break;
       case 92:
       if(debugging && !ignore)
         debugger(IP,"anum");
       
       if(!ignore)
         anum();
       else
        IP += 3;
       break;
       case 93:
       if(debugging && !ignore)
         debugger(IP,"sleep");
       
       if(!ignore)
         _sleep();
       else
        IP += 3;
       break;
       case 94:
       if(debugging && !ignore)
         debugger(IP,"cp");
       
       if(!ignore)
         cp();
       else
        IP += 3;
       break;
       case 96:
       if(debugging && !ignore)
         debugger(IP,"string");
       
         _string();
       break;
       case 97:
       if(debugging && !ignore)
         debugger(IP,"adr");
       
       if(!ignore)
         adr();
       else
        IP += 3;
       break;
       case 98:
       if(debugging && !ignore)
         debugger(IP,"r_load");
       
       if(!ignore)
         r_load();
       else
        IP += 3;
       break;
       case 99:
       if(debugging && !ignore)
         debugger(IP,"strcp");
       
       if(!ignore)
         strcp();
       else
        IP += 3;
       break;
       case 100:
       if(debugging && !ignore)
         debugger(IP,"e2str");
       
       if(!ignore)
         e2str();
       else
        IP += 3;
       break; // strcpi
       case 101:
       if(debugging && !ignore)
         debugger(IP,"strcpi");
       
       if(!ignore)
         strcpi();
       else
        IP += 3;
       break;
       case 102:
       if(debugging && !ignore)
         debugger(IP,"swi");
       
       if(!ignore)
         swi();
       else
        IP += 3;
       break;
       case 103:
       if(debugging && !ignore)
         debugger(IP,"array");
       
       if(!ignore)
         array();
       else
        IP += 3;
       break;
       case 104:
       if(debugging && !ignore)
         debugger(IP,"aload");
       
       if(!ignore)
         aload();
       else
        IP += 3;
       break;
       case 105:
       if(debugging && !ignore)
         debugger(IP,"aaload");
       
       if(!ignore)
         aaload();
       else
        IP += 3;
       break;
       case 106:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"throw");
       
       if(!ignore)
         _throw();
       else
        IP += 3;
       break;
       default:
         if(!ignore){
             cout << "Segmentation Fault" << endl;
             EBX = 1;
             p_exit();
         }
        break;
   }
   return;
}

