#include <string>
#include <sstream>
#include <iostream>
#include "properties.h"
#include "../Log/Log.h"
#include <stdlib.h>
using namespace std;

#define NUM_PROPERTIES 11
string names [ NUM_PROPERTIES ];
string values [ NUM_PROPERTIES ];

Log p_log;
void c_names()
{
  names[ 0 ] = "RSID-Fingerprint"; // set at startup
  names[ 1 ] = "Serial #"; // set at startup
  names[ 2 ] = "Build Version";
  names[ 3 ] = "Version #";
  names[ 4 ] = "Version Name";
  names[ 5 ] = "Processor";
  names[ 6 ] = "Security Software Version";
  names[ 7 ] = "Model #";
  names[ 8 ] = "Device Name";
  names[ 9 ] = "IP"; // set at startup
  names[ 10 ] = "Radio Addr";

  values[ 0 ] = "f3.109d7.x49l";
  values[ 2 ] = "0.0.0.0.1";
  values[ 3 ] = "1";
  values[ 4 ] = "Core";
  values[ 5 ] = "Arm i1-400 CPU";
  values[ 6 ] = "VCT v1.0";
  values[ 7 ] = "Pi-C700";
  values[ 8 ] = "Raspberry Pi";
  values[ 10 ] = "F51B2G6NS3";
}

void genVls()
{
  int n;
  char c;
  string text = "";

  for(int i = 0; i < 18; i++)
  {
    n = rand() % 100;
     if((i == 3) || (i == 7) || (i == 11) || (i == 15))
          text.append("-");
     else{
       std::stringstream ss;
       ss << n;
          text.append(ss.str());
     }
  }
   values[ 1 ] = text;
   text ="";

    int n1 = rand() % 10;
    int n2 = rand() % 10;
    int n3 = rand() % 10;
    std::stringstream ss;
    ss << "192.168." << n1 << "." << n2 << "" << n3;
    values[ 9 ] = ss.str();
}

void Properties::build()
{
  c_names();
  genVls();
}

string get(string name)
{
  for(int i = 0; i < NUM_PROPERTIES; i++){
       if(name == names[i])
           return values[i];
  }
  return "!exists";
}

string Properties::GetProperty(string name)
{
   return get(name);
}

int Properties::good()
{
  return 100;
}

int Properties::bad()
{
  return -819;
}

int Properties::SetProperty(string property, string value)
{
   if(property == "IP")
       values[ 9 ] = value;
   else if(property == "Serial #")
        values[ 1 ] = value;
   else if(property == "RSID-Fingerprint")
        values[ 0 ] = value;
   else {
       p_log.v("System","Err property [" + property + "] does not exist!");
     return bad();
   }
     return good();
}

void Properties::list()
{
   string _names = "";
   for(int i = 0; i < NUM_PROPERTIES; i++){
       stringstream ss;
       ss << ":\t" << names[i] << "\t" << values[i] << "\n";
       _names = ss.str();
       cout << _names;
   }
}

string Properties::s_list()
{

}

void Properties::PropertyNames()
{
  string _names = "";
  for(int i = 0; i < NUM_PROPERTIES; i++){
        stringstream ss;
        ss << ":\t" << names[i] << "\n";
        _names = ss.str();
        cout << _names;
  }
}
