#include "core0.h"
#include <cstdlib>
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
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <time.h>
using namespace std;

bool inFunc = false;
extern string prog_args;
extern int arg_c;
C0 C;
Log d_log;
void loadi(double *pkg)
{
      if(pkg[1] == 21937856)
         C.setr(0, pkg[0], null);
      else
         C.setr(0, pkg[0], (long) pkg[1]);
}

void rload(double *pkg)
{
    long ref = C.getr(0, pkg[1]);
    double reg = C.getr(0, ref);
    C.setr(0, pkg[0], reg);
}

void r_load(double *pkg)
{
    long ref = C.getr(0, pkg[0]);
    C.setr(0, ref, C.getr(0, pkg[1]));
}

void cp(double *pkg)
{
   C.setr(0, pkg[0], C.getr(0, pkg[1]));
}

void sload(double *pkg)
{
     if(pkg[1] == 21937856)
        C.setr(0, pkg[0], null);
     else
        C.setr(0, pkg[0], (int) pkg[1]);
       // log invalid type assignment
}

void adr(double *pkg)
{
   C.setr(0, pkg[0], (long) pkg[1]);
}

void ct_int(double *pkg)
{
     char a = C.getr(0, pkg[1]);
     int val = a - '0';
     C.setr(0, pkg[0], val);
}

void anum(double *pkg)
{
         stringstream ss;
         ss << C.getr(0, pkg[0]) << C.getr(0, pkg[1]);
         string num = ss.str();
         
         if(I1 == SHORT || I1 == INT)
           C.setr(0, pkg[0], atoi(num.c_str()));
         else if(I1 == DOUBLE || I1 == FLOAT)
           C.setr(0, pkg[0], atof(num.c_str()));
         else {
           EBX = 2;
           d_log.w("System", "warning: canot assignn decimal value to not integer and or float data types");
         }
}

void rln(double *pkg)//  length, start addr, excape  char, 
{
   long s_addr = (long) pkg[0] + 1;
   long max = C.getr(0, pkg[0]);
   long length = 0;
   if(pkg[1] == 10){ // excape char = \n
     string input = "";
     getline(cin, input);
     length = input.length();
     Ram ram;
       for(int i = 0; i < input.length(); i++){
         if(i > max)
           break;
            char a = input.at(i);
            int chr = (int) a;
            C.setr(0, s_addr + i, chr);
       }
         C.setr(0, pkg[0], length);
   }
}

void loadc(double *pkg);
void _string(double *pkg) // string @434 32 'this is the string'
{
 if(pkg[1] <= 0){}
 else if(pkg[1] == 1){
   C.setr(0, pkg[0], 1);
   double *pckg;
   pckg[0] == pkg[0] + 1;
   pckg[1] == pkg[2];
   loadc(pckg);
 }
 else if(pkg[1] >= 2) {
    IP--;
    Disassembler d;
    long addr = pkg[0] + 1;
    if(!ignore)
        C.setr(0, pkg[0], pkg[1]);
    for(int i = 0; i < (long) pkg[1]; i++){
       string str = prog(2, IP++, ""); // get char
       long _str = d.disassemble(str); // dissasemble char
       if(!ignore)
          C.setr(0, addr, _str);
       addr++;
   }
 }
 else{
  cout << "CPU string_length_logic err something went wrong while determing the length of the string to print" << endl;
  EBX = 1;
  p_exit();
 }
}

void c_print(double _char)
{
    char c = _char;
    cout << c;
}

