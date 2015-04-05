#ifndef VM_THREAD
#define VM_THREAD

struct thread {
     long IPos;
     int state;
     int ticks;
} ;
#define THREAD_STACK_SIZE (64 * 1024)
extern thread t_stack[ THREAD_STACK_SIZE ]; // create a thread stack

class Thread {
    public:
      static long TSP; // thread stack pointer
      static long t_size; // the current # of running threads
      static int max_t; // the max ammount of executable instructions/thread
      void notify(); // shift to next thread if ticks > max_t
      int t_create(); // add new thread with memory status report
      void t_start(long t);
      void t_pause(long t);
      void t_wait(long t);
      void t_remove(long t); // remove thread from stack
      short t_status(int value, long t);

};

#endif
