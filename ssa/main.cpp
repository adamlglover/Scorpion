#include "checker.h"
#include "help.h"
#include <iostream>
using namespace std;

void handle()
{

}

int main( int argc, const char **file )
{
  if(argc > 3)
     help();

  if(ok(file))
     handle();
  else{
   cout << "ssa: fatal err occured while" <<
   "attempting to run program. Use --help for help" << endl;
  }
  return 0;
}

