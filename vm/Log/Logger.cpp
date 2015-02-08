#include <string>
#include <iostream>
#include "../ctime.h"
#include "Logger.h"
using namespace std;

bool tofile = false;
string stackmsg = "";

string t_ch(int priority)
{
   switch( priority ){
      case 2:
        return "v";
      case 3:
        return "d";
      case 4:
        return "i";
      case 5:
        return "w";
      case 6:
        return "e";
      case 7:
        return "a";
      default:
        return "?";
   }
}
int Logger::println(int priority,string tag,string message)
{
  if(!tofile){
    stackmsg += currtime() + ":" + t_ch(priority) + "/" + tag + ": " + message + "\n"; 
  }
}

void Logger::printStackTrace()
{
  cout << stackmsg << endl;
}

void Logger::init(bool to_file)
{
  tofile = to_file;
  if(!to_file){
     stackmsg += "=======System Dev Log begin=======\n";
     println(2,"System","System init..");
  }
}

