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

int Gate::route(double instr, double r1,double r2, double r3)
{
   double pkg [3];
   pkg[0] = r1;
   pkg[1] = r2;
   pkg[2] = r3;

   C0 _cpu;
   switch( (long) instr )
   {
  /*---System Control---*/
      case 0: // halt
       if(!ignore)
       p_exit();
       if(scmnd && (!ignore))
      cout << ".addr:" << IP << " " << "halt" << endl;
       break;
      case 1: // scmnd
       if(!scmnd)
         scmnd = true;
       else 
         scmnd = false;
      cout << ".addr:" << IP << " " << "scmnd" << endl;
       break;
      case 2: // rhalt
       if(!ignore)
          _cpu.Reset();
       if(scmnd && (!ignore))
       cout <<  ".addr:" << IP << " " << "rhalt" << endl;
        break;
       case 3: // chalt
       if(!ignore)
	  _cpu.Halt();
       if(scmnd && (!ignore))
       cout <<  ".addr:" << IP << " " << "chalt" << endl;
        break;

   /*---ALU---*/
       case 4:
       if(!ignore)
         add(pkg);
       if(scmnd && (!ignore)) 
       cout <<  ".addr:" << IP << " " << "add" << endl;
        break;
       case 5:
       if(!ignore)
         sub(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "sub" << endl;
        break;
       case 6:
       if(!ignore)
	 mult(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "mult" << endl;
        break;
       case 7:
       if(!ignore)
	 div(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "div" << endl;
        break;
       case 8:
       if(!ignore)
	 rem(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "rem" << endl;
 	break;
       case 9:
       if(!ignore)
         inc(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "inc" << endl;
       break;
       case 10:
       if(!ignore)
	 dec(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "dec" << endl;
       break;

   /*---Logic Unit---*/
       case 11:
       if(!ignore)
         and_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "and" << endl;
       break;
       case 12:
       if(!ignore)
         or_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "or" << endl;
       break;
       case 13:
       if(!ignore)
         xor_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "xor" << endl;
       break;
       case 14:
       if(!ignore)
         not_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "not" << endl;
       break;
       case 15:
       if(!ignore)
         nand_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "nand" << endl;
       break;
       case 16:
       if(!ignore)
         nor_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "nor" << endl;
       break;
       case 17:
       if(!ignore)
         xnor_l(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "xnor" << endl;
       break;

  /*---Data Transfer---*/
        case 18:
       if(!ignore)
         loadi(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadi" << endl;
       break;
	 case 19:
       if(!ignore)
         loadbl(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadbl" << endl;
       break;
	 case 20:
       if(!ignore)
         loadr(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadr" << endl;
       break;
         case 21:
       if(!ignore)
         mv(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "mv" << endl;
       break;
	 case 22:
       if(!ignore)
         rm(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "rm" << endl;
       break;
	 case 23:
       if(!ignore)
         func(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "func" << endl;
       break;
	 case 24:
         push(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "push" << endl;
       break;
	 case 25:
         _return(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "return" << endl;
       break;
	 case 26:
       if(!ignore)
         call(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "call" << endl;
       break;
	 case 27:
       if(!ignore)
         swp(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "swp" << endl;
       break;
	 case 28:
       if(!ignore)
         eof(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "eof" << endl;
       break;
	 case 29:
       if(!ignore)
         loop(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loop" << endl;
       break;
	 case 30:
         end();
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "end" << endl;
       break;
	 case 31:
       if(!ignore)
         endl(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "endl" << endl;
       break;
	 case 32:
       if(!ignore)
         _do(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "do" << endl;
       break;
   /*---Special commands---*/
        case 33: // mov
       if(!ignore)
          mov(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "mov" << endl;
         break;
        case 34: // rmov
       if(!ignore)
	  rmov(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "rmov" << endl;
        break;
        case 35: // init
       if(!ignore) 
         invoke(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "invoke" << endl;
        break;
        case 36:
       if(!ignore)
          ilt(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "ilt" << endl;
        break;
        case 37:
       if(!ignore)
        igt(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "igt" << endl;
        break;
        case 38:
       if(!ignore)
	 iltoeq(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "iltoeq" << endl;
        break;
        case 39:
       if(!ignore)
	igtoeq(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "igtoeq" << endl;
        break;
        case 40:
       if(!ignore)
        ndo(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "ndo" << endl;
        break;
        case 41:
       if(!ignore)
        inlt(pkg);
       if(scmnd && (!ignore))
	cout << ".addr:" << IP << " " <<  "inlt" << endl;
	break;
        case 42:
       if(!ignore)
	ingt(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "ingt" << endl;
	break;
 	case 43:
       if(!ignore)
	inltoeq(pkg);
       if(scmnd && (!ignore))
 	cout << ".addr:" << IP << " " <<  "inltoeq" << endl;
	break;
	case 44:
       if(!ignore)
 	ingtoeq(pkg);
       if(scmnd && (!ignore))
	cout << ".addr:" << IP << " " <<  "ingtoeq" << endl;
	break;
        case 45:
       if(!ignore)
        neg(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "neg" << endl;
        break;
        case 46:
       if(!ignore)
         cadd(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "cadd" << endl;
        break;
       case 47:
       if(!ignore)
         csub(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "csub" << endl;
        break;
       case 48:
       if(!ignore)
         cmult(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "cmult" << endl;
        break;
       case 49:
       if(!ignore)
         cdiv(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "cdiv" << endl;
        break;
       case 50:
       if(!ignore)
         crem(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "crem" << endl;
        break;
       case 51:
       if(!ignore)
          mlock(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "mlock" << endl;
        break;
       case 52:
       if(!ignore)
	  lock(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "lock" << endl;
        break;
       case 53:
       if(!ignore)
	  mulock(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "mulock" << endl;
        break;
      case 54:
       if(!ignore)
	  ulock(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "ulock" << endl;
	break;
      case 55:
       if(!ignore)
	  xreg(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "xreg" << endl;
        break;
      case 56:
       if(!ignore)
          clx(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "clx" << endl;
        break;
       case 57:
       if(!ignore)
	  rloop(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "rloop" << endl;
        break;
       case 58:
       if(!ignore)
          wloop(pkg);
       if(scmnd && (!ignore))
	cout << ".addr:" << IP << " " <<  "wloop" << endl;
        break;
       case 59:
       if(!ignore)
          endwl(pkg);
       if(scmnd && (!ignore))
	cout << ".addr:" << IP << " " <<  "endwl" << endl;
	break;
       case 61:
       if(!ignore)
           same(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "same" << endl;
        break;
       case 62: // nac
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "nac" << endl;
       break;
       case 63:
       if(!ignore)
           sr(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "sr" << endl;
        break;
       case 64:
       if(!ignore)
           sl(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "sl" << endl;
        break;
        case 65:
       if(!ignore)
           r_mv(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "r_mv" << endl;
        break;
        case 66:
       if(!ignore)
           cpuid();
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "cpuid" << endl;
        break;
        case 67:
       if(!ignore)
           rdtsc();
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rdtsc" << endl;
        break;
        case 68:
       if(!ignore)
           rflush();
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rflush" << endl;
        break;
       case 69:
       if(!ignore)
          _print(pkg);
      else if(ignore){
         if(pkg[0] > 2){
           IP--;
           IP--;
           IP += pkg[0];
         }
      }
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "print" << endl;
        break;
        case 70:
       if(!ignore)
           rand_1(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rand_1" << endl;
        break;
        case 71:
       if(!ignore)
           rand_2(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rand_2" << endl;
        break;
        case 72:
       if(!ignore)
           rand_3(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rand_3" << endl;
        break;
        case 74:
       if(!ignore)
           rrand_1(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rrand_1" << endl;
        break;
        case 75:
       if(!ignore)
           rrand_2(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rrand_1" << endl;
        break;
        case 76:
       if(!ignore)
           rrand_3(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "rrand_3" << endl;
        break;
        case 77:
          _printf(pkg);
       if(scmnd && (!ignore))
        cout << ".addr:" << IP << " " <<  "printf" << endl;
        break;
        case 78:
       if(!ignore)
         loadc(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadc" << endl;
         break;
         case 79:
       if(!ignore)
         dload(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "dload" << endl;
       break;
         case 80:
       if(!ignore)
         t_cast(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "t_cast" << endl;
       break;
        case 81:
       if(!ignore)
         sload(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "sload" << endl;
       break;
        case 82:
       if(!ignore)
         loadf(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadf" << endl;
       break;
       case 83:
         _throw(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "throw" << endl;
       break;
       case 84:
       if(!ignore)
         rln(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "rln" << endl;
       break;
       case 85:
       if(!ignore)
         loadi_r(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadi_r" << endl;
       break;
       case 86:
       if(!ignore)
         loadf_r(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "loadf_r" << endl;
       break;
       case 87:
       if(!ignore)
         sload_r(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "sload_r" << endl;
       break;
       case 88:
       if(!ignore)
         dload_r(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "dload_r" << endl;
       break;
       case 89:
       if(!ignore)
         bck_t(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "bck_t" << endl;
       break;
       case 90:
         ct_int(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "ct_int" << endl;
       break;
       case 91:
       if(!ignore)
         ct_float(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "ct_float" << endl;
       break;
       case 92:
       if(!ignore)
         anum(pkg);
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "anum" << endl;
       break;
       case 93:
       if(!ignore)
         _sleep();
       if(scmnd && (!ignore))
       cout << ".addr:" << IP << " " <<  "sleep" << endl;
       break;
       default:
         if(!ignore){
             Log lg;
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

