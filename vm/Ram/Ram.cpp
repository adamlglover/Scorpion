/**
* Virtural Random Access Memory Chip Designed by Braxton Nunnally
*
* Cells: 5
* Model: DM3 101
* Production Date: 3-15
* R\C: 1mb
* Max Size: 5mb
*
* The DM3 101 Ram chip features a heavy 5 cell access ratio
* and a tiny ammount of Ram w/ status reports of access status
*
*
* For full info visit "https://github.com/AndroDevcd/RPVM/blob/master/LINEUP.md"
*/
#include "../CPU/cpu.h"
#include "../System.h"
#include "../Log/Log.h"
#include "../var.h"
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include "../CPU/core0/core0.h"
#include "../CPU/core0/runtime_exception.h"
#include "../program.h"
#include "ram.h"
#include "../CPU/core0/cpuf.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#define MAX 2000000 /* 1mb of R\c(ram per cell)*/
#define MAX_SIZE 16000000 /* 16mb of program memory */
#define NUM_CELLS 6
double ram[ MAX ]; // cell 0
double fram[ MAX ]; // cell 1
double lram[ MAX ];// cell 2
double xram[ MAX ];// cell 3
double lfram[ MAX ];// cell 4
string program[ MAX_SIZE ]; // cell 5

int rsize;

   int state;

long SIZE = 0;
int Ram::DONE = 4820;
int Ram::RUNNING = 5038;
int Ram::UNKNOWN = -20482;

int sr_state;
long sr_addr = 0;
bool first_time = true;
extern int INDEX_OUT_OF_RANGE;
extern int INDEX_OK;
long Ram::CB = 0;
short Ram::CS = 0;
long address = 0;
int Ram::addr(long index)
{
  if(index < 0 || index > MAX){
         state = INDEX_OUT_OF_RANGE;
     return INDEX_OUT_OF_RANGE;
  }
  else
     address = index;
  state = INDEX_OK;
  return INDEX_OK;
}

int Ram::cell(short index)
{
   if(index < 0 || index > NUM_CELLS){
         state = INDEX_OUT_OF_RANGE;
     return INDEX_OUT_OF_RANGE;
  }
  else
     CS = index;
  state = INDEX_OK;
  return INDEX_OK;
}

