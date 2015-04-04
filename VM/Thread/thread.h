#ifndef VM_THREAD
#define VM_THREAD

#define THREAD_STACK_SIZE (64 * 1024)
extern long t_stack[ THREAD_STACK_SIZE ]; // create a thread stack

class Thread {
    public:
      static long TSP; // thread stack pointer
      static long t_size; // the current # of running threads
      static int max_t; // the max ammount of executable instructions/thread
      static int ticks; // the current ammount of ticksin each thread
      void notify(long ticks); // shift to next thread if ticks > max_t
};

#endif
