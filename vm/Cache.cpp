#include <string>
#include "CPU/cpu.h"
#include "System.h"
#include "Log/Log.h"
#include "cache.h"
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include "program.h"
#include <sstream>
#include <iostream>
using namespace std;

#define MAX_SIZE 30000000 /* 30mb of Cache */
long program[ MAX_SIZE ];
long SIZE = 0;

int Cache::DONE = 4820;
int Cache::RUNNING = 5038;
int Cache::UNKNOWN = -20482;

void x86Shutdown();
void Cache::wipe()
{
   for(int i = 0; i < SIZE; i++)
       program[ i ] = 0;
   SIZE = 0;
}

long Cache::size()
{
   return SIZE;
}

int Cache::status(long instrptr)
{
  if((instrptr + 1) > SIZE)
    return Cache::DONE;
  else if((instrptr + 1) < SIZE)
    return Cache::RUNNING;
  else 
    return Cache::UNKNOWN;
}

void nextinstr(long instr) /* load the next instruction to the cache*/
{ 
   Cache m;
//  cout << "next instr "<< icount + 1 << " I$ " << instr << endl;
  if(!(SIZE > MAX_SIZE)){
        program[ SIZE++ ] = instr;  // assign the next instr
  }
  else {
   printf("Cache: program_size_overload err \nsize > %d(%08x) --size[%d] bytes\n", MAX_SIZE, MAX_SIZE, m.size());
    cout << "Shutting down...\n";
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

void Cache::load(string content)
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

long Cache::prog(long index)
{
   if(index < 0 || index > SIZE)
   {
     cout << "Cache: program_out_of_range error" << endl;
     EBX = 1;
     p_exit();
   }
   return program[ index ];
}