void _print(double *pkg)
{ 
 if(pkg[0] <= 0){}
 else if(pkg[0] == 1){
   IP--;
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
   if(_char == 256){ // reg r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1: " << (_str + 1)<< endl;
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         cout << C.getr(0, _str);
    }
   }
  else if(_char == 257){ // %c r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else{
         char c = C.getr(0, _str);
         cout << c;
      }
    }
   }
  else if(_char == 258){ // %d r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         cout << (long) C.getr(0, _str);
    }
   }
  else if(_char == 259){ // %f r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         printf("%f",C.getr(0, _str));
    }
   }
  else if(_char == 260){ // %x r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
        std::cout << "0x" << std::hex << (long) C.getr(0, _str);
    }
   }
   else if(_char == 261){ // %u r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else{
         unsigned num = (long) C.getr(0, _str);
         cout << num;
      }
    }
   }
  else if(_char == 262){ // %g r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         printf("%g",C.getr(0, _str));
    }
   }
  else if(_char == 263){ // %e r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         printf("%e",C.getr(0, _str));
    }
   }
  else if(_char == 264){ // %do r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         printf("%lf",C.getr(0, _str));
    }
   }
  else if(_char == 265){ // %lg r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         printf("%lg",C.getr(0, _str));
    }
   }
  else if(_char == 266){ // %le r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else
         printf("%le",C.getr(0, _str));
    }
   }
  else if(_char == 267){ // %bl r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else{
         if(C.getr(0, _str) == 1)
           cout << "true";
         else if(C.getr(0, _str) == 0)
           cout << "false";
         else
           cout << C.getr(0, _str);
      }
    }
   }
  else if(_char == 268){ // %s r#
    reg = true;
    Disassembler d;
    string str = prog(2, IP++, ""); // get char
    long _str = d.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(C.getr(0, _str) == null)
        cout << "null";
      else{
         long ref = _str + 1;
         for(int i = 0; i < C.getr(0, _str); i++){
             c_printf(C.getr(0, ref++));
         }
      }
    }
   }
  else if((!ignore)) {
    char c = _char;
    cout << c;
  }
}

