#include "math.h"
#include "core0.h"
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
