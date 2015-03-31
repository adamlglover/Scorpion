#ifndef THREAD
#define THREAD

class Thread {
    public:
      Thread();
      void elapsed();
        struct Info {
           int state;
           int id;
           bool waiting;
           long elapsedTime; /* time in mills */
           bool hasStarted;
           string clock;
        } ;

};

#endif
