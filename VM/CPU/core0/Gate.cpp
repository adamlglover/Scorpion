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
int Gate::route(double instr, double r1,double r2, double r3)
{
   pkg[0] = r1;
   pkg[1] = r2;
   pkg[2] = r3;

   switch( (long) instr )
   {
  /*---System Control---*/
      case 0: // halt
       if(debugging && !ignore)
         debugger(IP,"halt");

       if(!ignore)
       p_exit();
       break;
      case 1: // breakp
      {
        if(DEBUG_STATE == 0x43 || DEBUG_STATE == 0x54 || DEBUG_STATE == 0x55)
        {
           debugging = true;
        }
      }
      break;
      case 2: // rhalt
       if(debugging && !ignore)
         debugger(IP,"rhalt");

       if(!ignore)
          _cpu.Reset();
       break;
       case 3: // chalt
       if(debugging && !ignore)
         debugger(IP,"chalt");

       if(!ignore)
	  _cpu.Halt();
        break;

   /*---ALU---*/
       case 4:
       if(debugging && !ignore)
         debugger(IP,"add");

       if(!ignore)
         add(pkg);
        break;
       case 5:
       if(debugging && !ignore)
         debugger(IP,"sub");

       if(!ignore)
         sub(pkg);
        break;
       case 6:
       if(debugging && !ignore)
         debugger(IP,"mult");

       if(!ignore)
	 mult(pkg);
        break;
       case 7:
       if(debugging && !ignore)
         debugger(IP,"div");

       if(!ignore)
	 div(pkg);
        break;
       case 8:
       if(debugging && !ignore)
         debugger(IP,"rem");

       if(!ignore)
	 rem(pkg);
 	break;
       case 9:
       if(debugging && !ignore)
         debugger(IP,"inc");

       if(!ignore)
         inc(pkg);
       break;
       case 10:
       if(debugging && !ignore)
         debugger(IP,"dec");

       if(!ignore)
	 dec(pkg);
       break;

   /*---Logic Unit---*/
       case 11:
       if(debugging && !ignore)
         debugger(IP,"and");
       
       if(!ignore)
         and_l(pkg);
       break;
       case 12:
       if(debugging && !ignore)
         debugger(IP,"or");
       
       if(!ignore)
         or_l(pkg);
       break;
       case 13:
       if(debugging && !ignore)
         debugger(IP,"xor");
       
       if(!ignore)
         xor_l(pkg);
       break;
       case 14:
       if(debugging && !ignore)
         debugger(IP,"not");
       
       if(!ignore)
         not_l(pkg);
       break;
       case 15:
       if(debugging && !ignore)
         debugger(IP,"nand");
       
       if(!ignore)
         nand_l(pkg);
       break;
       case 16:
       if(debugging && !ignore)
         debugger(IP,"nor");
       
       if(!ignore)
         nor_l(pkg);
       break;
       case 17:
       if(debugging && !ignore)
         debugger(IP,"xnor");
       
       if(!ignore)
         xnor_l(pkg);
       break;

  /*---Data Transfer---*/
        case 18:
       if(debugging && !ignore)
         debugger(IP,"loadi");
       
       if(!ignore)
         loadi(pkg);
       return 0;
       break;
	 case 19:
       if(debugging && !ignore)
         debugger(IP,"loadbl");
       
       if(!ignore)
         loadbl(pkg);
       break;
       case 24:
       if(debugging && !ignore)
         debugger(IP,"push");
       push(pkg);
       break;
       case 25:
       if(debugging && !ignore)
         debugger(IP,"return");
         _return(pkg);
       break;
       case 26:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"call");
       if(!ignore)
         call(pkg);
       break;
       case 27:
       if(debugging && !ignore)
         debugger(IP,"swp");
       
       if(!ignore)
         swp(pkg);
       break;
       case 29:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"loop");
       
       if(!ignore)
         loop(pkg);
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
         endl(pkg);
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
         _do(pkg);
       break;
   /*---Special commands---*/
        case 33: // mov
       if(debugging && !ignore)
         debugger(IP,"mov");
       
       if(!ignore)
          mov(pkg);
         break;
        case 34: // rmov
       if(debugging && !ignore)
         debugger(IP,"rmov");
       
       if(!ignore)
	  rmov(pkg);
        break;
        case 35: // init
       if(debugging && !ignore)
         debugger(IP,"invoke");
       
       if(!ignore) 
         invoke(pkg);
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
          ilt(pkg);
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
        igt(pkg);
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
	 ile(pkg);
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
	ige(pkg);
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
        ndo(pkg);
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
        inlt(pkg);
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
	ingt(pkg);
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
	inle(pkg);
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
 	inge(pkg);
	break;
        case 45:
       if(debugging && !ignore)
         debugger(IP,"neg");
       
       if(!ignore)
        neg(pkg);
        break;
       case 52:
       if(debugging && !ignore)
         debugger(IP,"lock");
       
       if(!ignore)
	  lock(pkg);
        break;
      case 54:
       if(debugging && !ignore)
         debugger(IP,"ulock");
       
       if(!ignore)
	  ulock(pkg);
	break;
      case 55:
       if(debugging && !ignore)
         debugger(IP,"xreg");
       
       if(!ignore)
	  xreg(pkg);
        break;
      case 56:
       if(debugging && !ignore)
         debugger(IP,"clx");
       
       if(!ignore)
          clx(pkg);
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
	  rloop(pkg);
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
          wloop(pkg);
       break;
       case 59:
       if(debugging && !ignore){
         in_loop = false;
         debugger(IP,"endwl");
       }
       if(!ignore)
          endwl(pkg);
	break;
       case 61:
       if(debugging && !ignore)
         debugger(IP,"same");
       
       if(!ignore)
          same(pkg);
        break;
       case 62: // nac
       if(debugging && !ignore)
         debugger(IP,"nac");
       
       break;
       case 63:
       if(debugging && !ignore)
         debugger(IP,"sr");
       
       if(!ignore)
          sr(pkg);
        break;
       case 64:
       if(debugging && !ignore)
         debugger(IP,"sl");
       
       if(!ignore)
          sl(pkg);
        break;
        case 65:
       if(debugging && !ignore)
         debugger(IP,"r_mv");
       
       if(!ignore)
          r_mv(pkg);
        break;
        case 66:
       if(debugging && !ignore)
         debugger(IP,"cpuid");
       
       if(!ignore)
          cpuid();
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
       
       if(!ignore)
          _print(pkg);
      else if(ignore){
         if(pkg[0] > 2){
           IP--;
           IP--;
           IP += pkg[0];
         }
         else if(pkg[0] == 1){
           IP--;
         }
         else if (pkg[0] == 0){
           IP--;
           IP--;
         }
      }
        break;
        case 70:
       if(debugging && !ignore)
         debugger(IP,"rand_1");
       
       if(!ignore)
          rand_1(pkg);
        break;
        case 71:
       if(debugging && !ignore)
         debugger(IP,"rand_2");
       
       if(!ignore)
          rand_2(pkg);
        break;
        case 72:
       if(debugging && !ignore)
         debugger(IP,"rand_3");
       
       if(!ignore)
          rand_3(pkg);
        break;
        case 77:
       if(debugging && !ignore)
         debugger(IP,"printf");
       
          _printf(pkg);
        break;
        case 78:
       if(debugging && !ignore)
         debugger(IP,"loadc");
       
       if(!ignore)
          loadc(pkg);
         break;
         case 79:
       if(debugging && !ignore)
         debugger(IP,"dload");
       
       if(!ignore)
          dload(pkg);
       break;
         case 80:
       if(debugging && !ignore)
         debugger(IP,"t_cast");
       
       if(!ignore)
         t_cast(pkg);
       break;
        case 81:
       if(debugging && !ignore)
         debugger(IP,"sload");
       
       if(!ignore)
         sload(pkg);
       break;
        case 82:
       if(debugging && !ignore)
         debugger(IP,"loadf");
       
       if(!ignore)
         loadf(pkg);
       break;
       case 84:
       if(debugging && !ignore)
         debugger(IP,"rln");
       
       if(!ignore)
         rln(pkg);
       break;
       case 85:
       if(debugging && !ignore)
         debugger(IP,"rload");
       
       if(!ignore)
         rload(pkg);
       break;
       case 90:
       if(debugging && !ignore)
         debugger(IP,"ct_int");
       
       if(!ignore)
         ct_int(pkg);
       break;
       case 92:
       if(debugging && !ignore)
         debugger(IP,"anum");
       
       if(!ignore)
         anum(pkg);
       break;
       case 93:
       if(debugging && !ignore)
         debugger(IP,"sleep");
       
       if(!ignore)
         _sleep(pkg);
       break;
       case 94:
       if(debugging && !ignore)
         debugger(IP,"cp");
       
       if(!ignore)
         cp(pkg);
       break;
       case 96:
       if(debugging && !ignore)
         debugger(IP,"string");
       
         _string(pkg);
       break;
       case 97:
       if(debugging && !ignore)
         debugger(IP,"adr");
       
       if(!ignore)
         adr(pkg);
       break;
       case 98:
       if(debugging && !ignore)
         debugger(IP,"r_load");
       
       if(!ignore)
         r_load(pkg);
       break;
       case 99:
       if(debugging && !ignore)
         debugger(IP,"strcp");
       
       if(!ignore)
         strcp(pkg);
       break;
       case 100:
       if(debugging && !ignore)
         debugger(IP,"e2str");
       
       if(!ignore)
         e2str(pkg);
       break; // strcpi
       case 101:
       if(debugging && !ignore)
         debugger(IP,"strcpi");
       
       if(!ignore)
         strcpi(pkg);
       break;
       case 102:
       if(debugging && !ignore)
         debugger(IP,"swi");
       
       if(!ignore)
         swi(pkg);
       break;
       case 103:
       if(debugging && !ignore)
         debugger(IP,"array");
       
       if(!ignore)
         array(pkg);
       break;
       case 104:
       if(debugging && !ignore)
         debugger(IP,"aload");
       
       if(!ignore)
         aload(pkg);
       break;
       case 105:
       if(debugging && !ignore)
         debugger(IP,"aaload");
       
       if(!ignore)
         aaload(pkg);
       break;
       case 106:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"throw");
       
       if(!ignore)
         _throw(pkg);
       break;
       default:
         if(!ignore){
             cout << "Segmentation Fault" << endl;
             EBX = 1;
             p_exit();
         }
        break;
   }
   return 0;
}

