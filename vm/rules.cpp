#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Log/filter.h"
#include "Log/Log.h"
#include "program.h"
using namespace std;

Log rules_log;
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
             || (prog.at(i) == '\t') || (prog.at(i) == ' ') || (prog.at(i) == '\n'))
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
        if(file_exists(file)){
           tostring(file);
        if(hassyntax(p)){
             Program App;
             App.Save(p);
             isgenuine = true;
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
          stream << "Fatal err occured. File '" << file << "' does not exist!";
         string data = stream.str();
         rules_log.v("System",data);
      }
   }

     bool ext(string filename, string extn)
     {
         // the actual extention if file
         string aext = "";
        for(int i = filename.length() - extn.length(); i < filename.length(); i++)
       {
         // verify if the file has an extention
         if((filename.at(i) == '.') && (aext == ""))
           aext = aext + filename.at(i);
         else if((i > filename.length() - extn.length()))
           aext = aext  + filename.at(i);
         else
           break;
        }
         return (aext == extn);
      }

   void verify( int argc, const char **file )
   {
       rules_log.v("System","Verifying args...");
       if(argc == 2){
          if(ext(file[1],".bexe"))
              authenticate(file[1]);
          else
            rules_log.v("System","Fatal err occured. File is not a binary executable file '.bexe'");
       }
       else if(argc < 2)
         rules_log.v("System","Fatal err occured. No input files, System Halt!");
       else if(argc > 2)
         rules_log.v("System","Fatal err occured. Too many argument inputs, System Halt!");
   }

bool OK( int argc, const char **file )
{
   verify(argc, file);
   return isgenuine;
}
