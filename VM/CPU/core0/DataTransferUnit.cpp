/*
* Copyright 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/
#include "core0.h"
#include "system_color.h"
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
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

bool inFunc = false;
extern string prog_args;
extern int arg_c;
extern short DEBUG_STATE;

void loadi()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(p1 == 21937856)
     core0.setr(0, p0, null);
   else
     core0.setr(0, p0, (long) p1);
}

void rload()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   TMP = core0.getr(0, p1);
   double reg = core0.getr(0, TMP);
   core0.setr(0, p0, reg);
}

void r_load()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   TMP = core0.getr(0, p0);
   core0.setr(0, TMP, core0.getr(0, p1));
}

void cp()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   core0.setr(0, p0, core0.getr(0, p1));
}



void array() // array numbers sdx int
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   if(p1 == 0){
      SCR = -5;
      return;
   }   
   core0.setr(0, p0, (int) reg_check_ret(p1)); // check type
   if(p2 == INT || p2 == BOOL || p2 == CHAR || p2 == FLOAT || p2 == DOUBLE || p2 == SHORT) { }
   else {
   	RuntimeException re;
   	stringstream ss;
   	ss << p2;
   	re.introduce("ArrayTypeNotFoundException", "the specified array type: " + ss.str() + " was not found");
   }
   core0.setr(0, (p0 + 1), p2);
   
   TMP = p0 + 2;
   for(int i = 0; i < p1; i++)
       core0.setr(0, TMP++, 0);
}

int tibool( bool val );
long _char(long);
void aload() // aload numbers sdx i4
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   long length = (long) core0.getr(0, p0);
   long index = (long) reg_check_ret(p1);
   if(index >= length){
   	RuntimeException re;
   	stringstream ss, ss1;
   	ss << index;
   	ss1 << length;
   	re.introduce("ArrayLengthOutOfBoundsException", "index >= length;  could not access array at index[" + ss.str() + "] length is: " + ss1.str());
   }
   
   long addr = p0 + 2;
   addr += index;
   TMP  = (long) core0.getr(0, p0 + 1);

   if(TMP == INT)
       core0.setr(0, addr, (long) reg_check_ret(p2));
   else if(TMP == SHORT)
       core0.setr(0, addr, (int) reg_check_ret(p2));
   else if(TMP == DOUBLE)
       core0.setr(0, addr, (double) reg_check_ret(p2));
   else if(TMP == FLOAT)
       core0.setr(0, addr, (float) reg_check_ret(p2));
   else if(TMP == BOOL)
       core0.setr(0, addr, tibool(reg_check_ret(p2)) );
   else if(TMP == CHAR)
       core0.setr(0, addr,  _char((long) reg_check_ret(p2)));
   else {
        RuntimeException re;
        stringstream ss;
        ss << TMP;
        re.introduce("ArrayTypeNotFoundException", "the specified array type: " + ss.str() + " was not found");
   }
}

void aaload() // aaload numbers 0 num1
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   long length = (long) core0.getr(0, p0);
   long index = (long) reg_check_ret(p1);
   if(index >= length){
   	RuntimeException re;
   	stringstream ss, ss1;
   	ss << index;
   	ss1 << length;
   	re.introduce("ArrayLengthOutOfBoundsException", "index >= length;  could not access array at index[" + ss.str() + "] length is: " + ss1.str());
   }
   
   TMP = p0 + 2;
   TMP += index;
   reg_check_set(p2, core0.getr(0, TMP));
}

extern void sfinterrupt();
void swi()
{
   IP += 3;
   long ip = IP;
   long run_for = SDX;
   IP = SCX;
   for(long i= 0; i < run_for; i++)
        sfinterrupt();

   IP = ip;
}

int tibool(bool val);
void strcp()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   stringstream ss, ss1;
   TMP = p1 + 1; // string 1
   char ch;
   for(int i = 0; i < core0.getr(0, p1); i++){
        ch = core0.getr(0, TMP++);
        ss << ch;
   }

   TMP = p2 + 1; // string 2
   for(int i = 0; i < core0.getr(0, p2); i++){
         ch = core0.getr(0, TMP++);
         ss1 << ch;
   }
    reg_check_set( p0, tibool(ss.str() == ss1.str()));
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

void strcpi()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   stringstream ss, ss1;
   TMP = p1 + 1; // string 1
   char ch;
   for(int i = 0; i < core0.getr(0, p1); i++){
        ch = core0.getr(0, TMP++);
        ss << ch;
   }

   TMP = p2 + 1; // string 2
   for(int i = 0; i < core0.getr(0, p2); i++){
         ch = core0.getr(0, TMP++);
         ss1 << ch;
   }

    reg_check_set( p0, tibool(iequals(ss.str(),ss1.str())));
}

void e2str()
{
   IP += 3;
   stringstream ss;
   ss << core0.getr(0, SDX);
   string num = ss.str();
   TMP = SCX + 1; // the str
   char ch;
   for(int i = 0; i < num.length(); i++){
        core0.setr(0, TMP++, num.at(i));
   }
     core0.setr(0, SCX, num.length());
}

void sload()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(p1 == 21937856)
     core0.setr(0, p0, null);
   else
     core0.setr(0, p0, (int) p1);
}

void _throw()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   stringstream ss, ss1;
   TMP = p0 + 1; // the exception
     char ch;
     for(int i = 0; i < core0.getr(0, p0); i++){
        ch = core0.getr(0, TMP++);
        if((ch == '\n') || (ch == ' ') || (ch == '\t') || (ch == 10)){ }
        else
          ss << ch;
     }

     TMP = p1 + 1; // the msg
     for(int i = 0; i < core0.getr(0, p1); i++){
         ch = core0.getr(0, TMP++);
         ss1 << ch;
     }

      RuntimeException re;
      re.introduce(ss.str(), ss1.str());
}

void adr()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   reg_check_set( p0, (long) p1);
}

void ct_int()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   char a = core0.getr(0, p1);
   if(a == '0')
    core0.setr(0, p0, 0);
   else if (a == '1')
    core0.setr(0, p0, 1);
   else if (a == '2')
    core0.setr(0, p0, 2);
   else if (a == '3')
    core0.setr(0, p0, 3);
   else if (a == '4')
    core0.setr(0, p0, 4);
   else if (a == '5')
    core0.setr(0, p0, 5);
   else if (a == '6')
    core0.setr(0, p0, 6);
   else if (a == '7')
    core0.setr(0, p0, 7);
   else if (a == '8')
    core0.setr(0, p0, 8);
   else if (a == '9')
    core0.setr(0, p0, 9);
   else
    core0.setr(0, p0, 0);
}

void anum()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   stringstream ss;
   ss << core0.getr(0, p0) << core0.getr(0, p1);
   string num = ss.str();

   if(SFC == SHORT || SFC == INT)
     core0.setr(0, p0, atoi(num.c_str()));
   else if(SFC == DOUBLE || SFC == FLOAT)
     core0.setr(0, p0, atof(num.c_str()));
   else {
      EBX = 2;
      lg.w("System", "warning: canot assignn decimal value to not integer and or float data types");
   }
}

void rln()//  length, start addr, excape  char, 
{
   
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   TMP = (long) p0 + 1;
   long max = core0.getr(0, p0);
   if(p1 == 10){ // excape char = \n
     string input = "";
     getline(cin, input);
     char a;
     int chr;
     for(int i = 0; i < input.length(); i++){
       if(i > max)
         break;
          a = input.at(i);
          chr = (int) a;
          core0.setr(0, TMP++, chr);
     }
       TMP = input.length();
       core0.setr(0, p0, TMP);
   }
   else {
     string input = "", tmp = "";
     Ram ram;
     char a = p1;
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
          core0.setr(0, TMP++, chr);
     }
       TMP = input.length();
       core0.setr(0, p0, TMP);
   }
}

void _string() // string @434 32 'this is the string'
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
 if(p1 <= 0){}
 else if(p1 == 1){
   core0.setr(0, p0, 1);
   core0.setr(0, p0 + 1, p2);
 }
 else if(p1 >= 2) {
    IP--;
    TMP = p0 + 1;
    if(!ignore)
        core0.setr(0, p0, p1);
    string str;
    long _str;
    for(int i = 0; i < (long) p1; i++){
       str = prog(2, IP++, ""); // get char
       _str = disasm.disassemble(str); // dissasemble char
       if(!ignore)
          core0.setr(0, TMP++, _str);
   }
 }
 else{
  cout << "CPU string_length_logic err something went wrong while determing the length of the string to print" << endl;
  EBX = 1;
  p_exit();
 }
}

char _ostream;
void c_print(double _char)
{
  if(ignore)
   return;
    if(_char == 269)
         cout << std::flush;
    else{
      _ostream = _char;
      cout << _ostream;
    }
}

void _print()
{ 
 
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
 if(p0 <= 0){
    IP--;
    IP--;
 }
 else if(p0 == 1){
   IP--;
   c_print(p1);
 }
 else if(p0 == 2){
   c_print(p1);
   c_print(p2);
 }
 else if(p0 > 2) {
    IP--;
    IP--;
    string str;
    for(int i = 0; i < p0; i++){
       str = prog(2, IP++, ""); // get char
       TMP = disasm.disassemble(str); // dissasemble char
       c_print(TMP); // print char
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
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1: " << (_str + 1)<< endl;
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         cout << core0.getr(0, TMP);
    }
   }
  else if(_char == 257){ // %c r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else{
         char c = core0.getr(0, TMP);
         cout << c;
      }
    }
   }
  else if(_char == 258){ // %d r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         cout << (long) core0.getr(0, TMP);
    }
   }
  else if(_char == 259){ // %f r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         printf("%f",core0.getr(0, TMP));
    }
   }
  else if(_char == 260){ // %x r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
        std::cout << "0x" << std::hex << (long) core0.getr(0, TMP);
    }
   }
   else if(_char == 261){ // %u r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else{
         unsigned num = (long) core0.getr(0, TMP);
         cout << num;
      }
    }
   }
  else if(_char == 262){ // %g r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         printf("%g",core0.getr(0, TMP));
    }
   }
  else if(_char == 263){ // %e r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         printf("%e",core0.getr(0, TMP));
    }
   }
  else if(_char == 264){ // %do r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         printf("%lf",core0.getr(0, TMP));
    }
   }
  else if(_char == 265){ // %lg r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         printf("%lg",core0.getr(0, TMP));
    }
   }
  else if(_char == 266){ // %le r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else
         printf("%le",core0.getr(0, TMP));
    }
   }
  else if(_char == 267){ // %bl r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else{
         if(core0.getr(0, TMP) == 1)
           cout << "true";
         else if(core0.getr(0, TMP) == 0)
           cout << "false";
         else
           cout << core0.getr(0, TMP);
      }
    }
   }
  else if(_char == 268){ // %s r#
    reg = true;
    string str = prog(2, IP++, ""); // get char
    TMP = disasm.disassemble(str); // dissasemble char
    //cout << "pinting from reg " << _str  << " -1: " << (_str - 1) << " +1$
    if(!ignore){
      if(core0.getr(0, TMP) == null)
        cout << "null";
      else{
         long ref = TMP + 1;
         stringstream ss;
         string message = "";
         for(int i = 0; i < core0.getr(0, TMP); i++){
             ss << (char) core0.getr(0, ref++) << "";
         }
         message = ss.str();
         cout << message;
      }
    }
   }
  else if(_char == 269){ // /&
    if(!ignore)
        cout << std::flush;
  }
  else if(_char == 270){ // %col shade
    reg = true;
    string str = prog(2, IP++, ""); // get color shade
    TMP = disasm.disassemble(str); // dissasemble char
    SystemColor color;
    if(color.isColor(core0.getr(0, TMP), SDX) && !ignore)
      color.changeColor();
   }
  else if((!ignore)) {
    char c = _char;
    cout << c;
  }
}

extern string prog_data;
void c_update()
{
  IP += 3;
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

void _printf()
{
 
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
 if(p0 <= 0){
   IP--;
   IP--;
 }
 else if(p0 >= 1) {
    IP--;
    IP--;
    string str;
    for(int i = 0; i < p0; i++){
       str = prog(2, IP++, ""); // get char
       TMP = disasm.disassemble(str); // dissasemble char
       c_printf(TMP); // print char
   }
   reg = false;
 }
 else{
  cout << "CPU print_length_logic err something went wrong while determing the length of the string to print" << endl;
  EBX = 1;
  p_exit();
 }
}


int ibool(long);
void loadbl()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   core0.setr(0, p0, ibool( (long) p1));
}

long _char(long _ch)
{
  char c = _ch;
  long chr = c;
  return chr;
}

void loadc()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   core0.setr(0, p0, _char((long) p1));
}

void _sleep()
{
   
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   cout.flush();
   if(SDX < 0)
     SDX *= -1;
   if((long) p0 == 0)
       sleep(SDX);
   else
      usleep(SDX); // sleep for microseconds
}

void dload()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   stringstream ss;
   ss << p1 << "." << p2;
   string dec = ss.str();
   if(atof(dec.c_str()) == 21937856.0)
      core0.setr(0, p0, null);
   else
      core0.setr(0, p0, (double) atof(dec.c_str()));
}

void loadf()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   stringstream ss;
   ss << p1 << "." << p2;
   string dec = ss.str();
   if(atof(dec.c_str()) == 21937856)
      core0.setr(0, p0, null);
   else
      core0.setr(0, p0, (float) atof(dec.c_str()));
}

void mov()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
      switch( (long) p0 )
      {
          case 21:
	    EBX = p1;
           break;
  	   case 22:
	    SDX = p1;
           break;
	   case 23:
	    BP = p1;
           break;
 	   case 24:
	    EXC = p1;
           break;
	   case 25:
	    PS = 0;
           break;
	   case 26:
	    LG = p1;
           break;
  	   case 27:
	    LSL = p1;
           break;
           case 28:
	    SFC = p1;
           break;
           case 29:
            SCX = p1;
           break;
           case 30:
            I1 = p1;
           break;
           case 31:
            I2 = p1;
           break;
           case 32:
            TMP = p1;
           break;
           case 33:
	    AI = p1;
           break;
           case 34:
            IPI = p1;
	   break;
           case 37:
            I3 = p1;
           break;
           case 38:
            I4 = p1;
           break;
           case 39:
            I5 = p1;
           break;
           case 40:
            I6 = p1;
           break;
           case 41:
            I7 = p1;
           break;
           case 42:
            I8 = p1;
           break;
           case 43:
            I9 = p1;
           break;
           case 44:
            I10 = p1;
           break;
           case 45:
            I11 = p1;
           break;
           case 46:
            I12 = p1;
           break;
      }
}

void r_mv()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
      switch( (long) p0 )
      {
          case 21:
             core0.setr(0, p1, EBX);
           break;
           case 22:
             core0.setr(0, p1, SDX);
           break;
           case 23:
             core0.setr(0, p1, BP);
           break;
           case 24:
             core0.setr(0, p1, EXC);
           break;
           case 25:
             core0.setr(0, p1, PS);
           break;
           case 26:
             core0.setr(0, p1, LG);
           break;
           case 27:
             core0.setr(0, p1, LSL);
           break;
           case 28:
                core0.setr(0, p1, SFC);
           break;
           case 29:
                core0.setr(0, p1, SCX);
           break;
           case 30:
                core0.setr(0, p1, I1);
           break;
           case 31:
                core0.setr(0, p1, I2);
           break;
           case 32:
                core0.setr(0, p1, TMP);
           break;
           case 36:
                core0.setr(0, p1, SCR);
           break;
           case 20:
                core0.setr(0, p1, EAX);
           break;
           case 35:
                core0.setr(0, p1, IP);
           break;
           case 33:
		core0.setr(0, p1, AI);
   	   break;
  	   case 34:
                core0.setr(0, p1, IPI);
	   break;
           case 37:
                core0.setr(0, p1, I3);
           break;
           case 38:
                core0.setr(0, p1, I4);
           break;
           case 39:
                core0.setr(0, p1, I5);
           break;
           case 40:
                core0.setr(0, p1, I6);
           break;
           case 41:
                core0.setr(0, p1, I7);
           break;
           case 42:
                core0.setr(0, p1, I8);
           break;
           case 43:
                core0.setr(0, p1, I9);
           break;
           case 44:
                core0.setr(0, p1, I10);
           break;
           case 45:
                core0.setr(0, p1, I11);
           break;
           case 46:
                core0.setr(0, p1, I12);
           break;
      }
}

void rmov()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
     switch( (long) p0 )
     {
          case 21:
               EBX = (long) reg_check_ret( p1);
           break;
           case 22:
               SDX = (long) reg_check_ret( p1);
           break;
           case 23:
               BP = (long) reg_check_ret( p1);
           break;
           case 24:
               EXC = (long) reg_check_ret( p1);
           break;
           case 26:
               LG = (long) reg_check_ret( p1);
           break;
           case 27:
              LSL =  (long) reg_check_ret( p1);
            break;
           case 28:
               SFC = (long) reg_check_ret( p1);
           break;
           case 29:
               SCX = (long) reg_check_ret( p1);
           break;
           case 30:
               I1 = (long) reg_check_ret( p1);
           break;
           case 31:
               I2 = (long) reg_check_ret( p1);
           break;
           case 32:
               TMP = (long) reg_check_ret( p1);
            break;
           case 33:
              AI = (long) reg_check_ret( p1);
           break;
           case 34:
              IPI = (long) reg_check_ret( p1);
           break;
           case 37:
               I3 = (long) reg_check_ret( p1);
           break;
           case 38:
               I4 = (long) reg_check_ret( p1);
           break;
           case 39:
               I5 = (long) reg_check_ret( p1);
           break;
           case 40:
               I6 = (long) reg_check_ret( p1);
           break;
           case 41:
               I7 = (long) reg_check_ret( p1);
           break;
           case 42:
               I8 = (long) reg_check_ret( p1);
           break;
           case 43:
               I9 = (long) reg_check_ret( p1);
           break;
           case 44:
               I10 = (long) reg_check_ret( p1);
           break;
           case 45:
               I11 = (long) reg_check_ret( p1);
           break;
           case 46:
               I12 = (long) reg_check_ret( p1);
           break;
     }
}


extern long SIZE;
extern int alloc(bool free, long size);
extern void ucache();
void invoke()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
     switch((long) p0 )
     {
       case 0: // os system call
        {
          stringstream ss;
          long TMP = SDX + 1; // the command
          char ch;
          for(int i = 0; i < core0.getr(0, SDX); i++){
             ch = core0.getr(0, TMP++);
             if((ch == '\n') || (ch == ' ') || (ch == '\t') || (ch == 10)){ }
             else
               ss << ch;
          }
          string command = "" + ss.str();;
          system(command.c_str());
        }
       break;
       case 1: // log settings
        if(LG == 1)
          lg.On();
        else if(LG == 0)
          lg.Shutdown();

        SetPriority(LSL);
       break;
       case 2:
         Ram rm;
         SCR = rm.info(p1);
       break;
       case 3: // push code to Ram
        {
         TMP = SDX;
         string bin = "";
         stringstream ss1;
         for(long i = SDX + 1; i < (SDX + core0.getr(0, SDX)); i++){
            ss1 << core0.getr(0, i);
         }

         bin += "" + ss1.str();
         for(int i = 0; i < bin.length(); i++)
          {
               if(bin.at(i) != '1' || bin.at(i) != '0')
               {
                   SCR = -1;
                   return;
               }
          } // verify is binary

         cout << "setting to addr " << TMP << endl; 
         prog(1, TMP, bin);
        }
       break;
       case 4: // get code from ram
        {
         string bin = prog(2, SDX, "");
         SDX = bin.length();
          TMP = 0;
          for(long i = SCX; TMP < bin.length(); i++){
             core0.setr(0, i, bin.at(TMP));
             TMP++;
          }
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
              SCR = GPIODirection(SDX, SCX);
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
       break;
       case 11: // set IP back to original pos before it was interrupted
          IP = auto_ipi;
       break;
      case 12:
        {

          // Set terminal to raw mode
          system("stty raw");

          // Wait for single character
          if(SFC != CHAR){ // do not print char to screen
            SDX = (int) getchar();
            cout << "\b \b" << std::flush;
          }
          else
            SDX = (int) getchar();
          // Reset terminal to normal "cooked" mode
          system("stty cooked");
        }
      break;
       case 18: // assemble data
        {
          string bin = disasm.assemble(SDX);
          SDX = bin.length();
          TMP= 0;
          for(long i = SCX; TMP < bin.length(); i++){
             core0.setr(0, i, bin.at(TMP));
             TMP++;
          }
        }
       break;
       case 19: // dissassemble data
        {
          string bin = "";
          stringstream ss1; // sdx - start addr
                           // scx - length
          for(long i = SDX; i < (SDX + SCX); i++){
             ss1 << core0.getr(0, i);
          }

          bin += "" + ss1.str();
          for(int i = 0; i < bin.length(); i++)
          {
               if(bin.at(i) != '1' || bin.at(i) != '0')
               {
                   SCR = -1;
                   return;
               }
          } // verify is binary

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
       case 40:
         ucache();
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

          if(p1 <= 2)
           lg.v(ss.str(), ss1.str());
          else if(p1 == 3)
           lg.d(ss.str(), ss1.str());
          else if(p1 == 4)
           lg.i(ss.str(), ss1.str());
          else if(p1 == 5)
           lg.w(ss.str(), ss1.str());
          else if(p1 == 6)
           lg.e(ss.str(), ss1.str());
          else
           lg.a(ss.str(), ss1.str());
        }
       break;
       case 50: // read to a file
        {
          data[0] = p1;
          SCR = io.Read(1,data); // read to a file
        }
       break;
       case 51: // write to a file
        {
          data[0] = p1;
          SCR = io.Write(1,data); // write to a file
        }
       break;
       case 100: // cursor maniputation
        {
          stringstream ss;
          string cursorpos = "";
          if(SFC == 0){
             ss << "\033[" << SDX << ";" << SCX << "f";
             cursorpos = ss.str();
             cout << cursorpos;
          }
          else if(SFC == 1){ // move up N lines
             ss << "\033[" << SDX << "A";
             cursorpos = ss.str();
             cout << cursorpos;
          }
           else if(SFC == 2){ // move down N lines
             ss << "\033[" << SDX << "B";
             cursorpos = ss.str();
             cout << cursorpos;
          }
           else if(SFC == 3){ // move forward N  colums
             ss << "\033[" << SDX << "C";
             cursorpos = ss.str();
             cout << cursorpos;
          }
           else if(SFC == 4){ // move backward N  colums
             ss << "\033[" << SDX << "D";
             cursorpos = ss.str();
             cout << cursorpos;
          }
           else if(SFC == 5){ // move to (0,0)
             cursorpos = "\033[2J";
             cout << cursorpos;
          }
           else if(SFC == 6){ // erase to end of line
             cursorpos = "\033[K";
             cout << cursorpos;
          }
           else if(SFC == 7){ // save cursor pos
             cursorpos = "\033[s";
             cout << cursorpos;
          }
           else if(SFC == 8){ // restore cursor pos
             cursorpos = "\033[u";
             cout << cursorpos;
          }
        }
       break;
       case 128:
          SCR = alloc(tibool(SDX), SCX);
       break;
       case 132:
          SystemColor color;
          SCR = color.getSystemColorInfo((int) SDX);
       break;
       case 250: // get total internal time the cpu has been running(in secs | nanosecs)
        {
          switch( SFC ) {
            case 0:
              core0.setr(0, SDX, core0.GetTime());
            break;
            case 1:
              core0.setr(0, SDX, core0.Get_UTime());
            break;
            case 2:
              core0.resetTime();
            break;
            case 3:
              core0.reset_UTime();
            break;
          }
        }
       break;
       default:
       stringstream ss;
       ss << p0;
       RuntimeException re;
       re.introduce("IllegalSystemCallExcpetion", "code is not a system call [" + ss.str() + "]");
       break;
     }
}

Ram r;
void lock()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
      if(core0.getr(3, p0) == 0)
         core0.setr(2, p0, core0.getr(0, p0));
      else {
       stringstream ss;
       ss << p0;
       lg.v("System","warning: ram lock err cannot lock excluded address into ram #{" + ss.str() + "}");
       EBX = 2;
      }
}

void xreg()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
     if(core0.getr(3, p0) == 0)
        core0.setr(3, p0, 1);
     else if(core0.getr(3, p0) == 1)
        core0.setr(3, p0, 0);
}

void clx()
{
    IP += 3;
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

void same()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   reg_check_set( p0, tibool(reg_check_ret( p1) == reg_check_ret( p2)));
}

void ulock()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   if(core0.getr(3, p0) == 0)
      core0.setr(0, p0, core0.getr(2, p0));
}

void push()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
  RuntimeException x;
   if(!inFunc){
    inFunc = true;
    core0.setr(0, p0, IP);
    ignore = true;
   }
   else
      x.introduce("FunctionCallException", "cannot initalize a function inside another function!");
}

void _return()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
    inFunc = false;
    RuntimeException re;
    if(ignore && p1 == 0)
       ignore = false;
    else if(ignore && p1 == 1) // skip
       inFunc = true;
    else {
       IP = (long) core0.getr(0, p0);
       core0.setr(0, p0, core0.getr(0, p0 + 1));
       if(DEBUG_STATE == 0x54)
       {
           debugging = true;
       }
    }
}

void call()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
    in_func = true;
    TMP = IP;
    IP = (long) core0.getr(0,  p0);
    core0.setr(0, p0, TMP);
    core0.setr(0, p0 + 1, IP);
    inFunc = true;
}

void swp()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
     TMP = core0.getr(0, p0);
     core0.setr(0, p0, core0.getr(0, p1));
     core0.setr(0, p1, TMP);
}

void loop()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
     in_loop = true;
     core0.setr(0, p1, p2);
     core0.setr(0, p0, IP);
     waiting = true;
}

void wloop()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
    if(core0.getr(0, p0) == 1)
       core0.setr(0, p1, IP);
    else {
       pass = true;  // do not run the contents in the loop
       ignore = true;
    }
}

void endwl()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
  if(pass){
     ignore = false;
     pass = false;
  }
  else if(!ignore && (core0.getr(0, p0) == 1)){ // loop again
       IP = core0.getr(0, p1);
       if(DEBUG_STATE == 0x55)
       {
           debugging = true;
       }
   }
}

void rloop()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
    core0.setr(0, p0, IP);
    core0.setr(0, p1, core0.getr(0, p2));
    waiting = true;
}

void end() // for do
{
  IP += 3;
  if((passed_if > 0) && if_ignore){
      passed_if--;
      return;
  }
  if(if_ignore){
      if_ignore = false;
      ignore = false;
  }
}

void endl()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(waiting){
      core0.setr(0, p1, (core0.getr(0, p1) - 1));
    if(core0.getr(0, p1) <= 0){
      waiting = false;
      if(DEBUG_STATE == 0x55)
      {
           debugging = true;
      }
    }
    else {
      IP = core0.getr(0, p0);
   }
  }
}

void _do()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   if(reg_check_ret( p0) == 1){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ilt()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(reg_check_ret(p0) < reg_check_ret( p1)){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void igt()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(reg_check_ret( p0) > reg_check_ret( p1)){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ile()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(reg_check_ret( p0) <= reg_check_ret( p1)){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ige()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(reg_check_ret( p0) >= reg_check_ret( p1)){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ndo()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   if(reg_check_ret( p0) == 0){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void inlt()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(!(reg_check_ret( p0) < reg_check_ret( p1))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void ingt()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(!(reg_check_ret( p0) > reg_check_ret( p1))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void t_cast()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
     RuntimeException re;
     switch( (long) p1 ){
        case 0: // short
            core0.setr(0, p0, (int) core0.getr(0, p0));
        break;
        case 1: // int
            core0.setr(0, p0, (long) core0.getr(0, p0));
        break;
        case 2: //  float
            core0.setr(0, p0, (float) core0.getr(0, p0));
        break;
        case 3: // double
	    core0.setr(0, p0, (double) core0.getr(0, p0));
        break;
        case 4: // char
         {
            char ch = core0.getr(0, p0);
            int c = ch;
            core0.setr(0, p0, c);
         }
        break;
        case 5: // bool
            core0.setr(0, p0, ibool(core0.getr(0, p0)));
        break;
        default: // err
        stringstream ss;
        ss << "the specified cast value [" << p1 << "] is not a valid arg[double(3),float(2),int(1),short(0)]";
        re.introduce("UnknownCastException", ss.str());
         break;
    }
}

void inle()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(!(reg_check_ret( p0) <= reg_check_ret( p1))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void inge()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   if(!(reg_check_ret( p0) >= reg_check_ret( p1))){}
   else {
     if_ignore = true;
     ignore = true;
   }
}

void neg(){

   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
    RuntimeException re;
    if(SFC == INT || SFC == DOUBLE
           || SFC == SHORT || SFC == FLOAT)
      reg_check_set( p0, (reg_check_ret( p0) * -1));
    else if(SFC == BOOL){
        if(reg_check_ret( p0) == 0)
           reg_check_set( p0, 1);
        else if(reg_check_ret( p0) == 1)
           reg_check_set( p0, 0);
    }
    else
       re.introduce("UnsatisfiedTypeException","must specify correct type to be inverted");
}
