#ifndef RAM
#define RAM

class Ram {
     public:
       static long CB;
       static short CS;
       int addr(long);
       int cell(short);
       double data(double);
       long info(int);

};

#endif 
