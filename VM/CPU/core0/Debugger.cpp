#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include "datatrans.h"
#include "core0.h"
#include "../../Ram/ram.h"
using namespace std;

short DEBUG_STATE;
bool has_started = false;
string command, instr;
long addrr, skip;
extern bool inFunc;
void debug();
void debug_help();
void listen();
void update(string);

double *d;
/*
* DEBUG CONSOLE COMMANDS
* {Debug Mode}
*
* >  what
* Debug Commands
* ---------------------------------------------------
* ls(list)   print debugger commands
* n(next)   go to next line of execution
* wh(where) print a trace to where we are in executing the file
* p(prev)   go back to the previously line of execution
* so(step out) setep out into the next line of execution that is not reaccurring
* ?         what are we about to execute
*/
void debugger(long addr, string instruction, double *data)
{
    if(!has_started)
     debug();
    addrr = addr;
    instr = instruction;
    listen();
}

extern string i2;
extern string i3;
extern string i4;

void listen()
{
   cout << "\n>>>    ";
   cin >> command;
   if(command == "ls" || command == "list")
     debug_help();
   else if(command == "?"){
     stringstream ss;
     ss << "[" << disasm.disassemble(i2) << ", " <<  disasm.disassemble(i3) << ", " << disasm.disassemble(i4) << "]";
     string args = ss.str();
     printf(".addr: %08X    %s %s", addrr, instr.c_str(), args.c_str());
     debugger(addrr, instr, d);
   }
   else if(command == "n" || command == "next")
   {

   }
   else if(command == "cont" || command == "continue")
   {
      DEBUG_STATE = 0x43;
      debugging = false;
   }
   else if(command == "so" || command == "step_out"){

        debugging = false;
        if((inFunc && !waiting))
          DEBUG_STATE = 0x54;
        else if(waiting)
          DEBUG_STATE = 0x55;
        else{
           debugging = true;
           debugger(addrr, instr, d);
        }
   }
   else if(command == "si" || command == "step_in"){
      debugging = false;
      DEBUG_STATE = 0x44;
   }
   else
   {
      cout << "Error: " << command << " is not a debug command.\nUse ls or list for help." << endl;
      debugger(addrr,instr, d);
   }
}

void debug_help()
{
  cout << "\nDebug Commands" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "ls(list)       list debugger commands" << endl;
  cout << "n(next)        go to next line of execution" << endl;
  cout << "cont(continue) continue until a breakpoint is reached" << endl;
  cout << "so(step_out)   step out of a reaccurring loop or function" << endl;
  cout << "si(step_in)    step into the next line of execution that is reaccurring" << endl;
  cout << "?              print what is about to be executed" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  debugger(addrr,instr, d);
}

#define nullptr ((void *)0)
void debug()
{
   cout << "{Debug Mode}" << endl;
   cout << "\n";
   has_started = true;
}

