#include "thread.h"
#include "../CPU/core0/runtime_excpetion.h"
#include "../CPU/core0/core0.h"
#include <iostream>
#include <stringstream>
#include <string>
using namespace std;

#define THREAD_STACK_SIZE (64 * 1024)
thread t_stack[ THREAD_STACK_SIZE ];

long Thread::TSP = -1;
long Thread::t_size = 0;
int Thread::max_t = 5000;

#define CREATED 0x000
#define RUNNING 0x001
#define PAUSED 0x002
#define WAITING 0x003
#define TERMINATED 0x004

void Thread::add()
{
  RuntimeException re;
  Thread::t_size++;
  if(!(Thread::t_size < THREAD_STACK_SIZE))
   re.introduce("ThreadStackOverloadException", "There are too many active threads running on the VM at a time. t_size > 65536");
  t_stack[ Thread::t_size - 1 ].state = CREATED;
  t_stack[ Thread::t_size - 1 ].ticks = 0;
  t_stack[ Thread::t_size - 1 ].IPos = IP;
}

bool first_t = true;// are we starting the first thread?
void Thread::t_start(long t)
{
   RuntimeException re;
   long tmp = Thread::TSP;
   Thread::TSP = t;
   if((Thread::TSP > Thread::t_size) || (Thread::TSP < 0)){
        stringstream ss;
		ss << Thread::TSP;
        re.introduce("ThreadNotFoundException", "Could not start the thread at the stack location(" + ss.str() + ")");
   }
    if(!first_t){
      // save prev. thread data
	  t_stack[ tmp ].IPos = IP;
	  t_stack[ tmp ].state = WAITING;
	}
	else
	   first_t = false;
	  // start thread
      t_stack[ Thread::TSP ].state = RUNNING;
      IP = t_stack[ Thread::TSP ].IPos;
}

void Thread::t_pause(long t)
{
   RuntimeException re;
   long tmp = Thread::TSP;
   Thread::TSP = t;
   if((Thread::TSP > Thread::t_size) || (Thread::TSP < 0)){
        stringstream ss;
		ss << Thread::TSP;
        re.introduce("ThreadNotFoundException", "Could not start the thread at the stack location(" + ss.str() + ")");
   }
      t_stack[ Thread::TSP ].state = PAUSED;
	  Thread::TSP = tmp;
	  if(Thread::TSP == t){ // curr_thread --> pause jump to next thread
	     t_stack[ Thread::TSP ].IPos = IP;
	     bool activated = false;
		  while(!activated){ // find next waiting thread
			 Thread::TSP++;
			if(Thread::TSP > Thread::t_size)
			     Thread::TSP = 0;
			if(t_stack[ Thread::TSP ].state == WAITING)
				activated = true;
	        else if((Thread::t_size == 1))
		    {
				Thread::TSP = 0;
				t_stack[ Thread::TSP ].state = RUNNING; // run main thread 0
				activated = true;
			}
		  }
         IP = t_stack[ Thread::TSP ].IPos;
	  }
}

void Thread::t_wait(long t)
{
   RuntimeException re;
   long tmp = Thread::TSP;
   Thread::TSP = t;
   if((Thread::TSP > Thread::t_size) || (Thread::TSP < 0)){
        stringstream ss;
		ss << Thread::TSP;
        re.introduce("ThreadNotFoundException", "Could not start the thread at the stack location(" + ss.str() + ")");
   }
      t_stack[ Thread::TSP ].state = WAITING;
	  tmp = Thread::TSP;
	  if(Thread::TSP == t){ // curr_thread --> pause jump to next thread
	     t_stack[ Thread::TSP ].IPos = IP;
	     bool activated = false;
		  while(!activated){ // find next waiting thread
			 Thread::TSP++;
			if(Thread::TSP > Thread::t_size)
			     Thread::TSP = 0;
			if(t_stack[ Thread::TSP ].state == WAITING)
				activated = true;
	        else if((Thread::t_size == 1))
		    {
		       Thread::TSP = 0;
	           t_stack[ Thread::TSP ].state = RUNNING; // run main thread 0
	           activated = true;
		    }
		  }
         IP = t_stack[ Thread::TSP ].IPos;
	  }
}

void Thread::remove(long t) // remove thread from stack
{
   if(t == 2302719) // delete all threads
   {
     Thread::t_size = 1; // dosent actually remove them(they will be reassigned anyway)
	 // leave thread 0 alive
   }
   else if((t > Thread::t_size) || (t < 0)){
        stringstream ss;
		ss << t;
        re.introduce("ThreadNotFoundException", "Could not start the thread at the stack location(" + ss.str() + ")");
   }
   else if(t == 0){
       stringstream ss;
	   ss << Thread::TSP;
       re.introduce("MainThreadException", "Could not delete main thread 0");
   }
   else {
     for(int i = t; i < Thread::t_size; i++){
         t_stack[ i ].IPos = t_stack[ i + 1 ].IPos;
		 t_stack[ i ].state = t_stack[ i + 1 ].state;
		 t_stack[ i ].ticks = t_stack[ i + 1 ].ticks;
	 }
	 Thread::t_size--;
   }
   
}

short t_status(int value, long t); // get thread status information
{
    if(((t > Thread::t_size) || (t < 0)) && (value <= 2)){
        stringstream ss;
		ss << t;
        re.introduce("ThreadNotFoundException", "Could not start the thread at the stack location(" + ss.str() + ")");
   }
    switch( value ){
	      case 0:
		     return t_stack[ t ].IPos;
		  break;
		  case 1:
		     return t_stack[ t ].state;
		  break;
		  case 2:
		     return t_stack[ t ].ticks;
		  break;
		  case 3:
		     return THREAD_STACK_SIZE;
		  break;
		  case 4:
		     return Thread::TSP;
		  break;
		  case 5:
		     return Thread::t_size;
		  break;
		  case 6:
		     return Thread::max_t;
		  break;
	}
	return -1;
}	  

void notify()
{
  if(t_stack[ Thread::TSP ].ticks > max_t){
      t_stack[ Thread::TSP ].IPos = IP;
	  t_stack[ Thread::TSP ].state = WAITING;
	  t_stack[ Thread::TSP ].ticks = 0;
	  bool activated = false;
	  while(!activated){
         Thread::TSP++;
        if(Thread::TSP > Thread::t_size)
          Thread::TSP = 0;
		if(t_stack[ Thread::TSP ].state == WAITING)
		    activated = true;
	    else if((Thread::t_size == 1))
		{
		   Thread::TSP = 0;
	       t_stack[ Thread::TSP ].state = RUNNING; // run main thread 0
	       activated = true;
		}
	  }
      IP = t_stack[ Thread::TSP ].IPos;
  }
  else
    t_stack[ Thread::TSP ].ticks++;
}

