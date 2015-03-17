#ifndef ALU
#define ALU

void add(long *pckg);
void sub(long *pckg);
void mult(long *pckg);
void div(long *pckg);
void rem(long *pckg);
void cadd(long *pckg);
void csub(long *pckg);
void cmult(long *pckg);
void cdiv(long *pckg);
void crem(long *pckg);
void inc(long *pckg);
void dec(long *pckg);
void sl(long *pckg);
void sr(long *pckg);
void cpuid();
void rdtsc();
void rand_1(long *pckg);
void rand_2(long *pckg);
void rand_3(long *pckg);
void rrand_1(long *pckg);
void rrand_2(long *pckg);
void rrand_3(long *pckg);

#endif
