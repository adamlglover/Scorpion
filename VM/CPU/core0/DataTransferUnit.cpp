#include "core0.h"
#include <stdlib.h>
#include "runtime_exception.h"
#include "../../System.h"
#include "../../program.h"
#include "../../var.h"
#include "io.h"
#include "../x86Disassm/disassembler.h"
#include "../../Log/filter.h"
#include "cpuf.h"
#include "../../Log/Log.h"
#include "../../Ram/ram.h"
#include "../../GPIO/gpio.h"
#include "io.h"
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
using namespace std;

bool inFunc = false;
C0 C;
Log d_log;
void loadi(double *pkg)
{
      if(pkg[1] == 21937856)
         C.setr(0, pkg[0], null);
      else
         C.setr(0, pkg[0], (long) pkg[1]);
       // log invalid type assignment
}

void rload(double *pkg)
{
    long ref = C.getr(0, pkg[1]);
    double reg = C.getr(0, ref);
    C.setr(0, pkg[0], reg);
}

void sload(double *pkg)
{
     if(pkg[1] == 21937856)
        C.setr(0, pkg[0], null);
     else
        C.setr(0, pkg[0], (int) pkg[1]);
       // log invalid type assignment
}

void ct_int(double *pkg)
{
  RuntimeException re;
  if(I1 == SHORT) || (I1== INT)){
     char a = C.getr(0, pkg[1]);
     int val = a - '0';
     C.setr(0, pkg[0], val);
  }
  else
     re.introduce("UnsatisfiedTypeException","invalid type assignment, inputed type is not of type int");
}

void anum(double *pkg)
{
         stringstream ss;
         ss << C.getr(0, pkg[0]) << C.getr(0, pkg[1]);
         string num = ss.str();
         
         if(I1 == SHORT) || (I1 == INT))
           C.setr(0, pkg[0], atoi(num.c_str()));
         else if(I1 == DOUBLE) || (I1 == FLOAT))
           C.setr(0, pkg[0], atof(num.c_str()));
         else {
           EBX = 2;
           d_log.w("System", "warning: canot assignn decimal value to not integer and or float data types");
         }
}

void rln(double *pkg)//  length, start addr, excape  char, 
{
   long s_addr = (long) pkg[1];
   long length = 0;
   if(pkg[2] == 10){ // excape char = \n
     string input = "";
     getline(cin, input);
     length = input.length();
     Ram ram;
     if(input.length() <= (ram.info(0) - s_addr)){ // resources available
       for(int i = 0; i < input.length(); i++){
            char a = input.at(i);
            int chr = (int) a;
            C.setr(1, s_addr + i, CHAR);
            C.setr(0, s_addr + i, chr);
         //   cout << "saving " << a << endl;
       }
       if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0])))
         C.setr(0, pkg[0], length);
       else
         cout << "number must be an integer";
     }
     else
      cout << "resources unavailable";
   }
}

void rflush()
{
  Ram ram;
  for(int cell = 0; cell < ram.info(2) - 1; cell++){
      stringstream ss;
      ss << cell;
      d_log.i("System","Flushing cell [" + ss.str() + "]");
      for(int i = 0; i < ram.info(0); i++)
          C.setr(cell, i, 0);
  }
}

void c_print(double _char)
{
  if(_char == 256)
    cout << "\n";
  else if(_char == 257)
    cout << "\t";
  else if(_char == 258)
    cout << "";
  else if((_char >= 0) && (_char <= 255)) {
    char c = _char;
    cout << c;
  }
  else{
   stringstream ss;
   ss << "warning: value " << _char << " is not a char" << endl;
   d_log.w("System", ss.str());
   EBX = 2; 
  }
}

void _print(double *pkg)
{ 
 if(pkg[0] <= 0){}
 else if(pkg[0] == 1){
   c_print(pkg[1]);
 }
 else if(pkg[0] == 2){
   c_print(pkg[1]);
   c_print(pkg[2]);
 }
 else if(pkg[0] > 2) {
    IP--;
    IP--;
    Disassembler d;
    for(int i = 0; i < pkg[0]; i++){
       string str = prog(2, IP++, ""); // get char
       long _str = d.disassemble(str); // dissasemble char
       c_print(_str); // print char
   }
 }
 else{
  cout << "CPU print_length_logic err something went wrong while determing the length of the string to print" << endl;
  EBX = 1;
  p_exit();
 }
}

