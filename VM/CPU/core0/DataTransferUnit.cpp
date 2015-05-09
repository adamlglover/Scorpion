#include "core0.h"
#include <cstdlib>
#include "runtime_exception.h"
#include "../../System.h"
#include "../../program.h"
#include "../../var.h"
#include "io.h"
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
void loadi(double *pkg)
{
   if(pkg[1] == 21937856)
     core0.setr(0, pkg[0], null);
   else
     core0.setr(0, pkg[0], (long) pkg[1]);
}

void rload(double *pkg)
{
    long ref = core0.getr(0, pkg[1]);
    double reg = core0.getr(0, ref);
    core0.setr(0, pkg[0], reg);
}

void r_load(double *pkg)
{
    long ref = core0.getr(0, pkg[0]);
    core0.setr(0, ref, core0.getr(0, pkg[1]));
}

void cp(double *pkg)
{
   core0.setr(0, pkg[0], core0.getr(0, pkg[1]));
}

void swi(double *pkg)
{
   long ip = IP;	
   long start_addr = SDX;
   for(long i= 0; i < pkg[0]; i++)
        core.Interrupt(start_addr++);
   IP = ip;     
}

int tibool(bool val);
void strcp(double *pkg)
{
   stringstream ss, ss1;
   long start_addr = SDX + 1; // string 1
   char ch;
   for(int i = 0; i < core0.getr(0, SDX); i++){
        ch = core0.getr(0, start_addr++);
        ss << ch;
   }

   start_addr = SCX + 1; // string 2
   for(int i = 0; i < core0.getr(0, SCX); i++){
         ch = core0.getr(0, start_addr++);
         ss1 << ch;
   }
    reg_check_set( pkg[0], tibool(ss.str() == ss1.str()));
}

bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

void strcpi(double *pkg)
{
   stringstream ss, ss1;
   long start_addr = SDX + 1; // string 1
   char ch;
   for(int i = 0; i < core0.getr(0, SDX); i++){
        ch = core0.getr(0, start_addr++);
        ss << ch;
   }

   start_addr = SCX + 1; // string 2
   for(int i = 0; i < core0.getr(0, SCX); i++){
         ch = core0.getr(0, start_addr++);
         ss1 << ch;
   }
    reg_check_set( pkg[0], tibool(iequals(ss.str(),ss1.str())));
}

void e2str(double *pkg)
{
   stringstream ss;
   ss << core0.getr(0, SDX);
   string num = ss.str();
   long start_addr = SCX + 1; // the str
   char ch;
   for(int i = 0; i < num.length(); i++){
        core0.setr(0, start_addr++, num.at(i));
   }
     core0.setr(0, SCX, num.length());
}

void sload(double *pkg)
{
   if(pkg[1] == 21937856)
     core0.setr(0, pkg[0], null);
   else
     core0.setr(0, pkg[0], (int) pkg[1]);
}

void adr(double *pkg)
{
   reg_check_set( pkg[0], (long) pkg[1]);
}

void ct_int(double *pkg)
{
   char a = core0.getr(0, pkg[1]);
   if(a == '0')
    core0.setr(0, pkg[0], 0);
   else if (a == '1')
    core0.setr(0, pkg[0], 1);
   else if (a == '2')
    core0.setr(0, pkg[0], 2);
   else if (a == '3')
    core0.setr(0, pkg[0], 3);
   else if (a == '4')
    core0.setr(0, pkg[0], 4);
   else if (a == '5')
    core0.setr(0, pkg[0], 5);
   else if (a == '6')
    core0.setr(0, pkg[0], 6);
   else if (a == '7')
    core0.setr(0, pkg[0], 7);
   else if (a == '8')
    core0.setr(0, pkg[0], 8);
   else if (a == '9')
    core0.setr(0, pkg[0], 9);
   else
    core0.setr(0, pkg[0], 0);
}

