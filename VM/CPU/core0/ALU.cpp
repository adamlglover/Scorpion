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
bool calc(int assign_flag, int flag_1, int flag_2)
{
  if((assign_flag == UFUNC) || (assign_flag == MAIN) || (assign_flag == CU) || (assign_flag == FUNC) || 
     (flag_1 == UFUNC) || (flag_1 == MAIN) || (flag_1 == CU) || (flag_1 == FUNC) ||
     (flag_2 == UFUNC) || (flag_2 == MAIN) || (flag_2 == CU) || (flag_2 == FUNC))
    cout << "NotANumberException: cannot +-*/ non-integer types" << endl;
  else if(assign_flag == BOOL){
     cout << "FloatingPointException: cannot +-*/ type bool" << endl;
  }
  else 
    return true;

   return false;
}

C0 c0;
void add(double *pkg)
{
  if(pkg[0] == 21)
       EAX = pkg[1] + pkg[2];
   else
   {
      if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else { 
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
           c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2])));
      }
   }
}

void sr(double *pkg)
{
       if(pkg[2] == 0)
           EAX = EAX >> (long) pkg[0];
       else {
          if(c0.getr(1, pkg[1]) == INT){
               long right = (long) c0.getr(1, pkg[1]) >> (long) pkg[0];
               c0.setr(0, pkg[1], right);
          }
          else if(c0.getr(1, pkg[1]) == DOUBLE){
                EBX = 2;
                LOGG.w("System", "warning: cannot right shift floating point number");
          }
          else if(c0.getr(1, pkg[1]) == FLOAT){
                EBX = 2;
                LOGG.w("System", "warning: cannot right shift floating point number");
          }
          else if(c0.getr(1, pkg[1]) == SHORT){
               int right = (int) c0.getr(1, pkg[1]) >> (long) pkg[0];
               c0.setr(0, pkg[1], right);
          }
          else if(c0.getr(1, pkg[1]) == CHAR){
               int right = (int) c0.getr(1, pkg[1]) >> (long) pkg[0];
               c0.setr(0, pkg[1], right);
          }
       }
}

void sl(double *pkg)
{
     if(pkg[2] == 0)
       EAX = EAX << (long) pkg[0];
     else {
          if(c0.getr(1, pkg[1]) == INT){
               long right = (long) c0.getr(1, pkg[1]) << (long) pkg[0];
               c0.setr(0, pkg[1], right);
          }
          else if(c0.getr(1, pkg[1]) == DOUBLE){
                EBX = 2;
                LOGG.w("System", "warning: cannot right shift floating point number");
          }
          else if(c0.getr(1, pkg[1]) == FLOAT){
                EBX = 2;
                LOGG.w("System", "warning: cannot right shift floating point number");
          }
          else if(c0.getr(1, pkg[1]) == SHORT){
               int right = (int) c0.getr(1, pkg[1]) << (long) pkg[0];
               c0.setr(0, pkg[1], right);
          }
          else if(c0.getr(1, pkg[1]) == CHAR){
               int right = (int) c0.getr(1, pkg[1]) << (long) pkg[0];
               c0.setr(0, pkg[1], right);
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
  if(pkg[1] > 5){
   if(c0.getr(1, pkg[0]) == OI){
           cout << "TypeErrException: uninitalized variables" << endl;
   }
   else {
      if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
          c0.setr(0, pkg[0], _catch(rand1(pkg[1]) - offset));
   }
  }
  else{
     if((c0.getr(1, pkg[0]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
              c0.setr(0, pkg[0], _catch(rand1(pkg[1])));
     }
  }
}

void rand_2(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[2] > 5){
      if((c0.getr(1, pkg[0]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
               c0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2]) - offset));
      }
  }
  else{
    if((c0.getr(1, pkg[0]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
               c0.setr(0, pkg[0], _catch(rand2(pkg[1], pkg[2])));
     }
  }
}

void rand_3(double *pkg)
{
  double offset = rand() % 4;
  if(pkg[1] > 5){
    if((c0.getr(1, pkg[0]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
                 c0.setr(0, pkg[0], _catch(rand3(pkg[1]) - offset));
      }
  }
  else
    c0.setr(0, pkg[0], _catch(rand3(pkg[1])));
}

void rrand_1(double *pkg)
{
  long offset = rand() % 4;
  if(c0.getr(0, pkg[1]) > 5){
     if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[0])))
                c0.setr(0, pkg[0], _catch(rand3(c0.getr(0, pkg[1])) - offset));
      }
  }
  else{
     if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[0])))
                c0.setr(0, pkg[0], _catch(rand1(c0.getr(0, pkg[1]))));
      }
  }

}

