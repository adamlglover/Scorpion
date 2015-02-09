#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Log/filter.h"
#include "Log/Log.h"
using namespace std;

Log rules_log;
void inf(string);
void x86(string);
bool isgenuine = false;

     bool file_exists(const char *fileName)
    {
      std::ifstream infile(fileName);
          return infile.good();
    }

   string program;

   void tostring(const char *name)
   {
      string tmp;

     ifstream input(name);

     while(!input.eof()) {
         tmp = "";
         getline(input, tmp);
         program += tmp;
         program += "\n";
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

   bool parsed(const char *conf)
   {
       cout << "parse conf file" << endl;
       return true;
   }

   void authenticate(const char *file)
   {
      rules_log.i("System","Checking authenticity...");
      if(file_exists(file)){
           tostring(file);
        if(hassyntax(program)){
          const char *conf = "/usr/share/svm/system.conf";
           if(file_exists(conf) && parsed(conf)){
		rules_log.i("System","Success! No errs detected. Starting System...");
                isgenuine = true;
                x86(program);
           }
           else if(!file_exists(conf)){
                rules_log.v("System","Err looking for .conf file..creating one..");
                isgenuine = true;
                x86(program);
            string fact_reset = "# SYSTEM CONFIG file for all system configurations\n\n[Log]"
            "\n\n# Determine wether logging is on or off\n\t-state=\"on\"\n"
            "\n# This is for determining the stack level for logging\n"
            "\t-stack=\"7\"   # range 2-7\n";
            ofstream conf_file ("/usr/share/svm/system.conf");
            if (conf_file.is_open())
            {
              conf_file << fact_reset;
              conf_file.close();
            }
             rules_log.v("System","System conf restore..");
             SetPriority(2);
             rules_log.On();
             rules_log.i("System","Success! No errs detected. Starting System...");
           }
           else if(!parsed(conf))
                rules_log.v("System","Error parsing .conf file");
           else
                rules_log.v("System","Fatal err: something went wrong while checking .conf file");
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
          rules_log.i("System","Checking Extention...");
          if(ext(file[1],".bo"))
              authenticate(file[1]);
          else
            rules_log.v("System","Fatal err occured. File is not a binary object file '.bo'");
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