void anum(double *pkg)
{
   stringstream ss;
   ss << core0.getr(0, pkg[0]) << core0.getr(0, pkg[1]);
   string num = ss.str();

   if(I1 == SHORT || I1 == INT)
     core0.setr(0, pkg[0], atoi(num.c_str()));
   else if(I1 == DOUBLE || I1 == FLOAT)
     core0.setr(0, pkg[0], atof(num.c_str()));
   else {
      EBX = 2;
      lg.w("System", "warning: canot assignn decimal value to not integer and or float data types");
   }
}

void rln(double *pkg)//  length, start addr, excape  char, 
{
   long s_addr = (long) pkg[0] + 1;
   long max = core0.getr(0, pkg[0]);
   long length = 0;
   if(pkg[1] == 10){ // excape char = \n
     string input = "";
     getline(cin, input);
     length = input.length();
     char a;
     int chr;
     for(int i = 0; i < input.length(); i++){
       if(i > max)
         break;
          a = input.at(i);
          chr = (int) a;
          core0.setr(0, s_addr++, chr);
     }
       core0.setr(0, pkg[0], length);
   }
   else {
     string input = "", tmp = "";
     Ram ram;
     char a = pkg[1];
     int chr;
     stringstream ss;
     ss << a;
      while (true) {
       getline(cin, tmp);
        if (tmp == ss.str()) {
            break;
        }
        else
         input += tmp + "\n";
    }
    for(int i = 0; i < input.length(); i++){
       if(i > max)
         break;
          a = input.at(i);
          chr = (int) a;
          core0.setr(0, s_addr++, chr);
     }
      	 length = input.length();
       core0.setr(0, pkg[0], length);
   }
}