bool reg = false;
string str_bool(long a)
{
  if(a == 1)
    return "true";
  else
    return "false";
}

void c_printf(double _char)
{
  if(_char == 256 && !ignore)
    cout << "\n";
  else if(_char == 257  && !ignore)
    cout << "\t";
  else if(_char == 258  && !ignore)
    cout << "";
  else if(_char == 0){ // reg r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1: " << (_str + 1)<< endl;
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else if(C.getr(1, _str) == BOOL)
        cout << str_bool((long) C.getr(0, _str));
      else
         cout << C.getr(0, _str);
    }
   }
  else if(_char == 1){ // %c reg r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else if(C.getr(1, _str) == BOOL)
        cout << str_bool((long) C.getr(0, _str));
      else{
         char c = C.getr(0, _str);
         cout << c;
      }
    }
   }
  else if((_char >= 5) && (_char <= 255)  && (!ignore)) {
    char c = _char;
    cout << c;
  }
  else {
   if(!ignore){
      stringstream ss;
      ss << "system warning: value " << _char << " is not a char" << endl;
      d_log.w("System", ss.str());
      EBX = 2;
   }  
  }
}

void _printf(double *pkg)
{
 if(pkg[0] <= 0){}
 else if(pkg[0] >= 1) {
    IP--;
    IP--;
    Disassembler d;
    for(int i = 0; i < pkg[0]; i++){
       string str = prog(2, IP++, ""); // get char
       long _str = d.disassemble(str); // dissasemble char
       c_printf(_str); // print char
   }
   if((pkg[0] == 1) && !(reg))
    IP++;
   reg = false;
 }
 else{
  cout << "CPU print_length_logic err something went wrong while determing the length of the string to print" << endl;
  EBX = 1;
  p_exit();
 }
}

string e_throw(long _char)
{
  if(_char == 256 && !ignore)
    return "\n";
  else if(_char == 257  && !ignore)
    return "\t";
  else if(_char == 258  && !ignore)
    return "";
  else if(_char == 0){ // reg r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1: " << (_str + 1)<< endl;
    if(!ignore){
      if(C.getr(0, _str) == null)
        return "null";
      else if(C.getr(1, _str) == BOOL)
        return str_bool((long) C.getr(0, _str));
      else {
         stringstream ss;
         ss << C.getr(0, _str);
         return ss.str() + "";
      }
    }
  }
  else if((_char >= 5) && (_char <= 255)  && (!ignore)) {
    char c = _char;
    return "" + c;
  }
  else {
   if(!ignore){
      stringstream ss;
      ss << "warning: value " << _char << " is not a char" << endl;
      d_log.w("System", ss.str());
      EBX = 2;
   }
  }
}

void _throw(double *pkg)
{
  string excpn = "", msg = "", str;

  long _str;
  IP--;
  Disassembler d;
  RuntimeException re;
    for(int i = 0; i < pkg[0]; i++){ // Exception
       _str = (long) d.disassemble(prog(2, IP++, "")); // dissasemble char
       cout << _str << endl;
       excpn.append(e_throw(_str)); // print char
    }

    for(int i = 0; i < pkg[1]; i++){ // E_Message
       _str = (long) d.disassemble(prog(2, IP++, "")); // dissasemble char
       cout << _str << endl;
       msg.append(e_throw(_str)); // print char
    }

    if(!ignore)
        re.introduce(excpn,  msg);
}

void loadr(double *pkg)
{
      C.setr(0, pkg[0], C.getr(0, pkg[1]));
}

int ibool(long);
void loadbl(double *pkg)
{
     C.setr(0, pkg[0], ibool( (long) pkg[1]));
       // log invalid type assignment
}

long _char(long _ch)
{
  if(_ch >= 5 && _ch <= 258)
     return _ch;
  else 
     return 5;
}

void loadc(double *pkg)
{
    C.setr(0, pkg[0],(long) _char((long) pkg[1]));
}

