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
#include <iostream>
#include "Log/Logger.h"
#include "Log/Log.h"
#include "program.h"
#include "Sys/properties.h"

using namespace std;

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

