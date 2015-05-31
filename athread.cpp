/*
* Copyright 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
* athread.cpp
* Non concurrent threading
*
* The Scorpion VM supports 2
* unique types of threading.
*
* NON_CONCURRENT
* non concurrent threading gives
* the end user the issusion of multitasking
* as you would expect from true
* multiprocessing.
*
* athread provides multithreading that
* is directly tied to the Scorpion
* VM's processor architecture.
*
* CONCURRENT
* concurrent threading is multithreading that
* is not controlled and handeled by the
* Scorpion VM directly, but by the physical
* microprocessor that Scorpion runs on.
*
* pthread does not provide multithreading that
* is directly tied to the Scorpion
* VM's processor architecture.
*
*/
#define maxThreads 64 * (1024)
#define mainThreadId 1

#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#ifndef NC_THREAD_STATES

  #define THREAD_STATE_ZOMBIE 0x00000

  #define THREAD_STATE_ACTIVE 0x00001

  #define THREAD_STATE_PAUSED 0x00002

  #define THREAD_STATE_WAITING 0x00003

#endif

     /**
     * The minimum priority that a thread can have.
     */
     int MIN_PRIORITY = 0x000012;

     /**
     * The default priority that is assigned to a thread.
     */
     int NORM_PRIORITY = 0x000037;

     /**
     * The maximum priority that a thread can have.
     */
     int MAX_PRIORITY = 0x000080;


    /**
    * If a thread name is unavailableand already exists.
    */
    int THREAD_NAME_UNAVAILABLE = 0x0000110;

    /**
    * If the specified access base id unknown
    */
    int UNKNOWN_ACCESS_BASE = 0x0000123;

    /**
    * If the sig pipe is blocked, wait until thread
    * is finished. This will be used for async tasks.
    */
    int SIG_PIPE_BLOCKED = 0x00000129;

    /**
    * If the sig pipe is open, wait until thread
    * is finished
    */
    int SIG_PIPE_OPEN = 0x00000142;

struct athread {
   long threadId;
   const char *name;
   long stackSize;
   int threadStatus;
   long cap;
   long priority;

} ;

athread threadPages[ maxThreads ];
bool isBorn = false;
long threadPtr = -1;
long pageFramePtr = 0;
int sigPipe = SIG_PIPE_BLOCKED;
long pages = 0;

bool threadExists;
long threadCap;
long threadStackSize;

#define nullptr ((void *)0)
int init(string threadName, long stacksize, long tCap);
bool available(string tName);
void start0();

const char currentThread(){ return threadPages[ threadPtr ].name; }

int getSigPipe(){ return sigPipe; }

void blockSigPipe() { sigPipe = SIG_PIPE_BLOCKED; }

void openSigPipe(){ sigPipe = SIG_PIPE_OPEN; }

bool thread_exists(){ return threadExists; }

long getPageSize(){ return pages; }

long getFramePtr(){ return pageFramePtr; }

long getThreadCap(){ return threadCap; }

long getStackSize(){ return threadStackSize; }

void setThreadCap(long cap){ threadCap = cap; }

void setStackSize(long s_size){ threadStackSize = s_size; }


void yield(){

} // shift to next thread

/* For autonumbering anonymous threads. */
int threadInitNumber = 0;
int nextThreadNum() {
  return threadInitNumber++;
}

void AThread(long size, long cap) {
   stringstream ss;
   ss << nextThreadNum();
   init("Thread-" + ss.str(), size, cap);
}

long getId(string tName)
{
   for(long i = 1; i < getPageSize; i++)
   {
      if(threadPages[ i ].name == tName.c_str())
      {
         threadExists = true;
         return threadPages[ i ].threadId;
      }
   }
  return -1;
}

void setFramePtr(string tName)
{
     for(long i = 1; i < getPageSize(); i++)
   {
      if(threadPages[ i ].name == tName.c_str())
         pageFramePtr = i;
   }
}

int init(string threadName, long stacksize, long tCap)
{
  if(threadName == nullptr){
     RuntimeException re;
     re.introduce("NullPointerException", "name cannot be null");
  }

  if(!isBorn){
     RuntimeException re;
     re.introduce("NullPointerException", "main thread not started");
  }

  threadPtr++;
  if(threadPtr >= maxThreads){
    RuntimeException re;
    re.introduce("ScorpionOutOfMemoryError","the max limit of athreads has been reached");
  }

  if(!available(threadname))
     return THREAD_NAME_UNAVAILABLE;

  pages++;
  threadPages[ threadPtr ].threadId = pages;
  threadPages[ threadPtr ].name = threadName.c_str();
  
  threadPages[ threadPtr ].stackSize = stacksize;
  threadPages[ threadPtr ].cap = tCap;
  threadPages[ threadPtr ].accessBaseControl;
  threadPages[ threadPtr ].priority = MAX_PRIORITY;
  threadPages[ threadPtr ].threadStatus = THREAD_STATE_ZOMBIE;
}

bool available(string tName)
{
   if(tName == "_start") // main thread
    return false;

   for(long i = 1; i < maxThreads; i++)
   {
      if(threadPages[ threadPtr ].name == tName.c_str())
        return false;
   }
  return true;
}

void run(string thread)
{
   long tId = getId(thread); // used to test thread's existance
   if(!thread_exists())
   {
     RuntimeException re;
     stringstream ss;
     ss << thread;
     re.introduce("ThreadNotFoundException", "thread " + ss.str() + " does not exists.");
   }
  
   threadExists = false;
   setFramePtr(thread);
   setStackSize(threadPages[ pageFramePtr ].stackSize);
   setThreadCap(threadPages[ pageFramePtr ].cap);
} // rest of thread processing will be handled by the Scorpion VM's processor

void start0()
{
  if(isBorn){
     RuntimeException re;
     re.introduce("IllegalStateException","main thread has already started");
  }

  isBorn = true;

  Ram rm;
  init("_start", rm.info(5), 0);
  run("_start");
}

void aThreadExit()
{
  blockSigPipe();
  
}

void start()
{
   start0;
}