void _sleep(double *pkg)
{
   if(SCX < 0)
     SCX *= -1;
   if((long) pkg[0] == 0)
       sleep(SCX); // sleep curr thread for specified secs
   else
      usleep(SCX); // sleep for mills
}

void dload(double *pkg)
{
          stringstream ss;
          ss << pkg[1] << "." << pkg[2];
          string dec = ss.str();
          if(atof(dec.c_str()) == 21937856.0)
             C.setr(0, pkg[0], null);
          else
             C.setr(0, pkg[0], atof(dec.c_str()));
       // log invalid type assignmen
}

void loadf(double *pkg)
{
          stringstream ss;
          ss << pkg[1] << "." << pkg[2];
          string dec = ss.str();
          if(atof(dec.c_str()) == 21937856)
             C.setr(0, pkg[0], null);
          else
             C.setr(0, pkg[0], atof(dec.c_str()));
       // log invalid type assignment
}

void mov(double *pkg)
{
      switch( (long) pkg[0] )
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
	    PS = 0;
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
           case 11:
            TMP = pkg[1];
           break;
      }
}

void r_mv(double *pkg)
{
      switch( (long) pkg[0] )
      {
          case 0:
            if(I1 == INT || I1 == SHORT)
                 C.setr(0, pkg[1], EBX);
            else
	       d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 1:
            if(I1 == INT || I1 == SHORT)
                 C.setr(0, pkg[1], SDX);
            else
	       d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 2:
             if(I1 == INT || I1 == SHORT)
                 C.setr(0, pkg[1], BP);
             else
	        d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 3:
             if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], EXC);
             else
		d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 4:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], PS);
            else
	       d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 5:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], LG);
            else
	       d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 6:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], LSL);
            else
               d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 7:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], SFC);
            else
               d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 8:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], SCX);
            else
	       d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 9:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], I1);
            else
	       d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 10:
            if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], I2);
            else
               d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 11:
             if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], TMP);
             else
                d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 12:
             if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], SCR);
             else
                d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
           case 13:
             if(I1 == INT || I1 == SHORT)
                C.setr(0, pkg[1], EAX);
             else
                d_log.w("System", "warning: type must be an integer type to obtain cpu register info");
           break;
      }
}

void rmov(double *pkg) // ----------------------------------------------------------------------------
{
     switch( (long) pkg[0] )
     {
          case 0:
             if(pkg[1] == 21)
               EBX = EAX;
            else{
              if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                 EBX = C.getr(0, pkg[1]);
              else{
		EBX = 2;
	        d_log.w("System", "warning: type must be an integer type to modify cpu registers");
     	      }
            }
           break;
           case 1:
            if(pkg[1] == 21)
               SDX = EAX;
            else{
              if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                 SDX = C.getr(0, pkg[1]);
              else{
	        EBX = 2;
	        d_log.w("System", "warning: type must be an integer type to modify cpu registers");
              }
            }
           break;
           case 2:
             if(pkg[1] == 21)
               BP = EAX;
            else{
             if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
               BP = C.getr(0, pkg[1]);
             else{
	        EBX = 2;
                d_log.w("System", "warning: type must be an integer type to modify cpu registers");
	     }
            }
           break;
           case 3:
	     if(pkg[1] == 21)
               EXC = EAX;
            else{
             if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                EXC = C.getr(0, pkg[1]);
             else{
	        EBX = 2;
		d_log.w("System", "warning: type must be an integer type to modify cpu registers");
	     }
            }
           break;
           case 5:
	     if(pkg[1] == 21)
               LG = EAX;
            else{
              if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
               LG = C.getr(0, pkg[1]);
              else{
	        EBX = 2;
                d_log.w("System", "warning: type must be an integer type to modify cpu registers");
	      }
            }
           break;
           case 6:
             if(pkg[1] == 21)
               LSL = EAX;
            else{
               if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                   LSL =  C.getr(0, pkg[1]);
               else{
	         EBX = 2;
                 d_log.w("System", "warning: type must be an integer type to modify cpu registers");
               }
            }
            break;
           case 7:
 	     if(pkg[1] == 21)
               SFC = EAX;
            else{
             if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
               SFC = C.getr(0, pkg[1]);
             else{
	       EBX = 2;
	       d_log.w("System", "warning: type must be an integer type to modify cpu registers");
             } 
           }
           break;
           case 8:
	     if(pkg[1] == 21)
               SCX = EAX;
            else{
              if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                SCX = C.getr(0, pkg[1]);
              else{
	         EBX = 2;
	         d_log.w("System", "warning: type must be an integer type to modify cpu registers");
	      }
            }
           break;
           case 9:
             if(pkg[1] == 21)
               I1 = EAX;
            else{
             if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
               I1 = C.getr(0, pkg[1]);
	        else{
	          EBX = 2;
                  d_log.w("System", "warning: type must be an integer type to modify cpu registers");
	        }
            }
           break;
           case 10:
             if(pkg[1] == 21)
               I2 = EAX;
            else{
             if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
               I2 = C.getr(0, pkg[1]);
	        else{
	           EBX = 2;
		   d_log.w("System", "warning: type must be an integer type to modify cpu registers");
	        }
            }
           break;
           case 11:
             if(pkg[1] == 21)
               TMP = EAX;
            else{
             if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                TMP = C.getr(0, pkg[1]); 
             else{
	        EBX = 2;
                d_log.w("System", "warning: type must be an integer type to modify cpu registers");
             }
            }
            break;
     }
}

