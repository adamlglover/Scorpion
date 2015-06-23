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
#include <iostream>
#include "Logger.h"
using namespace std;

int PRIORITY = 1;

Logger logger;
void SetPriority(int priority)
{
  if(priority <= 2)
    PRIORITY = 2;
  else if(priority >= 7)
    PRIORITY = 7;
  else
    PRIORITY = priority;
}

int print(int priority, string tag, string message, bool log)
{
     if(!log)
         return 0;
     else if(log){
         if(PRIORITY == 1){
             cout << "svm: warning: err processing log, priority not set." << endl;
             return 0;
	 }
         else {
           if(priority <= PRIORITY)
               return logger.println(priority,tag,message);
           else
               return 0;
         }
     }
}
