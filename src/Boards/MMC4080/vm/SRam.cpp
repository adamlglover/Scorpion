/**
* Virtural Random Access Memory Chip Designed by Braxton Nunnally
*
* Cells: 1
* Model: DM3 100(Standard)
* Production Date: 3-15
* Max Size: 30mb
*
* The DM3 100 Ram chip features a big 30mb memory space 
* w/ status reports of access status
*
*
* For full info visit "https://github.com/AndroDevcd/RPVM/blob/master/LINEUP.md"
*/

#include <string>
#include "CPU/cpu.h"
#include "System.h"
#include "Log/Log.h"
#include "sram.h"
#include "var.h"
#include "CPU/core0/core0.h"
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include "program.h"
#include <sstream>
#include <iostream>
using namespace std;

#define MAX_SIZE 30000000 /* 30mb of secondary Ram */
string program[ MAX_SIZE ];
long SIZE = 0;

int SRam::DONE = 4820;
int SRam::RUNNING = 5038;
int SRam::UNKNOWN = -20482;

void SRam::wipe()
{
   for(int i = 0; i < SIZE; i++)
       program[ i ] = "0";
   SIZE = 0;
}

long SRam::size()
{
   return SIZE;
}

int SRam::status(long instrptr)
{
  if((instrptr + 1) > SIZE)
    return SRam::DONE;
  else if((instrptr + 1) < SIZE)
    return SRam::RUNNING;
  else 
    return SRam::UNKNOWN;
}

void nextinstr(string instr) /* load the next instruction to the secondary ram*/
{ 
   SRam m;
//  cout << "next instr "<< icount + 1 << " I$ " << instr << endl;
  if(!(SIZE > MAX_SIZE)){
        program[ SIZE++ ] = instr;  // assign the next instr
  }
  else {
   printf("SRam: program_size_overload err \nsize > %d(%08x) --size[%d] bytes\n", MAX_SIZE, MAX_SIZE, m.size());
    cout << "Shutting down...\n";
    EBX = null;
    p_exit();
  }
}

void SRam::load(string content)
{
  string str = "";
     for(int i = 0; i < content.length(); i++)
     {
    if(content.at(i) == '.'){
       if(str != ""){
           //cout << result << endl;
           nextinstr(str);
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

string SRam::prog(long index)
{
   if(index < 0 || index > SIZE)
   {
     cout << "SRam: program_out_of_range error" << endl;
     EBX = null;
     p_exit();
   }
   return program[ index ];
}