void invoke(double *pkg)
{
     switch((long) pkg[0] )
     {
       case 0:
        // will be used soon
       break;
       case 1: // log
        Log _l;
        if(LG == 1)
          _l.On();
        else if(LG == 0)
          _l.Shutdown();

        SetPriority(LSL);
       break;
       case 5:// I/O for GPIO pins
         InputOutput io;
         long data[2];
         switch( SFC ) {
            case 0:
              {
                data[0] = SDX;
                SCR = io.Read(0,data);
                if(SCR == -1)
                   EBX = 3;
              }
	    break;
            case 1:
              data[0] = SDX;
              data[1] =  TMP;
              SCR = io.Write(0,data);
              if(SCR == -1)
                 EBX = 3;
      	    break;
	  }
       break;
       case 6: // Os Calls for GPIO
           switch( SFC ) {
            case 0:// set dir
              SCR = GPIODirection(SDX, TMP);
              if(SCR == -1)
                 EBX = 3;
            break;
            case 1: // unexport
              SCR = GPIOUnexport(SDX);
              if(SCR == -1)
                 EBX = 3;
            break;
            case 2: // export
              SCR = GPIOExport(SDX);
              if(SCR == -1)
                 EBX = 3;
            break;
          }
       break;
       case 10: // goto (could be used for multitasking)
	    C.Interrupt(SDX);
		SCR = 0;
       break;
       default:
       stringstream ss;
       ss << pkg[0];
       RuntimeException re;
       re.introduce("IllegalSystemCallExcpetion", "code is not a system call [" + ss.str() + "]");
       break;

     }
}

Ram r;
void mlock(double *pkg)
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

void lock(double *pkg)
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
       d_log.v("System","warning: ram lock err cannot lock excluded address into ram #{" + ss.str() + "}");
       EBX = 2;
      }
}

void xreg(double *pkg)
{
     if(C.getr(3, pkg[0]) == 0)
        C.setr(3, pkg[0], 1);
     else if(C.getr(3, pkg[0]) == 1)
        C.setr(3, pkg[0], 0);
}

void mulock(double *pkg)
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

void clx(double *pkg)
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

void same(double *pkg)
{
	RuntimeException re;
	if(C.getr(1, pkg[0]) == BOOL){
           if(C.getr(0, pkg[1]) == 21)
               C.setr(0, pkg[0], tibool(EAX == C.getr(0, pkg[2])));
           else if(C.getr(0, pkg[2]) == 21)
               C.setr(0, pkg[0], tibool(C.getr(0, pkg[1]) == EAX));
           else
               C.setr(0, pkg[0], tibool(C.getr(0, pkg[1]) == C.getr(0, pkg[2])));
	}
	else
	  re.introduce("UnsatisfiedTypeException","the type reciving the input must be of type bool");

}

void ulock(double *pkg)
{
      if(C.getr(3, pkg[0]) == 0) {
         C.setr(0, pkg[0], C.getr(2, pkg[0]));
         C.setr(1, pkg[0], C.getr(4, pkg[0]));
      }
}

