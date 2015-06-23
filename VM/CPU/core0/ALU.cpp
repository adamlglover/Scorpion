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
#include "math.h"
#include <math.h>
#include "core0.h"
#include "../../var.h"
#include "cpuf.h"
#include "../../Log/Log.h"
#include "runtime_exception.h"
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

long _char(long);
void add()// add <eax><const><const> | add <reg><mem> | add <mem><reg> | add <reg><reg> | add <reg> <reg><reg> reg_check_ret(
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
  if(p0 == 20)
       EAX = p1 + p2;
   else
   {
      RuntimeException re;
       if((reg_check_ret(p1) == null) && (reg_check_ret(p2) == null))
           re.introduce("NullpointerException", "cannot perform math on null element");

      if(SFC == DOUBLE)// double addition
         reg_check_set( p0, reg_check_ret(p1) + reg_check_ret(p2));
      else if(SFC == FLOAT)// float addition
         reg_check_set(p0, ((float) reg_check_ret(p1) + reg_check_ret(p2)) );
      else if(SFC == INT)// int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) + reg_check_ret(p2) ));
      else if(SFC == SHORT)// short addition
         reg_check_set( p0, ((int) reg_check_ret(p1) + reg_check_ret(p2) ));
      else // int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) + reg_check_ret(p2) ));
   }
}

void sr()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   if(p0 == 20)
       EAX = EAX >> (long) SDX;
   else {
      RuntimeException re;
       if(reg_check_ret(p0) == null)
           re.introduce("NullpointerException", "cannot perform math on null element");

       if(SFC == INT){
         long right = (long) reg_check_ret(p0) >> (short) SDX;
         reg_check_set(p0, right);
       }
       else if(SFC == SHORT){
         int right = (int) reg_check_ret(p0) >> (short) SDX;
         reg_check_set(p0, right);
       }
       else {
         long right = (long) reg_check_ret(p0) >> (short) SDX;
         reg_check_set(p0, right);
       }
   }
}

void sl()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   if(p0 == 20)
       EAX = EAX << (long) SDX;
   else {
        RuntimeException re;
       if(reg_check_ret(p0) == null)
           re.introduce("NullpointerException", "cannot perform math on null element");

        if(SFC == INT){
         long right = (long) reg_check_ret(p0) << (short) SDX;
         reg_check_set(p0, right);
       }
       else if(SFC == SHORT){
         int right = (int) reg_check_ret(p0) << (short) SDX;
         reg_check_set(p0, right);
       }
       else {
         long right = (long) reg_check_ret(p0) << (short) SDX;
         reg_check_set(p0, right);
       }
   }
}

void rdtsc() // Read Time Stamp Counter
{
   IP += 3;
   SDX = cycles; // store total clock ticks since last startup
}

void cpuid()
{
 IP += 3;
  EAX = id[0]; // processor id
  SDX = id[1]; // # of cores
  SFC = id[2]; // IFT
  SCX = id[3]; // Production date
}

long _catch(double num)
{
  if(num < 0)
   return 0;
  else
   return num;
}

long rand1(long lim)
{
   static long a = 100001;
   a = (a * 125) % 2796203;
   return ((a % lim) + 1);
}

long rand2( long seed, long lim)
{
   static long a = seed;  // could be made the seed value
   a = (a * 32719 + 3) % 32749;
   return ((a % lim) + 1);
}

long rand3(long lim)
{
   static long a = 3;
   a = (((a * 214013L + 2531011L) >> 16) & 32767);
   return ((a % lim) + 1);
}

void rand_1()
{
  IP += 3;
  EAX = SDX + 1;
  double offset = rand() % 4;
   while(!(EAX < SDX))
     EAX = _catch(rand1(SDX) - offset);
}

void rand_2()
{
  IP += 3;
  double offset = rand() % 4;
     EAX = _catch(rand2(SDX, SCX) - offset);
}

void rand_3()
{
  IP += 3;
  double offset = rand() % 4;
     EAX =  _catch(rand3(SDX) - offset);
}

