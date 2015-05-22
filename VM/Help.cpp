#include "CPU/core0/core0.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

/*
* Scorpion VM Info
*/
string Version = "0.0.19_15";
string v_stage = "beta";


#define NUM_OPTIONS 5
string args[ NUM_OPTIONS ];

string OPTION = "";
int arg_start = 0;

void prepargs()
{
   args[0] = "-help";
   args[1] = "-version";
   args[2] = "-Qms:";
   args[3] = "-pstd:";
   args[4] = "-db";
}

bool isarg(string arg)
{
  for(int i = 0; i < NUM_OPTIONS; i++)
  {
     if(arg == args[i]){
        OPTION = arg;
        return true;
     }
  }

  return false;
}

bool hasdash(string arg)
{
   if(arg.at(0) == '-')
     return true;

  return false;
}

void help()
{
   cout << "Usage: scorpion binary [args..] | scorpion [-options] binary [args..]\n\n" << endl;
   cout << "Binary file must be a binary source(b) file contailing only 1's, 0's, .'s, and whitespace.\n" << endl;
   cout << "[-options]\n\n    -version          print the current product version and exit" << endl;
   cout <<               "    -Qms:<value>      set inital memory size" << endl;
   cout <<               "    -pstd:<value>     set program memory size" << endl;
   cout <<               "    -db               enable the Scorpion debug interface" << endl;
   exit(1);
}

extern long mem;
extern long xmem;
extern long pmem;
void handleargs(int argc, const char **args)
{
  string data;
  for(int i = 1; i < argc; i++){
     data = args[i];

     if(isarg(data)) {}
     else if(hasdash(data))
     {
        cout << "Unrecognized command line option: " << data << endl;
        exit(1);
     }
     else  // time for running application
      return;

     if(OPTION == "-help")
        help();
     else if(OPTION == "-version"){
        cout << "scorpion version \"" << Version << " " << v_stage << "\"\nScorpion Virtural Machine(TM)\nplatform version(" << Version << "-x24)" << endl;
        exit(1);
     }
     else if(OPTION == "-Qms:"){
        i++;
        arg_start++;
        data = args[i];
        int mb = atoi(data.c_str());
        mb *= 1000000; // convert to actual mem addrs
        mem = mb;
        if(mem == 0)
          mem = 1000000;
     }
     else if(OPTION == "-db"){
        debugging = true;
     }
     else if(OPTION == "-pstd:"){
        i++;
        arg_start++;
        data = args[i];
        int mb = atoi(data.c_str());
        mb *= 1000000; // convert to actual mem addrs
        pmem = mb;
        if(pmem == 0)
         pmem = 1000000;
     }

     arg_start++;
  }
}
