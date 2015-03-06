#include "disassembler.h" 
#include <sstream> 
#include <string> 
#include <math.h> 
#include <iostream>
using namespace std;

long binary_decimal(string num) /* Function to convert binary to dec */
{
  long dec = 0, n = 1, exp = 0;
  string bin = num;
  for(int i = bin.length() - 1; i > -1; i--)
  {
     n = pow(2,exp++);
      if(bin.at(i) == '1')
         dec += n;
  }
    return dec;
}

//long decimal_binary(long n)  /* Function to convert decimal to bin */
/*{
    long rem, i=1, binary=0;
    while (n!=0)
    {
        rem=n%2;
        n/=2;
        binary+=rem*i;
        i*=10;
    }
    return binary;
}*/



long Disassemble(string dataset, bool todecimal)
{
  if(todecimal){}
//      return decimal_binary(dataset);
  else
        return binary_decimal(dataset);
}

long Disassembler::disassemble(string data)
{
   return Disassemble(data, false);
}
