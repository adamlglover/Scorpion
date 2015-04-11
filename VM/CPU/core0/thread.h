#ifndef THREAD
#define THREAD

struct thread_map {
     long ip_h;
     long ip_l;
     short state;
     long ip;
     int ticks;
} ;
#define THREAD_SIZE (64 * 1024)
extern thread_map thread[ THREAD_SIZE ];
extern unsigned long THREAD_MTS;
extern unsigned long THREAD_SP;
extern unsigned long THREAD_SZ;

class Thread {
      public:
	long create(long high, long low);
        long start(long index);
	long stop(long index);
        long wait(long index);
	long destroy(long index);
	void notify();
        long stack_pointer();
        long thread_size();
	long max_ticks();
	long status(long index, int value);

};

#endif
