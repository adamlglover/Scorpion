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
using namespace std;

double pkg[3];
C0 _cpu;
extern long skip;
extern short DEBUG_STATE;
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
         debugger(IP,"halt", pkg);

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
         debugger(IP,"rhalt", pkg);

       if(!ignore)
          _cpu.Reset();
       break;
       case 3: // chalt
       if(debugging && !ignore)
         debugger(IP,"chalt", pkg);

       if(!ignore)
	  _cpu.Halt();
        break;

   /*---ALU---*/
       case 4:
       if(debugging && !ignore)
         debugger(IP,"add", pkg);

       if(!ignore)
         add(pkg);
        break;
       case 5:
       if(debugging && !ignore)
         debugger(IP,"sub", pkg);

       if(!ignore)
         sub(pkg);
        break;
       case 6:
       if(debugging && !ignore)
         debugger(IP,"mult", pkg);

       if(!ignore)
	 mult(pkg);
        break;
       case 7:
       if(debugging && !ignore)
         debugger(IP,"div", pkg);

       if(!ignore)
	 div(pkg);
        break;
       case 8:
       if(debugging && !ignore)
         debugger(IP,"rem", pkg);

       if(!ignore)
	 rem(pkg);
 	break;
       case 9:
       if(debugging && !ignore)
         debugger(IP,"inc", pkg);

       if(!ignore)
         inc(pkg);
       break;
       case 10:
       if(debugging && !ignore)
         debugger(IP,"dec", pkg);

       if(!ignore)
	 dec(pkg);
       break;

   /*---Logic Unit---*/
       case 11:
       if(debugging && !ignore)
         debugger(IP,"and", pkg);
       
       if(!ignore)
         and_l(pkg);
       break;
       case 12:
       if(debugging && !ignore)
         debugger(IP,"or", pkg);
       
       if(!ignore)
         or_l(pkg);
       break;
       case 13:
       if(debugging && !ignore)
         debugger(IP,"xor", pkg);
       
       if(!ignore)
         xor_l(pkg);
       break;
       case 14:
       if(debugging && !ignore)
         debugger(IP,"not", pkg);
       
       if(!ignore)
         not_l(pkg);
       break;
       case 15:
       if(debugging && !ignore)
         debugger(IP,"nand", pkg);
       
       if(!ignore)
         nand_l(pkg);
       break;
       case 16:
       if(debugging && !ignore)
         debugger(IP,"nor", pkg);
       
       if(!ignore)
         nor_l(pkg);
       break;
       case 17:
       if(debugging && !ignore)
         debugger(IP,"xnor", pkg);
       
       if(!ignore)
         xnor_l(pkg);
       break;

  /*---Data Transfer---*/
        case 18:
       if(debugging && !ignore)
         debugger(IP,"loadi", pkg);
       
       if(!ignore)
         loadi(pkg);
       return 0;
       break;
	 case 19:
       if(debugging && !ignore)
         debugger(IP,"loadbl", pkg);
       
       if(!ignore)
         loadbl(pkg);
       break;
       case 24:
       if(debugging && !ignore)
         debugger(IP,"push", pkg);
       push(pkg);
       break;
       case 25:
       if(debugging && !ignore)
         debugger(IP,"return", pkg);
         _return(pkg);
       break;
       case 26:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"call", pkg);
       if(!ignore)
         call(pkg);
       break;
       case 27:
       if(debugging && !ignore)
         debugger(IP,"swp", pkg);
       
       if(!ignore)
         swp(pkg);
       break;
       case 29:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"loop", pkg);
       
       if(!ignore)
         loop(pkg);
       break;
       case 30:
       if(debugging && !ignore)
         debugger(IP,"end", pkg);
       
         end();
       break;
	 case 31:
       if(debugging && !ignore)
         debugger(IP,"endl", pkg);
       
       if(!ignore)
         endl(pkg);
       break;
	 case 32:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"do", pkg);
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
         _do(pkg);
       break;
   /*---Special commands---*/
        case 33: // mov
       if(debugging && !ignore)
         debugger(IP,"mov", pkg);
       
       if(!ignore)
          mov(pkg);
         break;
        case 34: // rmov
       if(debugging && !ignore)
         debugger(IP,"rmov", pkg);
       
       if(!ignore)
	  rmov(pkg);
        break;
        case 35: // init
       if(debugging && !ignore)
         debugger(IP,"invoke", pkg);
       
       if(!ignore) 
         invoke(pkg);
        break;
        case 36:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"ilt", pkg);
       
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
         debugger(IP,"igt", pkg);
       
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
         debugger(IP,"ile", pkg);
       
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
         debugger(IP,"ige", pkg);
       
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
         debugger(IP,"ndo", pkg);
       
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
         debugger(IP,"inlt", pkg);
       
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
         debugger(IP,"ingt", pkg);
       
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
         debugger(IP,"inle", pkg);
       
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
         debugger(IP,"inge", pkg);
       
       if(if_ignore)
        passed_if++;
       if(!ignore)
 	inge(pkg);
	break;
        case 45:
       if(debugging && !ignore)
         debugger(IP,"neg", pkg);
       
       if(!ignore)
        neg(pkg);
        break;
       case 52:
       if(debugging && !ignore)
         debugger(IP,"lock", pkg);
       
       if(!ignore)
	  lock(pkg);
        break;
      case 54:
       if(debugging && !ignore)
         debugger(IP,"ulock", pkg);
       
       if(!ignore)
	  ulock(pkg);
	break;
      case 55:
       if(debugging && !ignore)
         debugger(IP,"xreg", pkg);
       
       if(!ignore)
	  xreg(pkg);
        break;
      case 56:
       if(debugging && !ignore)
         debugger(IP,"clx", pkg);
       
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
         debugger(IP,"rloop", pkg);
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
         debugger(IP,"wloop", pkg);
       }
       if(!ignore)
          wloop(pkg);
       break;
       case 59:
       if(debugging && !ignore){
         in_loop = false;
         debugger(IP,"endwl", pkg);
       }
       if(!ignore)
          endwl(pkg);
	break;
       case 61:
       if(debugging && !ignore)
         debugger(IP,"same", pkg);
       
       if(!ignore)
          same(pkg);
        break;
       case 62: // nac
       if(debugging && !ignore)
         debugger(IP,"nac", pkg);
       
       break;
       case 63:
       if(debugging && !ignore)
         debugger(IP,"sr", pkg);
       
       if(!ignore)
          sr(pkg);
        break;
       case 64:
       if(debugging && !ignore)
         debugger(IP,"sl", pkg);
       
       if(!ignore)
          sl(pkg);
        break;
        case 65:
       if(debugging && !ignore)
         debugger(IP,"r_mv", pkg);
       
       if(!ignore)
          r_mv(pkg);
        break;
        case 66:
       if(debugging && !ignore)
         debugger(IP,"cpuid", pkg);
       
       if(!ignore)
          cpuid();
        break;
        case 67:
       if(debugging && !ignore)
         debugger(IP,"rdtsc", pkg);
       
       if(!ignore)
           rdtsc();
        break;
       case 69:
       if(debugging && !ignore)
         debugger(IP,"print", pkg);
       
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
         debugger(IP,"rand_1", pkg);
       
       if(!ignore)
          rand_1(pkg);
        break;
        case 71:
       if(debugging && !ignore)
         debugger(IP,"rand_2", pkg);
       
       if(!ignore)
          rand_2(pkg);
        break;
        case 72:
       if(debugging && !ignore)
         debugger(IP,"rand_3", pkg);
       
       if(!ignore)
          rand_3(pkg);
        break;
        case 77:
       if(debugging && !ignore)
         debugger(IP,"printf", pkg);
       
          _printf(pkg);
        break;
        case 78:
       if(debugging && !ignore)
         debugger(IP,"rhalt", pkg);
       
       if(!ignore)
          loadc(pkg);
         break;
         case 79:
       if(debugging && !ignore)
         debugger(IP,"dload", pkg);
       
       if(!ignore)
          dload(pkg);
       break;
         case 80:
       if(debugging && !ignore)
         debugger(IP,"t_cast", pkg);
       
       if(!ignore)
         t_cast(pkg);
       break;
        case 81:
       if(debugging && !ignore)
         debugger(IP,"sload", pkg);
       
       if(!ignore)
         sload(pkg);
       break;
        case 82:
       if(debugging && !ignore)
         debugger(IP,"loadf", pkg);
       
       if(!ignore)
         loadf(pkg);
       break;
       case 84:
       if(debugging && !ignore)
         debugger(IP,"rln", pkg);
       
       if(!ignore)
         rln(pkg);
       break;
       case 85:
       if(debugging && !ignore)
         debugger(IP,"rload", pkg);
       
       if(!ignore)
         rload(pkg);
       break;
       case 90:
       if(debugging && !ignore)
         debugger(IP,"ct_int", pkg);
       
       if(!ignore)
         ct_int(pkg);
       break;
       case 92:
       if(debugging && !ignore)
         debugger(IP,"anum", pkg);
       
       if(!ignore)
         anum(pkg);
       break;
       case 93:
       if(debugging && !ignore)
         debugger(IP,"sleep", pkg);
       
       if(!ignore)
         _sleep(pkg);
       break;
       case 94:
       if(debugging && !ignore)
         debugger(IP,"cp", pkg);
       
       if(!ignore)
         cp(pkg);
       break;
       case 96:
       if(debugging && !ignore)
         debugger(IP,"string", pkg);
       
         _string(pkg);
       break;
       case 97:
       if(debugging && !ignore)
         debugger(IP,"adr", pkg);
       
       if(!ignore)
         adr(pkg);
       break;
       case 98:
       if(debugging && !ignore)
         debugger(IP,"r_load", pkg);
       
       if(!ignore)
         r_load(pkg);
       break;
       case 99:
       if(debugging && !ignore)
         debugger(IP,"strcp", pkg);
       
       if(!ignore)
         strcp(pkg);
       break;
       case 100:
       if(debugging && !ignore)
         debugger(IP,"e2str", pkg);
       
       if(!ignore)
         e2str(pkg);
       break; // strcpi
       case 101:
       if(debugging && !ignore)
         debugger(IP,"strcpi", pkg);
       
       if(!ignore)
         strcpi(pkg);
       break;
       case 102:
       if(debugging && !ignore)
         debugger(IP,"swi", pkg);
       
       if(!ignore)
         swi(pkg);
       break;
       case 103:
       if(debugging && !ignore)
         debugger(IP,"array", pkg);
       
       if(!ignore)
         array(pkg);
       break;
       case 104:
       if(debugging && !ignore)
         debugger(IP,"aload", pkg);
       
       if(!ignore)
         aload(pkg);
       break;
       case 105:
       if(debugging && !ignore)
         debugger(IP,"aaload", pkg);
       
       if(!ignore)
         aaload(pkg);
       break;
       case 106:
        if(DEBUG_STATE == 0x44)
        {
           debugging = true;
        }
       if(debugging && !ignore)
         debugger(IP,"throw", pkg);
       
       if(!ignore)
         _throw(pkg);
       break;
       default:
         if(!ignore){
             cout << "Segmentation Fault" << endl;
             stringstream ss;
             ss << "unknown command at {IP:" << _cpu.GetVirturalAddress() << "}. Shutting Down System...";
             RuntimeException re;
             re.introduce("CPULogicException", ss.str());
         }
        break;
   }
   return 0;
}