string prog_data = "";
long _char(long _ch);
int ibool(long);
double Ram::data(double dataBus)
{
  if( state == INDEX_OK ){
   if(Ram::CS == 0) {
      switch( Ram::CB ) {
         case 1: // S
        //   cout << "Saving " << dataBus<< "to ram CB " << Ram::CB << " address " << address << endl;
           if(fram[ address ] == INT)
            ram[ address ] = (long) dataBus;
           else if(fram[ address ] == SHORT)
            ram[ address ] = (int) dataBus;
           else if(fram[ address ] == FLOAT)
            ram[ address ] = (float) dataBus;
           else if(fram[ address ] == CHAR)
            ram[ address ] = _char(dataBus);
           else if(fram[ address ] == BOOL)
            ram[ address ] = ibool( (long) dataBus);
           else // format as double
            ram[ address ] = dataBus;
      //     if((address >= 30) && (address <= 33))
        //     cout << "ram " << ram[ address ];
         break;
         case 2: // E
        //   cout << "Getting " << dataBus<< "from ram CB " << Ram::CB << " address " << address << endl;
            if(fram[ address ] == INT)
              return (long) ram[ address ];
            else if(fram[ address ] == SHORT)
              return (int) ram[ address ];
            else if(fram[ address ] == FLOAT)
              return (float) ram[ address ];
            else // format as double
              return ram[ address ];
         break;
         default:
           RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
         break;

      }
   }
   else if(Ram::CS == 1){
      switch( Ram::CB ) {
         case 1: // S
           fram[ address ] = dataBus;
         break;
         case 2: // E
           return fram[ address ];
         break;
         default:
           RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
         break;

      }
   }
   else if(Ram::CS == 2){
      switch( Ram::CB ) {
         case 1: // S
           lram[ address ] = dataBus;
         break;
         case 2: // E
           return lram[ address ];
         break;
         default:
          RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
         break;

      }
   }
   else if(Ram::CS == 3){
      switch( Ram::CB ) {
         case 1: // S
           xram[ address ] = dataBus;
         break;
         case 2: // E
           return xram[ address ];
         break;
         default:
           RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
         break;

      }
   }
    else if(Ram::CS == 4){
      switch( Ram::CB ) {
         case 1: // S
           lfram[ address ] = dataBus;
         break;
         case 2: // E
           return lfram[ address ];
         break;
         default:
           RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
         break;

      }
   }
   else if(Ram::CS == 5){
     switch( Ram::CB ) {
      case 1: //set
              program[ address ] = prog_data;
      break;
      case 2://enable
        if(address < 0 || address > SIZE)
        {
            stringstream ss;
            ss << address;
            RuntimeException re;
            re.introduce("RamProgramOutOfRangeException", "cannot access program at index [" + ss.str() + "]");
        }
        prog_data = program[ address ];
      break;
      default:
      // err
       RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
      break;
     }
   }
   else{
     cout << "Ram: warning cell_not_found err" << endl;
     cout << "Ram: reverting to cell 0" << endl;
      switch( Ram::CB ) {
         case 1: // S
           ram[ address ] = dataBus;
         break;
         case 2: // E
           return ram[ address ];
         break;
         default:
           RuntimeException re;
           re.introduce("RamControlBusException","cannot access cell, invalid control bus input");
         break;
      }
   }
  }
  else if(state == INDEX_OUT_OF_RANGE) {
     stringstream ss;
     ss << address;
     RuntimeException re;
     re.introduce("RamIndexOutOfRangeException","faliure to acccess ram at address #" + ss.str());
  }
  else {
    RuntimeException re;
     re.introduce("RamStateUnknownException","failure to get current ram state");
  }
  state = 0; // dump addr state
  Ram::CB = 0; // dump the control bus
  address = 0; // dump address
  return 0;
}


void Ram::prog_wipe()
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

int Ram::prog_status(long instrptr)
{
  if((instrptr + 1) > SIZE)
    return Ram::DONE;
  else if((instrptr + 1) < SIZE)
    return Ram::RUNNING;
  else 
    return Ram::UNKNOWN;
}

long b_tmb(long bytes)
{
   return (bytes / 1000000);
} // convert from bytes to mb

long Ram::info(int info)
{
   if(info == 0)
    return MAX; // return r/c unformatted
   else if(info == 3)
    return b_tmb(MAX); // return r/c formatted
   else if(info == 1)
    return b_tmb((MAX * (NUM_CELLS - 1)) + MAX_SIZE); // return total ram size
   else if(info == 2)
    return NUM_CELLS; // return the total num of ram cells
   else if (info == 4)
	return b_tmb(MAX_SIZE); // return total program mem formatted
   else if (info == 6)
        return MAX_SIZE; // return total program mem unformatted
   else if(info == 5)
	return SIZE; // return current occupied prog mem
  else 
    return 0;
}

// ---------------------------------------------------------------------------

bool overload = false;
void nextinstr(string instr) /* load the next instruction to ram*/
{ 
//  cout << "next instr "<< icount + 1 << " I$ " << instr << endl;
   if(!(SIZE > MAX_SIZE)){
        program[ SIZE++ ] = instr; //  assign the next  instr(I was being lazy)
        if((SIZE -1) < L1_ICache_length)
          L1_ICache[SIZE - 1] = instr; // this was the best I could do at the moment
   }
   else {
     overload = true;
     SIZE++;
  }
}

void Ram::prog_load(string content)
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
    if(!overload){
    	Log l;
    	stringstream ss;
     	ss << SIZE;
    	l.v("System","Program finished loading to memory with size [" + ss.str() + "] bytes");
    	Program Applet;
    	Applet.Runnable(true);
    }
    else {
      Ram ramm;
      printf("Ram: program_size_overload err \nsize > %d(%08x) \n      --size[%d] bytes\n", MAX_SIZE, MAX_SIZE, ramm.info(5));
      cout << "Shutting down...\n";
      EBX = null;
      p_exit();
    }
}

