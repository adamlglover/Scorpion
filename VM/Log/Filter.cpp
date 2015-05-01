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
