#include "runtime.h"
#include "cpu.h"
#include <sstream>
#include "cpuf.h"
#include "../Log/Log.h"
#include "runtime_exception.h"
#include "../program.h"
using namespace std;

void checkreg(long _register)
{
   if(_register <= REG_SIZE){}
   else {
    stringstream ss;
    ss << _register;
    Log logg;
    logg.v("System","cpu loigc err: register *^" + ss.str() + " does not exist!");
    EBX = 1;
    p_exit();
   }
}

RuntimeException excpn;

void checktype(long type, long data, long desiredType)
{
  if(type == IC)
  {
    if((data <= 65056) && (data >= -65057)){}
    else {
     stringstream ss;
     ss << data;
     excpn.introduce("NumberOutOfBoundsException","The decimal value " + 
                            ss.str() + " exceeds the bounds of the type int variable.\nShutting Down VM.");
    }
  }
  else if(type == SC)
  {
    if((data <= 35056) && (data >= -35057)){}
    else {
     stringstream ss;
     ss << data;
     excpn.introduce("NumberOutOfBoundsException","The decimal value " +
                            ss.str() + " exceeds the bounds of the type short variable.\nShutting Down VM.");
    }
  }
  else if(type == LC)
  {
    if((data <= 9998096) && (data >= -9998097)){}
    else {
     stringstream ss;
     ss << data;
     excpn.introduce("NumberOutOfBoundsException","The decimal value " +
                            ss.str() + " exceeds the bounds of the type long variable.\nShutting Down VM.");
    }
  }
  else if(type == BC)
  {
   if((data == 1) || (data == 0)){}
    else {
     stringstream ss;
     ss << data;
     excpn.introduce("BoolNotSatisfiedException","The data value " +
                            ss.str() + " is not a boolean variable.\nShutting Down VM.");
    }
  }
   else if(type == CC)
  {
   if((data >= 0) && (data <= 227)){}
    else {
     stringstream ss;
     ss << data;
     excpn.introduce("CharOutOfBoundsException","The char value " +
                            ss.str() + " is is out of the range of the ascii code list.\nShutting Down VM.");
    }
  }
  else if(type == 0){
   CPU cpu_; 
    cpu_.SetFlag( desiredType );
    checktype(desiredType,data,0);
  }
  else if(type != 0){
     stringstream ss;
     ss << type;
     excpn.introduce("TypeNotFoundException","The requested type " + ss.str() + " does not exist!\nShutting Down VM.");
  }
}