void rm(double *pkg)
{
      C.setr(0, pkg[0], null);
      C.setr(1, pkg[0], OI);
}

void func(double *pkg)
{
          if(C.getr(1, pkg[0]) == OI){
            C.setr(0, pkg[0], null);
            C.setr(1, pkg[0], UFUNC);
          }
          else if((C.getr(1, pkg[0]) == FUNC) || (C.getr(1, pkg[0]) == UFUNC)){ }
          else{
	    EBX = 2;
	    stringstream ss;
	    ss << "warning: cannot create func at addr " << pkg[0];
	    d_log.w("System",ss.str());
          }
}

void push(double *pkg)
{
  RuntimeException x;
   if(!inFunc){
    inFunc = true;
       if(C.getr(1, pkg[0]) == UFUNC){
          C.setr(0, pkg[0], IP);
          C.setr(1, pkg[0], FUNC);
          ignore = true;
       }
       else if(C.getr(1, pkg[0]) == FUNC){
            stringstream ss;
            ss << pkg[0];
            x.introduce("FunctionInitializationException", "multiple definition of func " + ss.str());
       } 
       else{
         stringstream ss;
         ss << "addr " << pkg[0] << " is not a func";
         x.introduce("NotAFuncException", ss.str());
       }
   }
   else
      x.introduce("FuncCallException", "cannot run a function inside another function!");
}

void _return(double *pkg)
{
        inFunc = false;
	RuntimeException re;
        if(ignore && pkg[1] == 0)
            ignore = false;
        else if(ignore && pkg[1] == 1) { 
               // skip
        }
        else {
         if(C.getr(1, pkg[0]) == FUNC)
            IP = (long) C.getr(0, pkg[0]);
         else if(C.getr(1, pkg[0]) == UFUNC){
             stringstream ss;
             ss << "fatal err;" << " cannot return an unreferenced func at addr " << pkg[0];
             re.introduce("FunctionCallException", ss.str());
         }
         else{
            stringstream ss;
            ss << "addr " << pkg[0] << " is not a func";
            re.introduce("NotAFuncException", ss.str());
         }
        }
}

void call(double *pkg)
{
	RuntimeException re;
       if(C.getr(1, pkg[0]) == UFUNC){
             stringstream ss;
	     ss << "unidentified refrence to func " << pkg[0] ;
             re.introduce("FunctionCallException", ss.str());
       }
       else if(C.getr(1, pkg[0]) == FUNC){
          TMP = IP;
          IP = (long) C.getr(0, pkg[0]);
          C.setr(0, pkg[0], TMP);
       }
       else{
	 stringstream ss;
	 ss << "addr " << pkg[0] << " is not a func";
         re.introduce("NotAFunctionException", ss.str());
       }
}

void bck_t(double *pkg)
{
    RuntimeException re;
       if(C.getr(1, pkg[0]) == FUNC){
        //   cout << "setting ip " << C.getr(0, pkg[1]);
           if(C.getr(1, pkg[1]) == INT || C.getr(1, pkg[1]) == SHORT)
                C.setr(0, pkg[0], C.getr(0, pkg[1]));
             else{
                EBX = 2;
                d_log.w("System", "warning: type must be an integer type to set bck_t");
             }
       }
       else if(C.getr(1, pkg[0]) == UFUNC){
          EBX = 2;
          d_log.w("System", "func must be initalized before setting bck_t");
       }
       else{
         stringstream ss;
         ss << "addr " << pkg[0] << " is not a func";
         re.introduce("NotAFunctionException", ss.str());
       }
}

void swp(double *pkg)
{
          TMP = C.getr(0, pkg[0]);
          C.setr(0, pkg[0], C.getr(0, pkg[1]));
          C.setr(0, pkg[1], TMP);

         TMP = C.getr(1, pkg[0]);
          C.setr(1, pkg[0], C.getr(1, pkg[1]));
          C.setr(1, pkg[1], TMP);
}

void eof(double *pkg)
{
      C.setr(1, pkg[0], OI);
}

void loop(double *pkg)
{
         C.setr(0, pkg[1], pkg[2]);
         C.setr(0, pkg[0], IP);
         waiting = true;
}

