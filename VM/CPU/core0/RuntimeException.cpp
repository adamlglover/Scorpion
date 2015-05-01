#include <string>
#include "core0.h"
#include <sstream>
#include <iostream>
#include "../../program.h"
#include "runtime_exception.h"
using namespace std;

void create_stack(string,string);
void RuntimeException::introduce(string exception, string message)
{
   create_stack(exception,message);
}

void create_stack(string excpn, string msg)
{
  stringstream ss;
  ss << IP;
  string exitmsg = "Virtural Machine RuntimeException: caused by " + excpn + ":\n    " + msg + "\n" +
                   "    Program Position {" + ss.str() + "}\n";
  cout << exitmsg;
  EBX = 1;
  p_exit();
}

