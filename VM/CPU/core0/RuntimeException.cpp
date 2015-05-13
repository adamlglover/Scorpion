/*
* Copyright 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/
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

