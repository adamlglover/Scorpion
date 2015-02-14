#include "console.h"
#include "../mem.h"
#include "../Bus/bus.h"
#include <iostream>
#include <string>
using namespace std;

#define NUM_C_ADDRS 4
int c_addr[NUM_C_ADDRS] = {0x30, 0x32, 0x36, 0x39};
int c_addrs[NUM_C_ADDRS];

string i_tbl(int num)
{
   if(num >= 1)

        return "true";
   else 
        return "false";
}

void Console::Setup()
{
    for(int i = 0; i < NUM_C_ADDRS; i++)
       c_addrs[i] = STATUS_OPEN;
}

int Console::Write(int addr, long *input)
{
 for(int i = 0; i < NUM_C_ADDRS; i++){
   if(addr  == c_addr[i]){
       if(c_addrs[ addr ] == STATUS_OPEN)
       {
           if(input[3] == 0){ // dout
            cout << input[0] << endl;
	     return STATUS_OPEN;
           }
           else if(input[3] == 1){ // bout
             cout << i_tbl(input[0]) << endl;
             return STATUS_OPEN;
           }
           else if(input[3] == 2){ // size
             Memory s;
             cout << s.size() << endl;
             return STATUS_OPEN;
           }
           else {
             c_addrs[ addr ] = STATUS_BROKEN;
             return STATUS_BROKEN;
           }
        }
       else
         return c_addrs[ addr ];
    }
  }
          return  PORT_ADDRESS_UNKNOWN;
}

int Console::Process(int addr, long command, long *input)
{
    return STATUS_OPEN; 
}
