#include <iostream>
#include <string>
#include "Assembler.h"
using namespace std;


bool Assembler::compilation_terminated = false;
bool Assembler::compile_only = true;
int flag = 0;

extern int fsize;
extern string *sourceFiles;
extern string tostring(const char *file);
extern void assemble(string filen, string content);
extern void umap();

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
    
  }
  return 0;
}

