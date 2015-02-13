#include <string>
#include "Log/Log.h"
#include "mem.h"
#include <math.h>
#include <cstdlib>
#include "program.h"
#include <sstream>
#include <iostream>
using namespace std;

#define MAX_SIZE 80000000
long program[ MAX_SIZE ];
long SIZE = 0;

int Memory::DONE = 4820;
int Memory::RUNNING = 5038;
int Memory::UNKNOWN = -20482;

void x86Shutdown();
void Memory::wipe()
{
   for(int i = 0; i < SIZE; i++)
       program[ i ] = 0;
   SIZE = 0;
}

long Memory::size()
{
   return SIZE;
}

int Memory::status(long instrptr)
{
  if(instrptr > SIZE)
    return Memory::DONE;
  else if(instrptr < SIZE)
    return Memory::RUNNING;
  else 
    return Memory::UNKNOWN;
}

void nextinstr(long instr) /* load the next instruction to the cpu*/
{ 
   Memory m;
//  cout << "next instr "<< icount + 1 << " I$ " << instr << endl;
  if(!(SIZE > MAX_SIZE)){
        program[ SIZE++ ] = instr;  // assign the next instr
  }
  else {
    cout << "program too large size > 80000000(4C4B400) --size [" << m.size() << "] bytes" << endl;
    cout << "Shutting down...";
    x86Shutdown();
  }
}

long parse_long(string str)
{
   std::istringstream ss(str);
    long i;
    ss >> i;
   return i;
}

void Memory::load(string content)
{
  string str = "";
     for(int i = 0; i < content.length(); i++)
     {
    if(content.at(i) == '.'){
       if(str != ""){
           //cout << result << endl;
           nextinstr(parse_long(str));
           str = "";
       }
    }
    else if((content.at(i) == '1'))
       str.append("1");
    else if(content.at(i) == '0')
       str.append("0");
  }
    Log l;
    stringstream ss;
     ss << SIZE;
    l.v("System","Program finished loading to memory with size [" + ss.str() + "] bytes");
    Program Applet;
    Applet.Runnable(true);
}

long Memory::prog(long index)
{
  return program[ index ];
}
