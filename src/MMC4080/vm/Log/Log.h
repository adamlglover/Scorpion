#ifndef LOG
#define LOG

#include <string>
using namespace std;

extern const int VERBOSE;

extern const int DEBUG;

extern const int INFO;

extern const int WARN;

extern const int ERROR;

extern const int ASSERT;

 class Log {
   public:
     int a(string tag,string message);
     int e(string tag,string message);
     int w(string tag,string message);
     int i(string tag,string message);
     int d(string tag,string message);
     int v(string tag,string message);
     void Shutdown();
     void On();
     void prepare(int,bool);
 };

#endif
