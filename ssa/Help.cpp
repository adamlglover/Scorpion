#include <iostream>
using namespace std;

void help()
{
  cout << "Usage: ssa [option] [program] [output-file]| ssa [program] [output-file] \n| ssa [program]\n\n[program]" << endl;
  cout << "    The input program must be a single .ss file\n\n[option]" << endl;
  cout << "              -c        only compile the program(do not generate bytecode" << endl;
}