void rrand_2(double *pkg)
{
  long offset = rand() % 4;
  if(c0.getr(0, pkg[2]) > 5){
     if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
           c0.setr(0, pkg[0], _catch(rand2(c0.getr(0, pkg[1]), c0.getr(0, pkg[2])) - offset));
      }
  }
   else{
     if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
               c0.setr(0, pkg[0], _catch(rand2(c0.getr(0, pkg[1]), c0.getr(0, pkg[2]))));
      }
  }
}

void rrand_3(double *pkg)
{
  double offset = rand() % 4;
  if(c0.getr(0, pkg[1]) > 5){
     if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[0])))
                 c0.setr(0, pkg[0], _catch(rand3(c0.getr(0, pkg[1])) - offset));
      }
  }
  else
     c0.setr(0, pkg[0], _catch(rand3(c0.getr(0, pkg[1]))));
}

void sub(double *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] - pkg[2];
   else
   {
      if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
           c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2])));
      }
   } 
}

void inc(double *pkg)
{
    if(pkg[0] == 21)
       EAX++;
   else
    {
       if((c0.getr(1, pkg[0]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
            c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) + 1));
      }
    }
}

void dec(double *pkg)
{
   if(pkg[0] == 21)
       EAX--;
   else
    {
      if((c0.getr(1, pkg[0]) == OI)){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[0])))
               c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) - 1));
      }
    }
}

void mult(double *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] * pkg[2];
   else
   {
       if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
             c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2])));
      }
   }
}

void div(double *pkg)
{
   if(pkg[0] == 21)
       EAX = pkg[1] / pkg[2];
   else
   {
      if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
               c0.setr(0, pkg[0], (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2])));
      }
   }
}

void rem(double *pkg)
{
   if(pkg[0] == 21)
       EAX = ((long) pkg[1]) % ((long) pkg[2]);
   else{
      if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
            c0.setr(0, pkg[0], fmod(c0.getr(0, pkg[1]), c0.getr(0, pkg[2])));
      }
  }
}

void cadd(double *pkg)
{
  if(pkg[0] == 21)
       EAX += pkg[1] + pkg[2];
   else
   {
       if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
              c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) + (c0.getr(0, pkg[1]) + c0.getr(0, pkg[2]))));
      }
   }
}

void csub(double *pkg)
{
   if(pkg[0] == 21)
       EAX -= pkg[1] - pkg[2];
   else
   {
       if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
             c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) - (c0.getr(0, pkg[1]) - c0.getr(0, pkg[2]))));
      }
   }
}

void cmult(double *pkg)
{
   if(pkg[0] == 21)
       EAX *= pkg[1] * pkg[2];
   else
   {
      if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
            c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) * (c0.getr(0, pkg[1]) * c0.getr(0, pkg[2]))));
      }
   }
}

void cdiv(double *pkg)
{
   if(pkg[0] == 21)
       EAX /= pkg[1] / pkg[2];
   else
   {
      if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2])))
              c0.setr(0, pkg[0], (c0.getr(0, pkg[0]) / (c0.getr(0, pkg[1]) / c0.getr(0, pkg[2]))));
      }
   }
}

void crem(double *pkg)
{
   if(pkg[0] == 21)
       EAX %= ((long) pkg[1]) % ((long) pkg[2]);
   else
   {
       if((c0.getr(1, pkg[0]) == OI) || (c0.getr(1, pkg[1]) == OI) || (c0.getr(1, pkg[2]) == OI) ){
           cout << "TypeErrException: uninitalized variables" << endl;
      }
      else {
         if(calc((int) c0.getr(1, pkg[0]),(int) c0.getr(1, pkg[1]),(int) c0.getr(1, pkg[2]))){
               double tmp = c0.getr(0, pkg[0]);
               double x = fmod(c0.getr(0, pkg[1]), c0.getr(0, pkg[2]));
               double y = fmod(tmp, x);
               c0.setr(0, pkg[0], y);
        } 
     }
   }
}
