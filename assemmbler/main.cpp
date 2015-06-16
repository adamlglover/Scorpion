#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include "Assembler.h"
using namespace std;


bool Assembler::compilation_terminated = false;
bool Assembler::compile_only = false;
int flag = 0;

extern int fsize;
extern string *sourceFiles, *objFiles, fOutput;
extern string tostring(const char *file);
extern void assemble(string filen, string content);
extern void umap();
extern void fOut(const char *filename, string source);

void help();
void handleargs(int, const char **f);
int main(int argc, const char **file)
{

  if(argc >= 2)
    handleargs(argc, file);
  else if(argc == 1)
    help();

   for(int i = 0; i < fsize; i++)
  {
    assemble(sourceFiles[i], tostring(sourceFiles[i].c_str()));
  }

  umap();
  if(!Assembler::compile_only){ // link and generate binary file
     fOut(fOutput.c_str(), "");
     for(int i = 0; i < fsize; i++)
     {
       stringstream ss;
       ss << tostring(objFiles[i].c_str()) << tostring(fOutput.c_str());
       fOut(fOutput.c_str(), ss.str());
     }
  }

   for(int i = 0; i < fsize; i++) // clean up objects
  {
    remove(objFiles[i].c_str());
  }
  return 0;
}

