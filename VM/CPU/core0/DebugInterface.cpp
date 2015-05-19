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
#include <iostream>
#include <string>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include "datatrans.h"
#include "core0.h"
#include "../../Ram/ram.h"
using namespace std;

short DEBUG_STATE = 0x00000;
bool has_started = false;
string command, instr;
long addrr;
extern bool inFunc;

void debug();
void debug_help();
void listen();
void update(string);

/*
* DEBUG INTERFACE
* Scorpion provides a simple debug
* interface that allows you to debug your
* scorpion programs. The debug interface will become
* more complex as time passes.
*/
void debugger(long addr, string instruction)
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
     debugger(addrr, instr);
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
           debugger(addrr, instr);
        }
   }
   else if(command == "fn" || command == "fource_nxt"){
      debugging = false;
      DEBUG_STATE = 0x44;
   }
   else
   {
      cout << "Error: " << command << " is not a debug command.\nUse ls or list for help." << endl;
      debugger(addrr,instr);
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
  cout << "fn(fource_nxt) fource jump to next occurance of a reaccurring loop or function" << endl;
  cout << "?              print what is about to be executed" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  debugger(addrr,instr);
}

void debug()
{
   cout << "{Debug Mode}" << endl;
   cout << "\n";
   has_started = true;
}

