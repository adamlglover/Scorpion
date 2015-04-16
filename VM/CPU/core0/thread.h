#ifndef THREAD
#define THREAD

struct thread_map {
     long id;
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
	long create(long id, long high, long low);
        long start(long id);
	long stop(long id);
        long wait(long id);
	long destroy(long id);
	void notify();
        long stack_pointer();
        long thread_size();
	long max_ticks();
	long status(long id, int value);
        void Shutdown();

};

#endif
