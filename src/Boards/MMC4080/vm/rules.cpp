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

   void tostring(const char *name)
   {
      string tmp;

     ifstream input(name);

     while(!input.eof()) {
         tmp = "";
         getline(input, tmp);
         p += tmp;
         p += "\n";
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
        stringstream ss;
        ss << file << ".bexe";
        string bridge = ss.str();
        const char *name = bridge.c_str();
        if(file_exists(name)){
           tostring(name);
        if(hassyntax(p)){
             Program App;
             App.Save(p);
             isgenuine = true;
           prog_name = file;
        }
        else{
          std::ostringstream stream;
          stream << "Fatal err occured. Unknown char in file char:" << _char << " *^" << uchar << ". Permitted <'1' : '0' : '.' : witespace>";
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

   void verify( int argc, const char **file )
   {
       rules_log.v("System","Verifying args...");
       if(argc == 2)
          authenticate(file[1]);
       else if(argc < 2)
         rules_log.v("System","Fatal err occured. No input files, System Halt!");
       else if(argc > 2)
         rules_log.v("System","Fatal err occured. Too many argument inputs, System Halt!");
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

