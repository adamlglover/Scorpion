#include "math.h"
#include "core0.h"
#include "cpuf.h"
#include "../../Log/Log.h"
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

long _char(long);
void add(double *pkg)
{
  if(pkg[0] == 20)
       EAX = pkg[1] + pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         core0.setr(0, pkg[0], core0.getr(0, pkg[1]) + core0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         core0.setr(0, pkg[0], ((float) core0.getr(0, pkg[1]) + core0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) + core0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         core0.setr(0, pkg[0], ((int) core0.getr(0, pkg[1]) + core0.getr(0, pkg[2])));
      else // int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) + core0.getr(0, pkg[2])));
   }
}

void sr(double *pkg)
{
   if(pkg[0] == 20)
       EAX = EAX >> (long) SDX;
   else {
       if(I1 == INT){
         long right = (long) core0.getr(1, pkg[0]) >> (short) SDX;
         core0.setr(0, pkg[0], right);
       }
       else if(I1 == SHORT){
         int right = (int) core0.getr(1, pkg[0]) >> (short) SDX;
         core0.setr(0, pkg[0], right);
       }
       else {
         long right = (long) core0.getr(1, pkg[0]) >> (short) SDX;
         core0.setr(0, pkg[0], right);
       }
   }
}

void sl(double *pkg)
{
   if(pkg[0] == 20)
       EAX = EAX << (long) SDX;
   else {
       if(I1 == INT){
         long right = (long) core0.getr(1, pkg[0]) << (short) SDX;
         core0.setr(0, pkg[0], right);
       }
       else if(I1 == SHORT){
         int right = (int) core0.getr(1, pkg[0]) << (short) SDX;
         core0.setr(0, pkg[0], right);
       }
       else {
         long right = (long) core0.getr(1, pkg[0]) << (short) SDX;
         core0.setr(0, pkg[0], right);
       }
   }
}

void rdtsc() // Read Time Stamp Counter
{
   EAX = t_clock.ticks; // store total clock ticks since last startup
}

void cpuid()
{
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

void rand_1(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[1] > 5)
     core0.setr(0, pkg[0], _catch(rand1(pkg[1]) - offset));
  else
     core0.setr(0, pkg[0], _catch(rand1(pkg[1])));
}

void rand_2(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[1] > 5)
     core0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2]) - offset));
  else
     core0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2])));
}

void rand_3(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[1] > 5)
     core0.setr(0, pkg[0], _catch(rand3(pkg[1]) - offset));
  else
     core0.setr(0, pkg[0], _catch(rand3(pkg[1])));
}

void sub(double *pkg)
{
   if(pkg[0] == 20)
       EAX = pkg[1] - pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         core0.setr(0, pkg[0], core0.getr(0, pkg[1]) - core0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         core0.setr(0, pkg[0], ((float) core0.getr(0, pkg[1]) - core0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) - core0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         core0.setr(0, pkg[0], ((int) core0.getr(0, pkg[1]) - core0.getr(0, pkg[2])));
      else // int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) - core0.getr(0, pkg[2])));
   }
}

void inc(double *pkg)
{
    if(pkg[0] == 20)
       EAX++;
   else
    {
       core0.setr(0, pkg[0], (core0.getr(0, pkg[0]) + 1));
    }
}

void dec(double *pkg)
{
   if(pkg[0] == 20)
       EAX--;
   else
    {
       core0.setr(0, pkg[0], (core0.getr(0, pkg[0]) - 1));
    }
}

void mult(double *pkg)
{
   if(pkg[0] == 20)
       EAX = pkg[1] * pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         core0.setr(0, pkg[0], core0.getr(0, pkg[1]) * core0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         core0.setr(0, pkg[0], ((float) core0.getr(0, pkg[1]) * core0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) * core0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         core0.setr(0, pkg[0], ((int) core0.getr(0, pkg[1]) * core0.getr(0, pkg[2])));
      else // int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) * core0.getr(0, pkg[2])));
   }
}

void div(double *pkg)
{
   if(pkg[0] == 20)
       EAX = pkg[1] / pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         core0.setr(0, pkg[0], core0.getr(0, pkg[1]) / core0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         core0.setr(0, pkg[0], ((float) core0.getr(0, pkg[1]) / core0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) / core0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         core0.setr(0, pkg[0], ((int) core0.getr(0, pkg[1]) / core0.getr(0, pkg[2])));
      else // int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) / core0.getr(0, pkg[2])));
   }
}

void rem(double *pkg)
{
   if(pkg[0] == 20)
       EAX = ((long) pkg[1]) % ((long) pkg[2]);
   else
   {
      if(I1 == DOUBLE)// double addition
         core0.setr(0, pkg[0], fmod(core0.getr(0, pkg[1]), core0.getr(0, pkg[2])));
      else if(I1 == FLOAT)// float addition
         core0.setr(0, pkg[0], fmod(core0.getr(0, pkg[1]), core0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) % (long) core0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         core0.setr(0, pkg[0], ((int) core0.getr(0, pkg[1]) % (int) core0.getr(0, pkg[2])));
      else // int addition
         core0.setr(0, pkg[0], ((long) core0.getr(0, pkg[1]) % (long) core0.getr(0, pkg[2])));
   }
}
