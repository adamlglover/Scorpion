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
#include "CPU/core0/runtime_exception.h"
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include "program.h"
#include <sstream>
#include <iostream>
using namespace std;

#define MAX_SIZE 24000000 /* 24mb of secondary Ram */
string program[ MAX_SIZE ];
long SIZE = 0;

int SRam::DONE = 4820;
int SRam::RUNNING = 5038;
int SRam::UNKNOWN = -20482;
int SRam::CB = 0;

int sr_state;
long sr_addr = 0;
bool first_time = true;
extern int INDEX_OUT_OF_RANGE;
extern int INDEX_OK;

void SRam::wipe()
{
   if(!first_time){
     for(int i = 0; i < SIZE; i++)
          program[ i ] = "0";
     SIZE = 0;
   }
   else {
     first_time = false;
   }
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

void SRam::s_e(int value)
{
  SRam::CB = value;
}

int SRam::addr(long index)
{
  if(index < 0 || index > MAX_SIZE){
         sr_state = INDEX_OUT_OF_RANGE;
     return INDEX_OUT_OF_RANGE;
  }
  else
     sr_addr = index;
  sr_state = INDEX_OK;
  return INDEX_OK;
}

string SRam::modify(string data)
{
 if( sr_state == INDEX_OK ){
   switch( SRam::CB )
   {
      case 1: //set
        program[ sr_addr ] = data;
      break;
      case 2://enable
        if(sr_addr < 0 || sr_addr > SIZE)
        {
            stringstream ss;
            ss << sr_addr;
            RuntimeException re;
            re.introduce("SRamProgramOutOfRangeException", "cannot access program at index [" + ss.str() + "]");
        }
        return program[ sr_addr ];
      break;
      default:
      // err
       RuntimeException re;
           re.introduce("SRamControlBusException","cannot access cell, invalid control bus input");
      break;
   }
  }
   else if(sr_state == INDEX_OUT_OF_RANGE) {
     stringstream ss;
     ss << sr_addr;
     RuntimeException re;
     re.introduce("SRamIndexOutOfRangeException","faliure to acccess ram at address #" + ss.str());
  }
  else {
    RuntimeException re;
     re.introduce("SRamStateUnknownException","failure to get current ram state");
  }
  sr_state = 0; // dump addr state
  SRam::CB = 0; // dump the control bus
  sr_addr = 0; // dump address
  return "";  
}

void nextinstr(string instr) /* load the next instruction to the secondary ram*/
{ 
   SRam sr;
//  cout << "next instr "<< icount + 1 << " I$ " << instr << endl;
  if(!(SIZE > MAX_SIZE)){
        program[ SIZE++ ] = instr; //  assign the next instr
  }
  else {
   printf("SRam: program_size_overload err \nsize > %d(%08x) \n      --size[%d] bytes\n", MAX_SIZE, MAX_SIZE, sr.size());
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
    if(content.at(i) == '.' || content.at(i) == ' '){
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

