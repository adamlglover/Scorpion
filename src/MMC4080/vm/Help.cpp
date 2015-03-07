#include "Sys/properties.h"
#include "Ram/ram.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define NUM_ARGS 5
string args[ NUM_ARGS ];

string ARG = "";

void prepargs()
{
   args[0] = "-version";
   args[1] = "-hardware";
   args[2] = "-properties";
   args[3] = "-help";
   args[4] = "-fspecs";
}

bool isarg(string arg)
{
  for(int i = 0; i < NUM_ARGS; i++)
  {
     if(arg == args[i]){
        ARG = arg;
        return true;
     }
  }

  return false;
}

void handleargs()
{
  if(ARG == "-help"){
     cout << "Usage: scorpion [FILE] | scorpion [ARG]\n\n" << endl;
     cout << "[FILE]\n\nFile must be a binary executable(bexe) contailing only 1's, 0's, and .'s\n\n" << endl;
     cout << "[ARG]\n\n    -version          print the current product version and exit" << endl;
     cout << "    -hardware         print out suported product virturalized hardware" << endl;
     cout << "    -fspecs           print full product virturalized components w/ specs" << endl;
     cout << "    -properties       print standard system properties\n" << endl;
  }
  else if(ARG == "-hardware"){
     cout << "Scorpion(TM) Virtural Hardware\n" << endl;
     cout << "\tCPU   RAM   HardDrive   System Cache" << endl;
  }
  else if(ARG == "-fspecs"){
      Ram rm;
     cout << "Scorpion(TM) Full Virturalized System Specs\n\n";
     cout << "CPU\nType: x86 Arm Core i1 CPU\nClock speed: .031-33Mhz\nProgram instruction set: 4(the amount of instructions read as 1)\nInstructions: 62 Opcodes\n" << endl;
     cout << "Ram\nTotal Size: " << rm.info(1) << "mb of Ram\nAccess Size: " << rm.info(3) << "mb of Ram\nSpecial Regiaters: 14 dedicated memory locations\n" << endl;
     cout << "Hardrive\nType: Disk img reader\nSize Limit: Max 64gb disk img size\n" << endl;
     cout << "System Cache\nTotal Size: 30mb of total possible program size\nis inversly porportional to the Ram size\n" << endl;
     cout << "STD Out(standard out)\nsupported formats :\n  decimal\n  bool\n  char\n  system stat(any status code defined by the vm)\nno current supported console input\n" << endl;
     cout << "GPIO(General Purpose Input Output)\nnot yet supported\n" << endl;
  }
  else if(ARG == "-properties"){
     Properties props;
     props.build();
     props.list();
  }
  else if(ARG == "-version"){
     cout << "scorpion version \"0.0.1\"\nScorpion Virtural Machine(TM)\nplatform version(0.0.1-x86)" << endl;
  }
  exit(1);
}