void wloop(double *pkg)
{
      if(C.getr(0, pkg[0]) == 1)
         C.setr(0, pkg[1], IP);
      else {
         pass = true;  // do not run the contents in the loop
         ignore = true;
      }
}

void endwl(double *pkg)
{
  if(pass){
     ignore = false;
     pass = false;
  }
  else if(!ignore && (C.getr(0, pkg[0]) == 1)) // loop again
       IP = C.getr(0, pkg[1]);
}

void rloop(double *pkg)
{
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

void endl(double *pkg)
{
   if(waiting){
      C.setr(0, pkg[1], (C.getr(0, pkg[1]) - 1));
    if(C.getr(0, pkg[1]) <= 0)
        waiting = false;
   else {
      IP = C.getr(0, pkg[0]);
   }
  }
}

void _do(double *pkg)
{
	RuntimeException re;
	if(C.getr(1, pkg[0]) == BOOL){
	    if(C.getr(0, pkg[0]) == 1){}
            else {
	       if_ignore = true;
	       ignore = true;
            }
	}
	else
	  re.introduce("UnsatisfiedTypeException","the type inputed must be of type bool");
}

void ilt(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
	    if(C.getr(0, pkg[0]) < C.getr(0, pkg[1])){}
            else {
	       if_ignore = true;
               ignore = true;
	    }
	}
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void igt(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if(C.getr(0, pkg[0]) > C.getr(0, pkg[1])){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
        }
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void iltoeq(double *pkg)
{
    RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if(C.getr(0, pkg[0]) <= C.getr(0, pkg[1])){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
        }
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void igtoeq(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if(C.getr(0, pkg[0]) >= C.getr(0, pkg[1])){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
        }
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void ndo(double *pkg)
{
	RuntimeException re;
	if(C.getr(1, pkg[0]) == BOOL){
		if(C.getr(0, pkg[0]) == 0){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
	}
	else
	  re.introduce("UnsatisfiedTypeException","the type inputed must be of type bool");
}

void inlt(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if(!(C.getr(0, pkg[0]) < C.getr(0, pkg[1]))){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
        }
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void ingt(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if(!(C.getr(0, pkg[0]) > C.getr(0, pkg[1]))){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
        }
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void t_cast(double *pkg)
{
     RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		switch( (long) pkg[1] ){
                    case 0: // int
                       C.setr(1, pkg[0], SHORT);
                    break;
		    case 1: // int
		       C.setr(1, pkg[0], INT);
		    break;
                    case 2: // int
                       C.setr(1, pkg[0], FLOAT);
                    break;
		    case 3: // double
	               C.setr(1, pkg[0], DOUBLE);
		    break;
	            default: // err
		        stringstream ss;
		        ss << "the specified cast value [" << pkg[1] << "] is not a valid arg[double(3),float(2),int(1),short(0)]";
			re.introduce("UnknownCastException", ss.str());
		    break;
		}
	}
	else
	   re.introduce("UnsatisfiedTypeException","the type inputed must be an integer type");
}

void inltoeq(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if(!(C.getr(0, pkg[0]) <= C.getr(0, pkg[1]))){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
	}
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void ingtoeq(double *pkg)
{
	RuntimeException re;
	if(is_integer(C.getr(1, pkg[0]), C.getr(1, pkg[0]))){
		if((C.getr(0, pkg[0]) >= C.getr(0, pkg[1])) == false){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
        }
	else
	   re.introduce("UnsatisfiedTypeException","the types inputed must be an integer type");
}

void neg(double *pkg){
	RuntimeException re;
    if(C.getr(1, pkg[0]) == INT || C.getr(1, pkg[0]) == DOUBLE
           || C.getr(1, pkg[0]) == SHORT || C.getr(1, pkg[0]) == FLOAT)
      C.setr(0, pkg[0], (C.getr(0, pkg[0]) * -1));
    else if(C.getr(1, pkg[0]) == BOOL){
           if(C.getr(0, pkg[0]) == 0)
              C.setr(0, pkg[0], 1);
           else if(C.getr(0, pkg[0]) == 1)
              C.setr(0, pkg[0], 0);
    }
    else
       re.introduce("UnsatisfiedTypeException","the type inputed cannot be inverted");
}
