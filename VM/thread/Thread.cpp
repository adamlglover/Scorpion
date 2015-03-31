#include "thread.h"
#include <iostream>
#include "../program.h"
#include "../CPU/cpu.h"
#include "../Sys/clock.h"
private static final int NANOS_PER_MILLI = 1000000;

        /**
         * The thread has been created, but has never been started.
         */
        int NEW = 0x00000;
        /**
         * The thread is running.
         */
        int RUNNING = 0x00001;
        /**
         * The thread is blocked and waiting for a lock.
         */
        int BLOCKED = 0x00002;
        /**
         * The thread is waiting.
         */
        int WAITING = 0x00003;
        /**
         * The thread is waiting for a specified amount of time.
         */
        int TIMED_WAITING = 0x00004;
        /**
         * The thread has been terminated.
         */
        int TERMINATED = 0x00005;

void Thread::Thread()
{
   Thread _thread = new Thread();
   _thread.t.state = NEW;
   _thread.t.id = 1; // will be changed
   _thread.t.waiting = false;

   // prep for elapsed time
   SystemClock newClock;
   stringstream ss;
   ss << "clock" << newClock.numClocks + 1;
   newClock.prep(ss.str(),newClock.INFINATE);

   // assign clock name
   _thread.t.clock = ss.str();

   _thread.t.hasStarted = false;
   int *th = create(_thread);

   if(th[0] == CREATED)
    cout << "Thread #" << th[1] << " created." << endl;
   else if(th[0] == THREAD_FULL)
   {
      EBX = 1;
      cout << "Thread: thread_stack_full err" << endl;
      p_exit();
   }
}

int * create(Thread th)
{
  ThreadManager magager;
  manager.numThreads++;

  return manager.add(th);  // simply add the thread to the thread manager
}

void Thread::wait(Thread th)
{
 // TODO stop thread
}

void Threat::start(Thread th, SystemClock newClock, string name)
{
  // TODO start the thread
  th.t.hasStarted = true;
  th.t.state = RUNNING;
  newCock.begin(name);
}

void Thread::status(Thread thd)
{
  return thd.t.state;
}

void Thread::id(Thread thd)
{
   return thd.t.id;
}

void Thread::pause(int mills)
{
 // TODO pause thread for certain ammount of mills
}

void Thread::destroy(Thread th)
{
  delete th;
}

void Thread::elapsed(Thread thd) /* Get the elapsedtime of the thread */
{  
  SystemClock Clock;
  thd.t.elapsedTime = Clock.time(thd.t.clock);
  return thd.t.elapsedTime;
}
