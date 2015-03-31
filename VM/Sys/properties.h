#ifndef PROP
#define PROP
#include <string>
using namespace std;

   class Properties {
	public:
           void build();
           string GetProperty(string name);
           void list();
           int bad();
           int good();
           int SetProperty(string,string);
           string s_list();
           void PropertyNames();
   }; 

#endif
