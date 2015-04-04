#include "thread.h"
#include "../CPU/core0/runtime_excpetion.h"
#include "../CPU/core0/core0.h"
#include <iostream>
using namespace std;

#define THREAD_STACK_SIZE (64 * 1024)
long t_stack[ THREAD_STACK_SIZE ];
long t_state[ THREAD_STACK_SIZE ];

long Thread::TSP = -1;
long Thread::t_size = 0;
int Thread::max_t = 5000;
int Thread::int ticks = 0;

#define CREATED 0x000
#define RUNNING 0x001
#define PAUSED 0x002
#define TERMINATED 0x003

void add()
{
  RuntimeException re;
  t_size++;
  if(t_size > THREAD_STACK_SIZE)
   re.introduce("OutOfMemoryError", "There are too many active threads running on the VM at a time. t_size > 65536");
  t_state[ t_size - 1 ] = CREATED;
}

void notify()
{
  if(ticks > max_t){
      t_stack[ TSP ] = IP;
      TSP++;
      if(TSP > t_size)
        TSP = 0;
      IP = t_stack[ TSP ];
      ticks = 0;
  }
  else
    ticks++;
}

