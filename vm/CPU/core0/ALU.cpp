#include "core0.h"
#include <sstream>

C0 c;
void add(long *pkg)
{
  if(pkg[0] == 21)
       EAX = pkg[1] + pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[1]) + c.getr(0, pkg[2])));
   }
}

void sub(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] - pkg[2];
   else
   {
       c.setr(0, pkg[0], (c.getr(0, pkg[1]) - c.getr(0, pkg[2])));
   }
}

void inc(long *pkg)
{
    if(pkg[0] == 21)
       EAX++;
   else
    {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) + 1));
    }
}

void dec(long *pkg)
{
   if(pkg[0] == 21)
       EAX--;
   else
    {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) - 1));
    }
}

void mult(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] * pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[1]) * c.getr(0, pkg[2])));
   }
}

void div(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] / pkg[2];
   else
   {
       c.setr(0, pkg[0], (c.getr(0, pkg[1]) / c.getr(0, pkg[2])));
   }
}

void rem(long *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] % pkg[2];
   else
      c.setr(0, pkg[0], (c.getr(0, pkg[1]) % c.getr(0, pkg[2])));
}

void cadd(long *pkg)
{
  if(pkg[0] == 21)
       EAX += pkg[1] + pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) + (c.getr(0, pkg[1]) + c.getr(0, pkg[2]))));
   }
}

void csub(long *pkg)
{
   if(pkg[0] == 21)
       EAX -= pkg[1] - pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) - (c.getr(0, pkg[1]) - c.getr(0, pkg[2]))));
   }
}

void cmult(long *pkg)
{
   if(pkg[0] == 21)
       EAX *= pkg[1] * pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) * (c.getr(0, pkg[1]) * c.getr(0, pkg[2]))));
   }
}

void cdiv(long *pkg)
{
   if(pkg[0] == 21)
       EAX /= pkg[1] / pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) / (c.getr(0, pkg[1]) / c.getr(0, pkg[2]))));
   }
}

void crem(long *pkg)
{
   if(pkg[0] == 21)
       EAX %= pkg[1] % pkg[2];
   else
   {
      c.setr(0, pkg[0], (c.getr(0, pkg[0]) % (c.getr(0, pkg[1]) % c.getr(0, pkg[2]))));
   }
}
