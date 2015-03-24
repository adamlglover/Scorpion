#include <string>
#include "Log.h"
#include "Logger.h"
#include "filter.h"
using namespace std;

bool Logging;
void Log::Shutdown()
{
  Logging = false;
}

void Log::On()
{
  Logging = true;
}

const int VERBOSE = 2;

const int DEBUG = 3;

const int INFO = 4;

const int WARN = 5;

const int ERROR = 6;

const int ASSERT = 7;

int Log::a(string tag, string message)
{
   return print(ASSERT,tag,message,Logging);
}

int Log::e(string tag,string message)
{
   return print(ERROR,tag,message,Logging);
}

int Log::w(string tag,string message)
{
   return print(WARN,tag,message,Logging);
}

int Log::i(string tag,string message)
{
   return print(INFO,tag,message,Logging);
}

int Log::d(string tag,string message)
{
   return print(ERROR,tag,message,Logging);
}

int Log::v(string tag,string message)
{
   return print(VERBOSE,tag,message,Logging);
}

void Log::prepare(int priority, bool to_file)
{
 Logging = true;
 Logger l;
 SetPriority( priority );
 l.init(to_file);
}
