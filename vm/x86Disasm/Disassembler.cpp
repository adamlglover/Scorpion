#include "disassembler.h"

long binary_decimal(long n) /* Function to convert binary to dec */
{
  long dec = 0, rem, base = 1;
     while (n > 0)
     {
        rem = n % 10;
        dec = dec + rem * base;
        base = base * 2;
        n = n / 10;
     }
    return dec;
}

long decimal_binary(long n)  /* Function to convert decimal to bin */
{
    long rem, i=1, binary=0;
    while (n!=0)
    {
        rem=n%2;
        n/=2;
        binary+=rem*i;
        i*=10;
    }
    return binary;
}



long Disassemble(long dataset, bool todecimal)
{
  if(todecimal)
      return decimal_binary(dataset);
  else
      return binary_decimal(dataset);
}

long Disassembler::disassemble(long data)
{
   return Disassemble(data, false);
}
