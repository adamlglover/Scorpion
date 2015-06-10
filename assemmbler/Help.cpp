#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Assembler.h"
using namespace std;


string Version = "0.1.48";
string v_stage = "beta";


#define NUM_OPTIONS 5
string args[ NUM_OPTIONS ];

string OPTION = "";
bool has_output_file = false;
string fOutput = "";
string *sourceFiles, *objFiles;
string binObj;  // This will be our final executable file
int fsize;
long l_size = 2000000;

bool file_exists(const char *fileName)
{
    std::ifstream infile(fileName);
        return infile.good();
}

string tostring(const char *file)
{
     string tmp, content;

     ifstream input(file);

     while(!input.eof()) {
         tmp = "";
         getline(input, tmp);
         content += tmp;
         content += "\n";
     }
   return content;
}

bool isempty(string str)
{

  for(int i = 0; i < str.size(); i++)
  {
    if((str.at(i) != ' ') && (str.at(i) != '\t') && (str.at(i) != '\n')
          && (str.at(i) != 10) && (str.at(i) != 13))
      return false;
  }

  return true;
}

string trim(string str)
{
  return str.substr(0, str.size()-1);
}

bool endswith(string extention, string file)
{
  int pushback = extention.size();
  int idx = file.size() - pushback;
  if(idx < 0)
   return false;

  stringstream ext;
  for(int i = 0; i < pushback; i++)
      ext << file.at(idx++);

  if(extention != ext.str())
   return false;
  return true;
}

void testfiles()
{
  bool ok = true;
  for(int i = 0; i < fsize; i++)
  {
    if(!file_exists(sourceFiles[i].c_str())){
      ok = false;
      cout << "nsc:  error: " << sourceFiles[i] << ": No such file or directory\n";
    }
    else if(!endswith(".ss",sourceFiles[i])){
      ok = false;
      cout << "nsc:  error: " << sourceFiles[i] << ": Is not a .ss file\n";
    }
  }
   if(!ok){
     cout << "compilation terminated.\n";
     exit(-19013625);
   }
}

void prepargs()
{
  args[0] = "-help";
  args[1] = "-version";
  args[2] = "-o";
  args[3] = "-c";
  args[4] = "-lsz";

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
   cout << "Usage: nsc [main] [file..] | nsc [-options] [main] [file..]\n";
   cout << "[-options]\n\n    -version          print the current product version and exit\n";
   cout << "    -o<file>          set object file to generate\n";
   cout << "    -c                only compile the program\n";
   cout << "    -lsz              allocate a set ammount of labels for your application\n";
   exit(1);
}

void handleargs(int argc, const char **args)
{
  prepargs();
   string data = "";
   int idx = 0;
  for(int i = 1; i < argc; i++){
     data = args[i];

     if(isarg(data)) {}
     else if(hasdash(data))
     {
        cout << "Unrecognized command line option: '" << data << "'" << endl;
        exit(1);
     }
     else{  // time for running application
        if(!has_output_file && !Assembler::compile_only)
           fOutput = "out.b";

        fsize = argc - i;
        sourceFiles = new string[ argc - i ];
        objFiles = new string[ argc - i ];
        for(int x = i; i < argc; x++ ) {
            sourceFiles[idx++] = args[x];
            i++;
        }
       break;
     }


     if(OPTION == "-help")
        help();
     else if(OPTION == "-version"){
        cout << "Native Scorpion Compiler(nsc)\nbuild: " + Version + " " + v_stage << endl;
        exit(1);
     }
     else if(OPTION == "-o"){
        i++;
        data = args[i];
        Assembler::compile_only = false;
        fOutput = data + ".b";
        has_output_file = true;
     }
     else if(OPTION == "-c")
        Assembler::compile_only = true;
     else if(OPTION == "-lsz"){
        i++;
        data = args[i];
        long segment;
        if(data.at(data.length() - 1) == 'k'){ // bytes
           segment = 1000;
           data = trim(data);
        }
        else if(data.at(data.length() - 1) == 'm'){ // kb
           segment = 1000000;
           data = trim(data);
        }
        else
           segment = 1;

        l_size = atoi(data.c_str());
        l_size *= segment;
        cout << "l_size: " << l_size << endl;
     }
  }

  if(idx == 0){
     cout << "nsc: fatal error; no input files!" << endl;
     exit(-19013625);
  }
  testfiles();
}



