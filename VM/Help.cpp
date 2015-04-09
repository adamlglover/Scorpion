#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

/*
* Scorpion VM Info
*/

string Version = "0.0.19_2";
string v_stage = "beta";

// ----------------------------------

#define NUM_OPTIONS 2
string args[ NUM_OPTIONS ];

string OPTION = "";

void prepargs()
{
   args[0] = "-help";
   args[1] = "-version";
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

void handleargs()
{
  if(OPTION == "-help"){
     cout << "Usage: scorpion [FILE] [args..]| scorpion [OPTION]\n\n" << endl;
     cout << "[FILE]\n\nFile must be a binary source(b) file contailing only 1's, 0's, .'s, and whitespace.\n\n" << endl;
     cout << "[OPTIONS]\n\n    -version          print the current product version and exit" << endl;
  }
  else if(OPTION == "-version"){
     cout << "scorpion version \"" << Version << " " << v_stage << "\"\nScorpion Virtural Machine(TM)\nplatform version(" << Version << "-x86)" << endl;
  }
  exit(1);
}