extern string prog_data;
void c_update()
{
  Ram r;
  for(int i = 0; i < L1_ICache_length; i++){
      if(i > r.info(5))
          break;
      else {
        C.getr(5, i);
        string instr = prog_data;
        if(instr != L1_ICache[ i ])
           L1_ICache[ i ] = instr;
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
  char c = _ch;
  long chr = c;
  return chr;
}

void loadc(double *pkg)
{
    C.setr(0, pkg[0], _char((long) pkg[1]));
}

void thread_wait(int seconds) 
{ 
    int endwait; 
    endwait = clock() + seconds * CLOCKS_PER_SEC ; 
    while (clock() < endwait){} 
}

void _sleep(double *pkg)
{
   if(SCX < 0)
     SCX *= -1;
   if((long) pkg[0] == 0)
       sleep(SCX);
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
          case 20:
	    EBX = pkg[1];
           break;
  	   case 22:
	    SDX = pkg[1];
           break;
	   case 23:
	    BP = pkg[1];
           break;
 	   case 24:
	    EXC = pkg[1];
           break;
	   case 25:
	    PS = 0;
           break;
	   case 26:
	    LG = pkg[1];
           break;
  	   case 27:
	    LSL = pkg[1];
           break;
           case 28:
	    SFC = pkg[1];
           break;
           case 29:
            SCX = pkg[1];
           break;
           case 30:
            I1 = pkg[1];
           break;
           case 31:
            I2 = pkg[1];
           break;
           case 32:
            TMP = pkg[1];
           break;
           case 33:
	    AI = pkg[1];
           break;
           case 34:
            IPI = pkg[1];
	   break;
      }
}

void r_mv(double *pkg)
{
      switch( (long) pkg[0] )
      {
          case 21:
             C.setr(0, pkg[1], EBX);
           break;
           case 22:
             C.setr(0, pkg[1], SDX);
           break;
           case 23:
             C.setr(0, pkg[1], BP);
           break;
           case 24:
             C.setr(0, pkg[1], EXC);
           break;
           case 25:
             C.setr(0, pkg[1], PS);
           break;
           case 26:
             C.setr(0, pkg[1], LG);
           break;
           case 27:
             C.setr(0, pkg[1], LSL);
           break;
           case 28:
                C.setr(0, pkg[1], SFC);
           break;
           case 29:
                C.setr(0, pkg[1], SCX);
           break;
           case 30:
                C.setr(0, pkg[1], I1);
           break;
           case 31:
                C.setr(0, pkg[1], I2);
           break;
           case 32:
                C.setr(0, pkg[1], TMP);
           break;
           case 36:
                C.setr(0, pkg[1], SCR);
           break;
           case 20:
                C.setr(0, pkg[1], EAX);
           break;
           case 35:
                C.setr(0, pkg[1], IP);
           break;
           case 33:
		C.setr(0, pkg[1], AI);
   	   break;
  	   case 34:
                C.setr(0, pkg[1], IPI);
	   break;
      }
}

void rmov(double *pkg)
{
     switch( (long) pkg[0] )
     {
          case 21:
             if(pkg[1] == 20)
               EBX = EAX;
            else
               EBX = (long) C.getr(0, pkg[1]);
           break;
           case 22:
            if(pkg[1] == 20)
               SDX = EAX;
            else
               SDX = (long) C.getr(0, pkg[1]);
           break;
           case 23:
             if(pkg[1] == 20)
               BP = EAX;
            else
               BP = (long) C.getr(0, pkg[1]);
           break;
           case 24:
	     if(pkg[1] == 20)
               EXC = EAX;
            else
                EXC = (long) C.getr(0, pkg[1]);
           break;
           case 26:
	     if(pkg[1] == 20)
               LG = EAX;
            else
               LG = (long) C.getr(0, pkg[1]);
           break;
           case 27:
             if(pkg[1] == 20)
               LSL = EAX;
            else
                   LSL =  (long) C.getr(0, pkg[1]);
            break;
           case 28:
 	     if(pkg[1] == 20)
               SFC = EAX;
            else
               SFC = (long) C.getr(0, pkg[1]);
           break;
           case 29:
	     if(pkg[1] == 20)
               SCX = EAX;
            else
                SCX = (long) C.getr(0, pkg[1]);
           break;
           case 30:
             if(pkg[1] == 20)
               I1 = EAX;
            else
               I1 = (long) C.getr(0, pkg[1]);
           break;
           case 31:
             if(pkg[1] == 20)
               I2 = EAX;
            else
               I2 = (long) C.getr(0, pkg[1]);
           break;
           case 32:
             if(pkg[1] == 20)
               TMP = EAX;
            else
               TMP = (long) C.getr(0, pkg[1]); 
            break;
     }
}


long iph, ipl; // ip high and low for threads
void invoke(double *pkg)
{
     switch((long) pkg[0] )
     {
       case 0:
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
         long data[8];
         switch( SFC ) {
            case 0:
                SCR = io.Read(0,data);
                if(SCR == -1)
                   EBX = 3;
	    break;
            case 1:
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
       case 10: // goto <address>(could be used for multitasking)
	    C.Interrupt(SDX);
		SCR = 0;
       break;
       case 11: // set IP back to original pos before it was interrupted
          IP = auto_ipi;
       break;
       case 18: // assemble data
        {
          Disassembler d;
          string bin = d.assemble(SDX);
          SDX = bin.length();
          int c = 0;
          for(long i = SCX; c < bin.length(); i++){
             C.setr(0, i, bin.at(c));
             c++;
          }
        }
       break;
       case 19: // dissassemble data
        {
          Disassembler d;
          string bin = "";
          stringstream ss1;
          for(long i = SDX; i < (SDX + SCX); i++){
             ss1 << C.getr(0, i);
          }
          bin += "" + ss1.str();
          SDX = (long) d.disassemble(bin);
        }
       break;
       case 35:
        {
          C.setr(0, SDX, prog_args.length());
          long start_addr = SCX;
          for(int i = 0; i < prog_args.length(); i++){
             int ch = prog_args.at(i);
             C.setr(0, start_addr + i, ch);
          }
          SCX = arg_c - 2;
        }
       break;
       case 50: // read to a file
        {
          data[0] = pkg[1];
          SCR = io.Read(1,data); // read to a file
        }
       break;
       case 51: // write to a file
        {
          data[0] = pkg[1];
          SCR = io.Write(1,data); // write to a file
        }
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
void lock(double *pkg)
{
	 if(C.getr(3, pkg[0]) == 0)
          C.setr(2, pkg[0], C.getr(0, pkg[0]));
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
           if( pkg[1] == 20)
               C.setr(0, pkg[0], tibool(EAX == C.getr(0, pkg[2])));
           else if(pkg[2] == 20)
               C.setr(0, pkg[0], tibool(C.getr(0, pkg[1]) == EAX));
           else
               C.setr(0, pkg[0], tibool(C.getr(0, pkg[1]) == C.getr(0, pkg[2])));

}

void ulock(double *pkg)
{
      if(C.getr(3, pkg[0]) == 0)
         C.setr(0, pkg[0], C.getr(2, pkg[0]));
}

void push(double *pkg)
{
  RuntimeException x;
   if(!inFunc){
    inFunc = true;
          C.setr(0, pkg[0], IP);
          ignore = true;
   }
   else
      x.introduce("FunctionCallException", "cannot initalize a function inside another function!");
}

void _return(double *pkg)
{
    inFunc = false;
	RuntimeException re;
        if(ignore && pkg[1] == 0)
            ignore = false;
        else if(ignore && pkg[1] == 1) { 
               // skip
			   inFunc = true;
        }
        else
            IP = (long) C.getr(0, pkg[0]);
}

void call(double *pkg)
{
      TMP = IP;
      IP = (long) C.getr(0, pkg[0]);
      C.setr(0, pkg[0], TMP);
}

void swp(double *pkg)
{
     TMP = C.getr(0, pkg[0]);
     C.setr(0, pkg[0], C.getr(0, pkg[1]));
     C.setr(0, pkg[1], TMP);
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
         C.setr(0, pkg[0], IP);
         C.setr(0, pkg[1], C.getr(0, pkg[2]));
         waiting = true;
}

void end() // for do
{
  if((passed_if > 0) && if_ignore){
      passed_if--;
      return;
  }
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
	    if(C.getr(0, pkg[0]) == 1){}
            else {
	       if_ignore = true;
	       ignore = true;
            }
}

void ilt(double *pkg)
{
	    if(C.getr(0, pkg[0]) < C.getr(0, pkg[1])){}
            else {
	       if_ignore = true;
               ignore = true;
	    }
}

void igt(double *pkg)
{
		if(C.getr(0, pkg[0]) > C.getr(0, pkg[1])){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void ile(double *pkg)
{
		if(C.getr(0, pkg[0]) <= C.getr(0, pkg[1])){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void ige(double *pkg)
{
		if(C.getr(0, pkg[0]) >= C.getr(0, pkg[1])){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void ndo(double *pkg)
{
            if(C.getr(0, pkg[0]) == 0){}
            else {
               if_ignore = true;
               ignore = true;
            }
}

void inlt(double *pkg)
{
		if(!(C.getr(0, pkg[0]) < C.getr(0, pkg[1]))){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void ingt(double *pkg)
{
		if(!(C.getr(0, pkg[0]) > C.getr(0, pkg[1]))){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void t_cast(double *pkg)
{
     RuntimeException re;
		switch( (long) pkg[1] ){
                    case 0: // short
                       C.setr(0, pkg[0], (int) C.getr(0, pkg[0]));
                    break;
		    case 1: // int
		       C.setr(0, pkg[0], (long) C.getr(0, pkg[0]));
		    break;
                    case 2: //  float
                       C.setr(0, pkg[0], (float) C.getr(0, pkg[0]));
                    break;
		    case 3: // double
	               C.setr(0, pkg[0], (double) C.getr(0, pkg[0]));
		    break;
                    case 4: // char
                     {
                       char ch = C.getr(0, pkg[0]);
                       int c = ch;
                       C.setr(0, pkg[0], c);
                     }
                    break;
                    case 5: // bool
                       C.setr(0, pkg[0], ibool(C.getr(0, pkg[0])));
                    break;
	            default: // err
		        stringstream ss;
		        ss << "the specified cast value [" << pkg[1] << "] is not a valid arg[double(3),float(2),int(1),short(0)]";
			re.introduce("UnknownCastException", ss.str());
		    break;
		}
}

void inle(double *pkg)
{
		if(!(C.getr(0, pkg[0]) <= C.getr(0, pkg[1]))){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void inge(double *pkg)
{
		if((C.getr(0, pkg[0]) >= C.getr(0, pkg[1])) == false){}
		else {
		  if_ignore = true;
		  ignore = true;
		}
}

void neg(double *pkg){
	RuntimeException re;
    if(I1 == INT || I1 == DOUBLE
           || I1 == SHORT || I1 == FLOAT)
      C.setr(0, pkg[0], (C.getr(0, pkg[0]) * -1));
    else if(I1 == BOOL){
           if(C.getr(0, pkg[0]) == 0)
              C.setr(0, pkg[0], 1);
           else if(C.getr(0, pkg[0]) == 1)
              C.setr(0, pkg[0], 0);
    }
    else
       re.introduce("UnsatisfiedTypeException","must specify correct type to be inverted");
}