void loadc(double *pkg);
void _string(double *pkg) // string @434 32 'this is the string'
{
 if(pkg[1] <= 0){}
 else if(pkg[1] == 1){
   core0.setr(0, pkg[0], 1);
   double *pckg;
   pckg[0] == pkg[0] + 1;
   pckg[1] == pkg[2];
   loadc(pckg);
 }
 else if(pkg[1] >= 2) {
    IP--;
    long addr = pkg[0] + 1;
    if(!ignore)
        core0.setr(0, pkg[0], pkg[1]);
    string str;
    long _str;
    for(int i = 0; i < (long) pkg[1]; i++){
       str = prog(2, IP++, ""); // get char
       _str = disasm.disassemble(str); // dissasemble char
       if(!ignore)
          core0.setr(0, addr++, _str);
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
    for(int i = 0; i < pkg[0]; i++){
       string str = prog(2, IP++, ""); // get char
       long _str = disasm.disassemble(str); // dissasemble char
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
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1: " << (_str + 1)<< endl;
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         cout << core0.getr(0, _str);
    }
   }
  else if(_char == 257){ // %c r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else{
         char c = core0.getr(0, _str);
         cout << c;
      }
    }
   }
  else if(_char == 258){ // %d r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         cout << (long) core0.getr(0, _str);
    }
   }
  else if(_char == 259){ // %f r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         printf("%f",core0.getr(0, _str));
    }
   }
  else if(_char == 260){ // %x r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
        std::cout << "0x" << std::hex << (long) core0.getr(0, _str);
    }
   }
   else if(_char == 261){ // %u r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else{
         unsigned num = (long) core0.getr(0, _str);
         cout << num;
      }
    }
   }
  else if(_char == 262){ // %g r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         printf("%g",core0.getr(0, _str));
    }
   }
  else if(_char == 263){ // %e r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         printf("%e",core0.getr(0, _str));
    }
   }
  else if(_char == 264){ // %do r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         printf("%lf",core0.getr(0, _str));
    }
   }
  else if(_char == 265){ // %lg r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         printf("%lg",core0.getr(0, _str));
    }
   }
  else if(_char == 266){ // %le r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else
         printf("%le",core0.getr(0, _str));
    }
   }
  else if(_char == 267){ // %bl r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else{
         if(core0.getr(0, _str) == 1)
           cout << "true";
         else if(core0.getr(0, _str) == 0)
           cout << "false";
         else
           cout << core0.getr(0, _str);
      }
    }
   }
  else if(_char == 268){ // %s r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    long _str = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, _str) == null)
        cout << "null";
      else{
         long ref = _str + 1;
         for(int i = 0; i < core0.getr(0, _str); i++){
             c_printf(core0.getr(0, ref++));
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
  string instr;
  for(int i = 0; i < L1_ICache_length; i++){
      if(i > r.info(5))
          break;
      else {
        core0.getr(5, i);
        instr = prog_data;
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
    string str;
    long _str;
    for(int i = 0; i < pkg[0]; i++){
       str = prog(2, IP++, ""); // get char
       _str = disasm.disassemble(str); // dissasemble char
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


int ibool(long);
void loadbl(double *pkg)
{
   core0.setr(0, pkg[0], ibool( (long) pkg[1]));
}

long _char(long _ch)
{
  char c = _ch;
  long chr = c;
  return chr;
}

void loadc(double *pkg)
{
   core0.setr(0, pkg[0], _char((long) pkg[1]));
}

void _sleep(double *pkg)
{
   cout.flush();
   if(SCX < 0)
     SCX *= -1;
   if((long) pkg[0] == 0)
       sleep(SCX);
   else
      usleep(SCX * 1000); // sleep for mills
}

void dload(double *pkg)
{
   stringstream ss;
   ss << pkg[1] << "." << pkg[2];
   string dec = ss.str();
   if(atof(dec.c_str()) == 21937856.0)
      core0.setr(0, pkg[0], null);
   else
      core0.setr(0, pkg[0], (double) atof(dec.c_str()));
}

void loadf(double *pkg)
{
   stringstream ss;
   ss << pkg[1] << "." << pkg[2];
   string dec = ss.str();
   if(atof(dec.c_str()) == 21937856)
      core0.setr(0, pkg[0], null);
   else
      core0.setr(0, pkg[0], (float) atof(dec.c_str()));
}

void mov(double *pkg)
{
      switch( (long) pkg[0] )
      {
          case 21:
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
           case 37:
            I3 = pkg[1];
           break;
           case 38:
            I4 = pkg[1];
           break;
           case 39:
            I5 = pkg[1];
           break;
           case 40:
            I6 = pkg[1];
           break;
           case 41:
            I7 = pkg[1];
           break;
           case 42:
            I8 = pkg[1];
           break;
           case 43:
            I9 = pkg[1];
           break;
           case 44:
            I10 = pkg[1];
           break;
           case 45:
            I11 = pkg[1];
           break;
           case 46:
            I12 = pkg[1];
           break;
      }
}

void r_mv(double *pkg)
{
      switch( (long) pkg[0] )
      {
          case 21:
             core0.setr(0, pkg[1], EBX);
           break;
           case 22:
             core0.setr(0, pkg[1], SDX);
           break;
           case 23:
             core0.setr(0, pkg[1], BP);
           break;
           case 24:
             core0.setr(0, pkg[1], EXC);
           break;
           case 25:
             core0.setr(0, pkg[1], PS);
           break;
           case 26:
             core0.setr(0, pkg[1], LG);
           break;
           case 27:
             core0.setr(0, pkg[1], LSL);
           break;
           case 28:
                core0.setr(0, pkg[1], SFC);
           break;
           case 29:
                core0.setr(0, pkg[1], SCX);
           break;
           case 30:
                core0.setr(0, pkg[1], I1);
           break;
           case 31:
                core0.setr(0, pkg[1], I2);
           break;
           case 32:
                core0.setr(0, pkg[1], TMP);
           break;
           case 36:
                core0.setr(0, pkg[1], SCR);
           break;
           case 20:
                core0.setr(0, pkg[1], EAX);
           break;
           case 35:
                core0.setr(0, pkg[1], IP);
           break;
           case 33:
		core0.setr(0, pkg[1], AI);
   	   break;
  	   case 34:
                core0.setr(0, pkg[1], IPI);
	   break;
           case 37:
                core0.setr(0, pkg[1], I3);
           break;
           case 38:
                core0.setr(0, pkg[1], I4);
           break;
           case 39:
                core0.setr(0, pkg[1], I5);
           break;
           case 40:
                core0.setr(0, pkg[1], I6);
           break;
           case 41:
                core0.setr(0, pkg[1], I7);
           break;
           case 42:
                core0.setr(0, pkg[1], I8);
           break;
           case 43:
                core0.setr(0, pkg[1], I9);
           break;
           case 44:
                core0.setr(0, pkg[1], I10);
           break;
           case 45:
                core0.setr(0, pkg[1], I11);
           break;
           case 46:
                core0.setr(0, pkg[1], I12);
           break;
      }
}

void rmov(double *pkg)
{
     switch( (long) pkg[0] )
     {
          case 21:
               EBX = (long) reg_check_ret( pkg[1]);
           break;
           case 22:
               SDX = (long) reg_check_ret( pkg[1]);
           break;
           case 23:
               BP = (long) reg_check_ret( pkg[1]);
           break;
           case 24:
               EXC = (long) reg_check_ret( pkg[1]);
           break;
           case 26:
               LG = (long) reg_check_ret( pkg[1]);
           break;
           case 27:
              LSL =  (long) reg_check_ret( pkg[1]);
            break;
           case 28:
               SFC = (long) reg_check_ret( pkg[1]);
           break;
           case 29:
               SCX = (long) reg_check_ret( pkg[1]);
           break;
           case 30:
               I1 = (long) reg_check_ret( pkg[1]);
           break;
           case 31:
               I2 = (long) reg_check_ret( pkg[1]);
           break;
           case 32:
               TMP = (long) reg_check_ret( pkg[1]);
            break;
           case 33:
              AI = (long) reg_check_ret( pkg[1]);
           break;
           case 34:
              IPI = (long) reg_check_ret( pkg[1]);
           break;
           case 37:
               I3 = (long) reg_check_ret( pkg[1]);
           break;
           case 38:
               I4 = (long) reg_check_ret( pkg[1]);
           break;
           case 39:
               I5 = (long) reg_check_ret( pkg[1]);
           break;
           case 40:
               I6 = (long) reg_check_ret( pkg[1]);
           break;
           case 41:
               I7 = (long) reg_check_ret( pkg[1]);
           break;
           case 42:
               I8 = (long) reg_check_ret( pkg[1]);
           break;
           case 43:
               I9 = (long) reg_check_ret( pkg[1]);
           break;
           case 44:
               I10 = (long) reg_check_ret( pkg[1]);
           break;
           case 45:
               I11 = (long) reg_check_ret( pkg[1]);
           break;
           case 46:
               I12 = (long) reg_check_ret( pkg[1]);
           break;
     }
}


long iph, ipl; // ip high and low for threads
void invoke(double *pkg)
{
     switch((long) pkg[0] )
     {
       case 1: // log settings
        if(LG == 1)
          lg.On();
        else if(LG == 0)
          lg.Shutdown();

        SetPriority(LSL);
       break;
       case 3:
          switch((long) pkg[1]){
          	case 0:
          	    tSP = SDX;
          	break;
          	case 1: // start processe
          	   
          	break;
          }
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
	  core0.Interrupt(SDX);
	  SCR = 0;
       break;
       case 11: // set IP back to original pos before it was interrupted
          IP = auto_ipi;
       break;
       case 18: // assemble data
        {
          string bin = disasm.assemble(SDX);
          SDX = bin.length();
          int c = 0;
          for(long i = SCX; c < bin.length(); i++){
             core0.setr(0, i, bin.at(c));
             c++;
          }
        }
       break;
       case 19: // dissassemble data
        {
          string bin = "";
          stringstream ss1;
          for(long i = SDX; i < (SDX + SCX); i++){
             ss1 << core0.getr(0, i);
          }
          bin += "" + ss1.str();
          SDX = (long) disasm.disassemble(bin);
        }
       break;
       case 35:
        {
          core0.setr(0, SDX, prog_args.length());
          long start_addr = SDX;
          int ch;
          for(int i = 0; i < prog_args.length(); i++){
             ch = prog_args.at(i);
             core0.setr(0, start_addr + i, ch);
          }
          SCX = arg_c - 2;
        }
       break;
       case 42:
        {
          stringstream ss, ss1;
          long start_addr = SDX + 1; // the tag
          char ch;
          for(int i = 0; i < core0.getr(0, SDX); i++){
             ch = core0.getr(0, start_addr++);
             if((ch == '\n') || (ch == ' ') || (ch == '\t') || (ch == 10)){ }
             else
               ss << ch;
          }

          start_addr = SCX + 1; // the tag
          for(int i = 0; i < core0.getr(0, SCX); i++){
             ch = core0.getr(0, start_addr++);
             if((ch == '\n') || (ch == 10)){ }
             else
             ss1 << ch;
          }

          if(pkg[1] <= 2)
           lg.v(ss.str(), ss1.str());
          else if(pkg[1] == 3)
           lg.d(ss.str(), ss1.str());
          else if(pkg[1] == 4)
           lg.i(ss.str(), ss1.str());
          else if(pkg[1] == 5)
           lg.w(ss.str(), ss1.str());
          else if(pkg[1] == 6)
           lg.e(ss.str(), ss1.str());
          else
           lg.a(ss.str(), ss1.str());
        }
       break;
       case 49:
        {
          stringstream ss, ss1;
          long start_addr = SDX + 1; // the exception
          char ch;
          for(int i = 0; i < core0.getr(0, SDX); i++){
             ch = core0.getr(0, start_addr++);
             if((ch == '\n') || (ch == ' ') || (ch == '\t') || (ch == 10)){ }
             else
               ss << ch;
          }

          start_addr = SCX + 1; // the msg
          for(int i = 0; i < core0.getr(0, SCX); i++){
             ch = core0.getr(0, start_addr++);
             ss1 << ch;
          }
         RuntimeException re;
         re.introduce(ss.str(), ss1.str());
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
       case 250: // get total internal time the cpu has been running(in secs)
          core0.setr(0, SDX, core0.GetTime());
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
      if(core0.getr(3, pkg[0]) == 0)
         core0.setr(2, pkg[0], core0.getr(0, pkg[0]));
      else {
       stringstream ss;
       ss << pkg[0];
       lg.v("System","warning: ram lock err cannot lock excluded address into ram #{" + ss.str() + "}");
       EBX = 2;
      }
}

void xreg(double *pkg)
{
     if(core0.getr(3, pkg[0]) == 0)
        core0.setr(3, pkg[0], 1);
     else if(core0.getr(3, pkg[0]) == 1)
        core0.setr(3, pkg[0], 0);
}

void clx(double *pkg)
{
     for(int i = 0; i < r.info(0); i++)
        core0.setr(3, i, 0);
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
   reg_check_set( pkg[0], tibool(reg_check_ret( pkg[1]) == reg_check_ret( pkg[2])));
}

void ulock(double *pkg)
{
   if(core0.getr(3, pkg[0]) == 0)
      core0.setr(0, pkg[0], core0.getr(2, pkg[0]));
}

void push(double *pkg)
{
  RuntimeException x;
   if(!inFunc){
    inFunc = true;
    core0.setr(0, pkg[0], IP);
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
    else if(ignore && pkg[1] == 1) // skip
       inFunc = true;
    else
       IP = (long) core0.getr(0, pkg[0]);
}

void call(double *pkg)
{
    TMP = IP;
    IP = (long) core0.getr(0,  pkg[0]);
    core0.setr(0, pkg[0], TMP);
}

void swp(double *pkg)
{
     TMP = core0.getr(0, pkg[0]);
     core0.setr(0, pkg[0], core0.getr(0, pkg[1]));
     core0.setr(0, pkg[1], TMP);
}

void loop(double *pkg)
{
     core0.setr(0, pkg[1], pkg[2]);
     core0.setr(0, pkg[0], IP);
     waiting = true;
}

void wloop(double *pkg)
{
    if(core0.getr(0, pkg[0]) == 1)
       core0.setr(0, pkg[1], IP);
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
  else if(!ignore && (core0.getr(0, pkg[0]) == 1)) // loop again
       IP = core0.getr(0, pkg[1]);
}

void rloop(double *pkg)
{
    core0.setr(0, pkg[0], IP);
    core0.setr(0, pkg[1], core0.getr(0, pkg[2]));
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
      core0.setr(0, pkg[1], (core0.getr(0, pkg[1]) - 1));
    if(core0.getr(0, pkg[1]) <= 0)
      waiting = false;
   else {
      IP = core0.getr(0, pkg[0]);
   }
  }
}

void _do(double *pkg)
{
   if(reg_check_ret( pkg[0]) == 1){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ilt(double *pkg)
{
   if(reg_check_ret(pkg[0]) < reg_check_ret( pkg[1])){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void igt(double *pkg)
{
   if(reg_check_ret( pkg[0]) > reg_check_ret( pkg[1])){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ile(double *pkg)
{
   if(reg_check_ret( pkg[0]) <= reg_check_ret( pkg[1])){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ige(double *pkg)
{
   if(reg_check_ret( pkg[0]) >= reg_check_ret( pkg[1])){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ndo(double *pkg)
{
   if(reg_check_ret( pkg[0]) == 0){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void inlt(double *pkg)
{
   if(!(reg_check_ret( pkg[0]) < reg_check_ret( pkg[1]))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ingt(double *pkg)
{
   if(!(reg_check_ret( pkg[0]) > reg_check_ret( pkg[1]))){}
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
            core0.setr(0, pkg[0], (int) core0.getr(0, pkg[0]));
        break;
        case 1: // int
            core0.setr(0, pkg[0], (long) core0.getr(0, pkg[0]));
        break;
        case 2: //  float
            core0.setr(0, pkg[0], (float) core0.getr(0, pkg[0]));
        break;
        case 3: // double
	    core0.setr(0, pkg[0], (double) core0.getr(0, pkg[0]));
        break;
        case 4: // char
         {
            char ch = core0.getr(0, pkg[0]);
            int c = ch;
            core0.setr(0, pkg[0], c);
         }
        break;
        case 5: // bool
            core0.setr(0, pkg[0], ibool(core0.getr(0, pkg[0])));
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
   if(!(reg_check_ret( pkg[0]) <= reg_check_ret( pkg[1]))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void inge(double *pkg)
{
   if(!(reg_check_ret( pkg[0]) >= reg_check_ret( pkg[1]))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void neg(double *pkg){
    RuntimeException re;
    if(I1 == INT || I1 == DOUBLE
           || I1 == SHORT || I1 == FLOAT)
      reg_check_set( pkg[0], (reg_check_ret( pkg[0]) * -1));
    else if(I1 == BOOL){
        if(reg_check_ret( pkg[0]) == 0)
           reg_check_set( pkg[0], 1);
        else if(reg_check_ret( pkg[0]) == 1)
           reg_check_set( pkg[0], 0);
    }
    else
       re.introduce("UnsatisfiedTypeException","must specify correct type to be inverted");
}
