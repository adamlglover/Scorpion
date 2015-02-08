#ifndef LOG
#define LOG

#include <string>
using namespace std;

 class Log {
   public:
     int a(string tag,string message);
     int e(string tag,string message);
     int w(string tag,string message);
     int i(string tag,string message);
     int d(string tag,string message);
     int v(string tag,string message);
     void Shutdown();
     void prepare(int,bool);
 };

#endif
