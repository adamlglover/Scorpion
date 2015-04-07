#include "math.h"
#include "core0.h"
#include "cpuf.h"
#include "../../Log/Log.h"
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

Log LOGG;
long _char(long);
C0 c0;
void add(double *pkg)
{
  if(pkg[0] == 21)
       EAX = pkg[1] + pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
   }
}

void sr(double *pkg)
{
       if(pkg[0] == 21)
           EAX = EAX >> (long) pkg[1];
       else {
          if((I1 == INT){
               long right = (long) c0.getr(1, pkg[0]) >> (short) pkg[1];
               c0.setr(0, pkg[0], right);
          }
          else if(I1 == SHORT){
               int right = (int) c0.getr(1, pkg[0]) >> (short) pkg[1];
               c0.setr(0, pkg[0], right);
          }
          else {
               long right = (long) c0.getr(1, pkg[0]) >> (short) pkg[1];
               c0.setr(0, pkg[0], right);
          }
       }
}

void sl(double *pkg)
{
     if(pkg[0] == 21)
           EAX = EAX << (long) pkg[1];
       else {
          if((I1 == INT){
               long right = (long) c0.getr(1, pkg[0]) << (short) pkg[1];
               c0.setr(0, pkg[0], right);
          }
          else if(I1 == SHORT){
               int right = (int) c0.getr(1, pkg[0]) << (short) pkg[1];
               c0.setr(0, pkg[0], right);
          }
          else {
               long right = (long) c0.getr(1, pkg[0]) << (short) pkg[1];
               c0.setr(0, pkg[0], right);
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
       c0.setr(0, pkg[0], _catch(rand1(pkg[1]) - offset));
  else
      c0.setr(0, pkg[0], _catch(rand1(pkg[1])));
}

void rand_2(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[1] > 5)
     c0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2]) - offset));
  else
     c0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2])));
}

void rand_3(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[1] > 5)
        c0.setr(0, pkg[0], _catch(rand3(pkg[1]) - offset));
  else
        c0.setr(0, pkg[0], _catch(rand3(pkg[1])));
}

void sub(double *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] - pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
   }
}

void inc(double *pkg)
{
    if(pkg[0] == 21)
       EAX++;
   else
    {
            c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) + 1));
    }
}

void dec(double *pkg)
{
   if(pkg[0] == 21)
       EAX--;
   else
    {
               c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) - 1));
    }
}

void mult(double *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] * pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
   }
}

void div(double *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] / pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
   }
}

void rem(double *pkg)
{
   if(pkg[0] == 21)
       EAX = ((long) pkg[1]) % ((long) pkg[2]);
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], fmod(c0.getr(0, pkg[1]), c0.getr(0, pkg[2])));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], fmod(c0.getr(0, pkg[1]), c0.getr(0, pkg[2])));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) % c0.getr(0, pkg[2])));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[1]) % c0.getr(0, pkg[2])));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[1]) % c0.getr(0, pkg[2])));
   }
}

void cadd(double *pkg)
{
  if(pkg[0] == 21)
       EAX += pkg[1] + pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]))));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]))));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]))));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]))));
   }
}

void csub(double *pkg)
{
   if(pkg[0] == 21)
       EAX -= pkg[1] - pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]))));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]))));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]))));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]))));
   }
}

void cmult(double *pkg)
{
   if(pkg[0] == 21)
       EAX *= pkg[1] * pkg[2];
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]))));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]))));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]))));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]))));
   }
}

void cdiv(double *pkg)
{
   if(pkg[0] == 21)
       EAX /= ((long) pkg[1]) / ((long) pkg[2]);
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], ((float) c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]))));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]))));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], ((int) c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]))));
      else // int addition
         c0.setr(0, pkg[0], ((long) c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]))));
   }
}

void crem(double *pkg)
{
   if(pkg[0] == 21)
       EAX %= ((long) pkg[1]) % ((long) pkg[2]);
   else
   {
      if(I1 == DOUBLE)// double addition
         c0.setr(0, pkg[0], fmod(c0.getr(0, pkg[0]), fmod((c0.getr(0, pkg[1]), c0.getr(0, pkg[2])))));
      else if(I1 == FLOAT)// float addition
         c0.setr(0, pkg[0], (float) fmod(c0.getr(0, pkg[0]), fmod((c0.getr(0, pkg[1]), c0.getr(0, pkg[2])))));
      else if(I1 == INT)// int addition
         c0.setr(0, pkg[0], (long) fmod(c0.getr(0, pkg[0]), fmod((c0.getr(0, pkg[1]), c0.getr(0, pkg[2])))));
      else if(I1 == SHORT)// short addition
         c0.setr(0, pkg[0], (int) fmod(c0.getr(0, pkg[0]), fmod((c0.getr(0, pkg[1]), c0.getr(0, pkg[2])))));
      else // int addition
         c0.setr(0, pkg[0], (long) fmod(c0.getr(0, pkg[0]), fmod((c0.getr(0, pkg[1]), c0.getr(0, pkg[2])))));
   }
}
