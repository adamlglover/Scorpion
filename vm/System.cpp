#include <iostream>
#include "Log/Logger.h"
#include "Log/Log.h"
#include "program.h"
#include "Sys/properties.h"

using namespace std;

void inf(string);
namespace System {
  bool Running;
  Log Sys_log;
  Properties prop;
  Program Application;
  void SetupSystem()
  {
    Sys_log.v("System","Setting up System...");
    prop.build();
    Application.Main();
  }
}

