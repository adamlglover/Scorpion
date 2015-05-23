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
#include <ctype.h>
#include "datatrans.h"
#include "core0.h"
#include "../../Ram/ram.h"
#include "../../program.h"
using namespace std;

short DEBUG_STATE = 0x00000;
bool has_started = false;
string command = "", instr;
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

void getinput();

void listen()
{
   cout << "\n>>>    ";
   command = "";
   getinput();

   if(command == "ls" || command == "list")
     debug_help();
   else if(command == "?"){
     stringstream ss;
     ss << "[" << disasm.disassemble(i2) << ", " <<  disasm.disassemble(i3) << ", " << disasm.disassemble(i4) << "]";
     string args = ss.str();
     printf(".addr: 0x%08X    %s %s", addrr, instr.c_str(), args.c_str());
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
   else if(command == "so" || command == "step out"){

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
   else if(command == "fn" || command == "force next"){
      debugging = false;
      DEBUG_STATE = 0x44;
   }
   else
   {
      cout << "Error: " << command << " is not a debug command.\nUse ls or list for help." << endl;
      debugger(addrr,instr);
   }
}

char c;
int oc_stream = 0;
void s_char()
{
  // Set terminal to raw mode
  system("stty raw");

  // Wait for single character
  c = getchar();

   // Reset terminal to normal "cooked" mode
   system("stty cooked");
  oc_stream++;
}

void o_stream(string out)
{
   oc_stream += out.length() - 1;
   cout << out;
}

void flush()
{
  if(!(oc_stream <= 0)){
    cout << "\r";
    for(int i = 0; i < oc_stream + 7; i++)
       cout << "   ";
    cout << "\r>>>    ";
  }
}

/*int s_int(string data)
{
  int value = 0;
  for(int i = 0; i < c.length(); i++){
       value += c.at(i);
 }
 return value;
}*/

string list[100];
int listptr = -1, list_size = -1, ptr = 0;

void upshift()
{
  listptr++;
  if(listptr >= 100)
   listptr = 99;
  
  if(listptr < list_size){
    flush(); // flush current input from console
    oc_stream = 0;
    o_stream(list[list_size - listptr]); // output from list stream
  }
  else {
    flush();
    oc_stream = 0;
    o_stream(list[0]);
    listptr = list_size;
  }
}

void downshift()
{
  listptr--;
  if(listptr < 0){
    listptr = -1;
    flush();
    oc_stream = 0;
    o_stream(command);
  }
  else {
    flush(); // flush current input from console
    oc_stream = 0;
    o_stream(list[list_size - listptr]); // output from list stream
  }
}

string trim(string str)
{
  return str.substr(0, str.size()-1);
}

#define KEY_UP 183
#define KEY_DOWN 184
#define KEY_RIGHT 185
#define KEY_LEFT 186
#define ESC 27
#define ENTER 13
#define CTRL_Z 26
#define BACKSPACE 127

int key, KEY_WAIT = 0, KEY_EVENTS = 0;
void key_event(char event) // we have full control of all keyboard recieved inputs
{
  key = (int) event;
  if(key == ESC){
    KEY_WAIT = 3; // wait 2 keys
  }

  KEY_WAIT--;
  if(KEY_WAIT <= 0){
    key += KEY_EVENTS;
    KEY_WAIT = 0;
    KEY_EVENTS = 0;
    switch( key ){
       case KEY_UP:
         upshift();
         getinput();
       break;
       case KEY_DOWN:
        downshift();
        getinput();
       break;
       case KEY_RIGHT:
         for(int i = 0; i < 4; i++)
           cout << "\b";
         cout << "    ";
         for(int i = 0; i < 4; i++)
           cout << "\b";
         getinput();
       break;
       case KEY_LEFT:
         for(int i = 0; i < 4; i++)
           cout << "\b";
         cout << "    ";
         for(int i = 0; i < 4; i++)
           cout << "\b";
         getinput();
       break;
       case CTRL_Z:
           p_exit();
       break;
       case BACKSPACE:
        {
          oc_stream--;
          if(!(oc_stream <= 0)){
            if(listptr < 0)
            { }
            else{
              command = list[ list_size - listptr ];
              listptr = -1;
            }
            command = trim(command);
            flush();
            cout << command;
          }
          else
            oc_stream = 0;
          getinput();
        }
       break;
       case ENTER:
         {
         if(listptr < 0)
         { }
         else
          command = list[ list_size - listptr ];

          flush();
          cout << command;
          oc_stream = 0;

         list_size++;       // save command
         if((list_size > 100) || (ptr > 99)){
           list_size = 100;
           ptr = 0;
         }

         list[ ptr++ ] = command;
         listptr = -1;
         cout << "\n";
        }
       break;
       default:
         if(listptr < 0)
         { }
         else{
           command = list[ list_size - listptr ];
           listptr = -1;
         }
         stringstream ss;
         ss << (char) key;
         command += ss.str();
//         cout << "letter or symbol " << key << " " << command << " \n";
         getinput();
       break;
    }
  }
  else{
    KEY_EVENTS += key;
    getinput();
  }
}

void getinput()
{

  s_char();
  key_event(c);
  c = '#';
}

void debug_help()
{
  cout << "\nDebug Commands" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "ls(list)       list debugger commands" << endl;
  cout << "n(next)        go to next line of execution" << endl;
  cout << "cont(continue) continue until a breakpoint is reached" << endl;
  cout << "so(step out)   step out of a reaccurring loop or function" << endl;
  cout << "fn(force next) force jump to next occurance of a reaccurring if statement, loop, or function" << endl;
  cout << "?              print what is about to be executed" << endl;
  cout << "up/down(arrow keys)   shift up and down a list of recent debugger commands" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  debugger(addrr,instr);
}

void debug()
{
   cout << "{Debug Mode}" << endl;
   cout << "\n";
   has_started = true;
}

