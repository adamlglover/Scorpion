#include "disassembler.h"
#include <sstream>
#include <string>
#include "../core0/runtime_exception.h"
#include <math.h>
#include <stdlib.h> 
#include <iostream>
using namespace std;

void bin_overload(string binary)
{
   stringstream ss;
   ss << binary.length();
   RuntimeException re;
   re.introduce("BinarySizeOverloadException","max allowable binary instruction is 1020 bits size[" + ss.str() + "]");
}

double binary_decimal(string num) /* Function to convert binary to dec */
{
  double dec = 0, n = 1, exp = 0;
  string bin = num;
  if(bin.length() > 1024)
       bin_overload(bin);
  else {
    /* for(int i = bin.length() - 1; i > -1; i--)
     {
          n = pow(2,exp++);
          if(bin.at(i) == '1')
            dec += n;
     }*/
     dec = strtol(num.c_str(), NULL, 2);
  }
    return dec;
}

string decimal_binary(long num) /* Function to convert dec to binary */
 {
     int number;
     string bin;
     char holder = ' ';
     number = num;
     while(number != 0)
     {
	holder = number % 2 + '0';
        bin = holder + bin;
	number /= 2;
     }

     if(bin.length() > 1024)
       bin_overload(bin);

     return bin;
 }



double Disassembler::disassemble(string data)
{
   return  binary_decimal(data);
}

string Disassembler::assemble(long data)
{
   return decimal_binary(data);
}

