#include "math.h"
#include "core0.h"
#include <stdlib.h>
#include <sstream>

C0 c0;
void add(long *pkg)
{
  if(pkg[0] == 21)
       EAX = pkg[1] + pkg[2];
   else
   {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
   }
}

void sr(long *pkg)
{
       EAX = EAX >> pkg[0];
}

void sl(long *pkg)
{
       EAX = EAX << pkg[0];
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

long _catch(long num)
{
  if(num < 0)
   return 0;
  else
   return num;
}

long rand1(int lim)
{
        static long a = 100001;
        a = (a * 125) % 2796203;
        return ((a % lim) + 1);
}

long rand2( long seed, int lim)
{
        static long a = seed;  // could be made the seed value
        a = (a * 32719 + 3) % 32749;
        return ((a % lim) + 1);
}

long rand3(int lim)
{
        static long a = 3;
        a = (((a * 214013L + 2531011L) >> 16) & 32767);

        return ((a % lim) + 1);
}

void rand_1(long *pkg)
{
  long offset = rand() % 4;
  if(pkg[1] > 5)
   c0.setr(0, pkg[0], _catch(rand1(pkg[1]) - offset));
  else
   c0.setr(0, pkg[0], _catch(rand1(pkg[1])));
}

void rand_2(long *pkg)
{
  long offset = rand() % 4;
  if(pkg[2] > 5)
    c0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2]) - offset));
  else
    c0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2])));
}

void rand_3(long *pkg)
{
  long offset = rand() % 4;
  if(pkg[1] > 5)
    c0.setr(0, pkg[0], _catch(rand3(pkg[1]) - offset));
  else
    c0.setr(0, pkg[0], _catch(rand3(pkg[1])));
}

void rrand_1(long *pkg)
{
  long offset = rand() % 4;
  if(c0.getr(0, pkg[1]) > 5)
     c0.setr(0, pkg[0], _catch(rand3(c0.getr(0, pkg[1])) - offset));
  else
     c0.setr(0, pkg[0], _catch(rand1(c0.getr(0, pkg[1]))));
}

void rrand_2(long *pkg)
{
  long offset = rand() % 4;
  if(c0.getr(0, pkg[2]) > 5)
     c0.setr(0, pkg[0], _catch(rand2(c0.getr(0, pkg[1]), c0.getr(0, pkg[2])) - offset));
  else
     c0.setr(0, pkg[0], _catch(rand2(c0.getr(0, pkg[1]), c0.getr(0, pkg[2]))));
}

void rrand_3(long *pkg)
{
  long offset = rand() % 4;
  if(c0.getr(0, pkg[0]) > 5)
     c0.setr(0, pkg[0], _catch(rand3(c0.getr(0, pkg[1])) - offset));
  else
     c0.setr(0, pkg[0], _catch(rand3(c0.getr(0, pkg[1]))));
}

void sub(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] - pkg[2];
   else
   {
       c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
   }
}

void inc(long *pkg)
{
    if(pkg[0] == 21)
       EAX++;
   else
    {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) + 1));
    }
}

void dec(long *pkg)
{
   if(pkg[0] == 21)
       EAX--;
   else
    {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) - 1));
    }
}

void mult(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] * pkg[2];
   else
   {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
   }
}

void div(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] / pkg[2];
   else
   {
       c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
   }
}

void rem(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] % pkg[2];
   else{
      c0.setr(0, pkg[0], fmod(c0.getr(0, pkg[1]), c0.getr(0, pkg[2])));
  }
}

void cadd(long *pkg)
{
  if(pkg[0] == 21)
       EAX += pkg[1] + pkg[2];
   else
   {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]))));
   }
}

void csub(long *pkg)
{
   if(pkg[0] == 21)
       EAX -= pkg[1] - pkg[2];
   else
   {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]))));
   }
}

void cmult(long *pkg)
{
   if(pkg[0] == 21)
       EAX *= pkg[1] * pkg[2];
   else
   {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]))));
   }
}

void cdiv(long *pkg)
{
   if(pkg[0] == 21)
       EAX /= pkg[1] / pkg[2];
   else
   {
      c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]))));
   }
}

void crem(long *pkg)
{
   if(pkg[0] == 21)
       EAX %= pkg[1] % pkg[2];
   else
   {
      double tmp = c0.getr(0, pkg[0]);
      double x = fmod(c0.getr(0, pkg[1]), c0.getr(0, pkg[2]));
      double y = fmod(tmp, x);
      c0.setr(0, pkg[0], y);
   }
}