void sub()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   if(p0 == 20)
       EAX = p1 - p2;
   else
   {
       RuntimeException re;
       if((reg_check_ret(p1) == null) && (reg_check_ret(p2) == null))
           re.introduce("NullpointerException", "cannot perform math on null element");

       if(SFC == DOUBLE)// double addition
         reg_check_set( p0, reg_check_ret(p1) - reg_check_ret(p2));
      else if(SFC == FLOAT)// float addition
         reg_check_set(p0, ((float) reg_check_ret(p1) - reg_check_ret(p2)) );
      else if(SFC == INT)// int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) - reg_check_ret(p2) ));
      else if(SFC == SHORT)// short addition
         reg_check_set( p0, ((int) reg_check_ret(p1) - reg_check_ret(p2) ));
      else // int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) - reg_check_ret(p2) ));
   }
}

void inc()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
    if(p0 == 20)
       EAX++;
   else
    {
       RuntimeException re;
       if(reg_check_ret(p0) == null)
           re.introduce("NullpointerException", "cannot perform math on null element");

       reg_check_set(p0, (reg_check_ret(p0) + 1));
    }
}

void dec()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   IP++;
   IP++;
   if(p0 == 20)
       EAX--;
   else
    {
       RuntimeException re;
       if(reg_check_ret(p0) == null)
           re.introduce("NullpointerException", "cannot perform math on null element");

       reg_check_set(p0, (reg_check_ret(p0) - 1));
    }
}

void mult()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   if(p0 == 20)
       EAX = p1 * p2;
   else
   {
       RuntimeException re;
       if((reg_check_ret(p1) == null) && (reg_check_ret(p2) == null))
           re.introduce("NullpointerException", "cannot perform math on null element");

       if(SFC == DOUBLE)// double addition
         reg_check_set( p0, reg_check_ret(p1) * reg_check_ret(p2));
      else if(SFC == FLOAT)// float addition
         reg_check_set(p0, ((float) reg_check_ret(p1) * reg_check_ret(p2)) );
      else if(SFC == INT)// int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) * reg_check_ret(p2) ));
      else if(SFC == SHORT)// short addition
         reg_check_set( p0, ((int) reg_check_ret(p1) * reg_check_ret(p2) ));
      else // int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) * reg_check_ret(p2) ));
   }
}

void div()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   if(p0 == 20)
       EAX = p1 / p2;
   else
   {
       RuntimeException re;
       if((reg_check_ret(p1) == 0) && (reg_check_ret(p2) == 0))
           re.introduce("ArithmeticException", "fatal error: / zero");
       if((reg_check_ret(p1) == null) && (reg_check_ret(p2) == null))
           re.introduce("NullpointerException", "cannot perform math on null element");

       if(SFC == DOUBLE)// double addition
         reg_check_set( p0, reg_check_ret(p1) / reg_check_ret(p2));
      else if(SFC == FLOAT)// float addition
         reg_check_set(p0, ((float) reg_check_ret(p1) / reg_check_ret(p2)) );
      else if(SFC == INT)// int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) / reg_check_ret(p2) ));
      else if(SFC == SHORT)// short addition
         reg_check_set( p0, ((int) reg_check_ret(p1) / reg_check_ret(p2) ));
      else // int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) / reg_check_ret(p2) ));
   }
}

void rem()
{
   double p0 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p1 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   double p2 = strtol(prog(2, IP++, "").c_str(), NULL, 2);
   if(p0 == 20)
       EAX = ((long) p1) % ((long) p2);
   else
   {
       RuntimeException re;
       if((reg_check_ret(p1) == 0) && (reg_check_ret(p2) == 0))
           re.introduce("ArithmeticException", "fatal error: / zero");
       if((reg_check_ret(p1) == 1) && (reg_check_ret(p2) == 0))
           reg_check_set( p0, null);
       if((reg_check_ret(p1) == null) && (reg_check_ret(p2) == null))
           re.introduce("NullpointerException", "cannot perform math on null element");
       
       if(SFC == DOUBLE)// double addition
         reg_check_set( p0, fmod(reg_check_ret(p1), reg_check_ret(p2)));
      else if(SFC == FLOAT)// float addition
         reg_check_set(p0, ((float) fmod(reg_check_ret(p1), reg_check_ret(p2))) );
      else if(SFC == INT)// int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) % (long) reg_check_ret(p2) ));
      else if(SFC == SHORT)// short addition
         reg_check_set( p0, ((int) reg_check_ret(p1) % (int) reg_check_ret(p2) ));
      else // int addition
         reg_check_set( p0, ((long) reg_check_ret(p1) % (long) reg_check_ret(p2) ));
  }
}
