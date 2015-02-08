#include <iostream>
#include "Log/Logger.h"
#include "Log/Log.h"

using namespace std;

void inf(string);
namespace System {
  bool Running;
  Log Sys_log;
  void SetupSystem()
  {
    Sys_log.v("System","Setting up System...");
  }
}

