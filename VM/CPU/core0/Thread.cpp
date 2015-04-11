#include "thread.h"
#include "core0.h"
#include "runtime_exception.h"
#include <iostream>
using namespace std;

#define TMAX (64 * 1024)
thread_map thread[ TMAX ]; // thread stack

bool first_thread = true;
unsigned long THREAD_MTS = 9000; // 9000 instructions/session
unsigned long THREAD_SP = -1; // begin at main thread
unsigned long THREAD_SZ = 0; // # of threads

void nextThread();

/* THREAD STATES */
#define CREATED    19
#define ACTIVE     20
#define WAITING    21
#define STOPPED    22
#define TERMINATED 23

long Thread::create(long high, long low)
{
  RuntimeException re;
  THREAD_SZ++;
  if(THREAD_SZ > TMAX)
    re.introduce("StackOverflowExcption", "there are too many running threads");
  /* Create Thread */
  thread[ THREAD_SZ - 1 ].ip_h = high;
  thread[ THREAD_SZ - 1 ].ip_l = low;
  thread[ THREAD_SZ - 1 ].state = CREATED;
  thread[ THREAD_SZ - 1 ].ip = high; // start thread at start of instruction stack
  thread[ THREAD_SZ - 1 ].ticks = 0;
 
 return THREAD_SZ - 1; // return thread number
}

long Thread::start(long index)
{
  cout << "starting thread " << index << endl;
  RuntimeException re;
  if(!(index < THREAD_SZ))
    re.introduce("ThreadIndexOutOfBoundsException", "index > thread_size");
  if(thread[ index ].state == THREAD_SP)
     return 3; //  thread already active
  /* Start thread */
  if(first_thread){
     THREAD_SP = index;
     thread[ THREAD_SP ].state = ACTIVE;
     IP = thread[ THREAD_SP ].ip;
     IPH = thread[ THREAD_SP ].ip_h;
     IPL = thread[ THREAD_SP ].ip_l;
     first_thread = false; 
  }
  else {
    // save current thread state
    thread[ THREAD_SP ].ip = IP;
    thread[ THREAD_SP ].state = WAITING;

    // start thread
    THREAD_SP = index;
    thread[ THREAD_SP ].state = ACTIVE;
    IP = thread[ THREAD_SP ].ip;
    IPH = thread[ THREAD_SP ].ip_h;
    IPL = thread[ THREAD_SP ].ip_l;
  }
  return 0;
}

long Thread::wait(long index)
{
  cout << "waiting thread " << index << endl;
  RuntimeException re;
  if(!(index < THREAD_SZ))
     re.introduce("ThreadIndexOutOfBoundsException", "index > thread_size");
  if(index == THREAD_SP)
    nextThread();
  else
    thread[ index ].state = WAITING;
 return 0;
}

void nextThread()
{
    for(long i = THREAD_SP; i < THREAD_SZ; i++){
       if(thread[ i ].state == WAITING){
          Thread t;
          t.start(i);
       }
       if((i + 1) > THREAD_SZ)
          i = 0; // loop back around
    }
}

long Thread::stop(long index)
{
   cout << "stoppig thread " << index << endl;
   RuntimeException re;
   if(!(index < THREAD_SZ))
      re.introduce("ThreadIndexOutOfBoundsException", "index > thread_size");
   if(index == THREAD_SP){ // are we stopping the current thread?
    nextThread(); // search for next thread
    thread[ index ].state = STOPPED;
   }
   else
    thread[ index ].state = STOPPED;
   return 0;
}

long Thread::destroy(long index)
{
  cout << "destroying thread " << index << endl;
  RuntimeException re;
  if(!(index < THREAD_SZ))
    re.introduce("ThreadIndexOutOfBoundsException", "index > thread_size");
  if(index == 0)
    return -1; // cannot destroy main thread
  if(index == THREAD_SP) // are we destroying the current thread?
    return -2; // thread must be stopped first
  if(thread[ index ].state == STOPPED){ // destroy thread
      for(long i = index; i <= THREAD_SZ; i++){
           thread[ i ].state = thread[ i + 1 ].state;
           thread[ i ].ip_h  = thread[ i + 1 ].ip_h;
           thread[ i ].ip_l  = thread[ i + 1 ].ip_l;
           thread[ i ].ip    = thread[ i + 1 ].ip;
	   thread[ i ].ticks = thread[ i + 1 ].ticks;
      }
     THREAD_SZ--;
  }
  else
   return -3; // thread must be stopped first

   return 0;
}

void Thread::notify() // notify Thread about current running thread state
{
  if(IP > thread[ THREAD_SP ].ip_l) // is the thread finished running?
  {
     long t_finished = THREAD_SP;
     Thread t;
     t.stop(t_finished);
     t.destroy(t_finished);
  }
  else{
     if(thread[ THREAD_SP ].ticks > THREAD_MTS){
        thread[ THREAD_SP ].ticks = 0;
        nextThread(); // jump to next thread
     }
     else
       thread[ THREAD_SP ].ticks++;
  }
}

long Thread::stack_pointer()
{
  return THREAD_SP;
}

long Thread::thread_size()
{
  return THREAD_SZ;
}

long Thread::max_ticks()
{
  return THREAD_MTS;
}

long Thread::status(long index, int value)
{
   if(!(index < THREAD_SZ))
      return TERMINATED;
   switch( value ) {
      case 0:
       return thread[ index ].state;
      break;
      case 1:
       return thread[ index ].ticks;
      break;
      case 2:
       return thread[ index ].ip;
      break;
      case 3:
       return thread[ index ].ip_h;
      break;
      case 4:
       return thread[ index ].ip_l;
      break;
      default:
       return -1; // unknown status value
      break;
   }
}
