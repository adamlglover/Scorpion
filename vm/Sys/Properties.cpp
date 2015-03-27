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
long rand1(long lim);
long rand2(long seed, long lim);
long rand3(long lim);

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

  values[ 2 ] = "0.0.1";
  values[ 3 ] = "1";
  values[ 4 ] = "Core";
  values[ 5 ] = "x86 Arm i1-400 CPU";
  values[ 6 ] = "VCT v1.0";
  values[ 7 ] = "Pi-C700";
  values[ 8 ] = "Raspberry Pi VM";
  values[ 10 ] = "F51B2G6NS3";
}

long genRand(long range)
{
  long seed,n1,n2,n3,num;
  
  for (int i = 0; i < rand2(rand2(rand(9), rand1(100)), rand1(100); i++)
      seed = rand2(8, range);
  
  for (int i = 0; i < rand2(rand2(rand(9), rand1(100)), rand1(100); i++)
      n1 = rand2(seed, range);
      
  for(int i = 0; i < rand2(rand2(rand(9), rand1(100)), rand1(100); i++)
      n2 = rand2(n1, range);
  
  for(int i = 0; i < rand2(rand2(rand(9), rand1(100)), rand1(100); i++)
      n3 = rand2(n2, range);
      
  num = n3;
  return num;
}

void genVls()
{
  stringstream ss;
  
  ss << "fe." << rand2(6, genRand(120)) << "d7." << "x" << rand1(genRand(10)) << rand2(genRand(8), genRand(100));
  values[ 0 ] = ss.str();
  
  stringstream ss1;
  ss1 << rand2(genRand(8), genRand(1000000)) << "-" << rand2(genRand(8), genRand(1000000)) << "-" << rand2(genRand(8), genRand(1000000)) << "-" << rand2(genRand(8), genRand(1000000)) << "-" << rand2(genRand(8), genRand(1000000));
  values[ 1 ] = ss1.str();

  stringstream ss2;
  ss2 << "192.168.1." << rand2(genRand(10), genRand(100));
  values[ 9 ] = ss2.str();
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
       p_log.v("System","Err cannot modify property [" + property + "]");
     return bad();
   }
     return good();
}

void Properties::list()
{
   string prop = "";
   for(int i = 0; i < NUM_PROPERTIES; i++){
       stringstream ss;
       ss << "   " << names[i] << "   " << values[i] << "\n";
       prop = ss.str();
       cout << prop;
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
