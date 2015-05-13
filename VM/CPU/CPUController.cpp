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
#include "cpu.h"
#include "core0/core0.h"
#include <iostream>
using namespace std;

C0 core0;
void CPU::Reset()
{
  core0.Reset();
}

void CPU::Halt()
{
  core0.Halt();
}

void CPU::Run()
{
  core0.run0();
}

