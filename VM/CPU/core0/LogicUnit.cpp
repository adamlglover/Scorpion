/*
* Copyright 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/
#include "core0.h"
#include "cpuf.h"
#include "runtime_exception.h"
#include <sstream>

long _xor(int,int);
long _or(int,int);
long _and(int,int);
long _not(int);
long _nand(int,int);
long _nor(int,int);
long _xnor(int,int);

long _xor(int a, int b)
{
    if((_and(_not(a),b)) || (_and(a,_not(b))))
       return 1;
    else
       return 0;
}

long _or(int a, int b)
{
    if((a == 1) || (b == 1))
      return 1;
    else
      return 0;
}

long _and(int a, int b)
{
  if(a == b)
     return 1;
  else
     return 0;
}

long _not(int a)
{
   if(a == 1)
      return 0;
   else
      return 1;
}


long _nand(int a, int b)
{
    if(_and(a,b))
        return 0;
    else
        return 1;
}

long _nor(int a,int b)
{
   if(_or(a,b))
       return 0;
   else
       return 1;
}

long _xnor(int a, int b)
{
   if(_xor(a,b))
      return 0;
   else
      return 1;
}

int ibool(long num)
{
     if((num == 1) || (num == 0))
        return num;
     else if(num > 1)
        return 1;
     else
        return 0;
}


void nand_l(double *pkg)
{
   if(pkg[0] == 20)
       EAX = _nand(ibool(pkg[1]),ibool(pkg[2]));
   else
   {
       reg_check_set( pkg[0], _nand(ibool(reg_check_ret(pkg[1])),ibool(reg_check_ret(pkg[2]))));
   }
}

void nor_l(double *pkg)
{
   if(pkg[0] == 20)
     EAX = _nor(ibool(pkg[1]),ibool(pkg[2]));
   else
   {
       reg_check_set(pkg[0], _nor(ibool(reg_check_ret(pkg[1])),ibool(reg_check_ret(pkg[2]))));
   }
}

void xnor_l(double *pkg)
{
   if(pkg[0] == 20)
       EAX = _xnor(ibool(pkg[1]),ibool(pkg[2]));
   else 
   {
       reg_check_set(pkg[0], _xnor(ibool(reg_check_ret( pkg[1])),ibool(reg_check_ret( pkg[2]))));
   }
}

void and_l(double *pkg)
{
   if(pkg[0] == 20)
      EAX = _and(ibool(pkg[1]),ibool(pkg[2]));
   else
   {
      reg_check_set( pkg[0], _and(ibool(reg_check_ret(pkg[1])),ibool(reg_check_ret(pkg[2]))));
   }
}

void or_l(double *pkg)
{
   if(pkg[0] == 20)
     EAX = _or(ibool(pkg[1]),ibool(pkg[2]));
   else
   {
      reg_check_set( pkg[0], _or(ibool(reg_check_ret( pkg[1])),ibool(reg_check_ret( pkg[2]))));
   }
}

void xor_l(double *pkg)
{
   if(pkg[0] == 20)
      EAX = _xor(ibool(pkg[1]),ibool(pkg[2]));
   else 
   {
       reg_check_set(pkg[0], _xor(ibool(reg_check_ret(pkg[1])),ibool(reg_check_ret(pkg[2]))));
   }
}

void not_l(double *pkg)
{
   if(pkg[0] == 20)
      EAX = _not(ibool(pkg[1]));
   else
   {
        reg_check_set( pkg[0], _not(ibool(reg_check_ret(pkg[0]))));
   }
}
