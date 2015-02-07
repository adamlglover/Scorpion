#include <string>
#include <iostream>
#include "ctime.h"
#include "CPU/cpu.h"
#include "rules.h"
#include "System.h"

using namespace std;

//using namespace CPU;

  string message = "";
   void setup(){
     message = "=======System Dev Log begin=======\n" + currtime() + ": System init..\n";
   }

   void inf( string msg )
   {
       message += currtime() + ": " + msg + "\n";
   }

   string errstack(){
      return message;
   }

string bo_prog = "";
void x86(string prog)
{
  bo_prog = prog;
}

void Restart()
{
    System::Running = false;
    CPU mprocessor;
    mprocessor.Reset();
    System::Running = true;
    System::SetupSystem();
}

void Start()
{
   CPU mprocessor;
   System::Running = true;
   mprocessor.Reset();
   System::SetupSystem();
}

void display()
{
  cout << errstack() << endl;
}


int main( int argc, const char **file )
{
  setup();
  if(OK(argc, file)){
      Start();
      display();
  }
  else
    display();
   return 0;
}

