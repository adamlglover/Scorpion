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
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Log/filter.h"
#include "Log/Log.h"
#include "program.h"
using namespace std;

Log rules_log;
string prog_name = "";
bool isgenuine = false;

   bool file_exists(const char *fileName)
   {
     std::ifstream infile(fileName);
         return infile.good();
   }

   string p;
   extern string PROG;
   void tostring(const char *name)
   {
      string tmp;

     ifstream input(name);

     while(!input.eof()) {
         tmp = "";
         getline(input, tmp);
         PROG += tmp;
         PROG += "\n";
     }
    }

  int _char;
  char uchar;
  bool hassyntax(string prog)
  {
   _char = 0;
    for(int i = 0; i < prog.length(); i++){

        if((prog.at(i) == '1') || (prog.at(i) == '0') || (prog.at(i) == '.')
             || (prog.at(i) == '\t') || (prog.at(i) == ' ') || (prog.at(i) == '\n') || (prog.at(i) == 10) || (prog.at(i) == 13) )
         _char++;
        else{
          uchar = prog.at(i);
          return false;
        }
    }
     return true;
  }

   void authenticate(const char *file)
   {
        stringstream ss, ss2;
        ss << file << ".b";
        string bridge = ss.str();
        const char *name = bridge.c_str();
        if(file_exists(name)){
           tostring(name);
        if(hassyntax(PROG)){
            isgenuine = true;
            prog_name = file;
        }
        else{
          std::ostringstream stream;
          stream << "Fatal err occured. Unexpected char in file char:" << _char << " *^" << uchar << ". Permitted <'1' : '0' : '.' : witespace>";
          string data = stream.str();
          rules_log.v("System",data);
        }
      }
      else{
         std::ostringstream stream;
         stream << "Fatal err occured. Could not find or load binary executable " << file;
         string data = stream.str();
         rules_log.v("System",data);
      }
   }

extern int arg_start;
   void verify( int argc, const char **file )
   {
       rules_log.v("System","Verifying args...");
       if(argc >= 2)
         authenticate(file[ arg_start + 1 ]);
       else if(argc < 2)
         rules_log.v("System","Fatal err occured. No input files, System Halt!");
   }

string getname()
{
  return prog_name;
}

bool OK( int argc, const char **file )
{
   verify(argc, file);
   return isgenuine;
}

