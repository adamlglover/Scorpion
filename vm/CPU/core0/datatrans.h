#ifndef DATA_TRANS
#define DATA_TRANS

void loadi(double *pkg);
void loadbl(double *pkg);
void loadc(double *pkg);
void dload(double *pkg);
void loadr(double *pkg);
void mv(double *pkg);
void mov(double *pkg);
void rmov(double *pkg);
void _init(double *pkg);
void rm(double *pkg);
void func(double *pkg);
void push(double *pkg);
void _return(double *pkg);
void call(double *pkg);
void swp(double *pkg);
void eof(double *pkg);
void loop(double *pkg);
void rloop(double *pkg);
void end();
void endl(double *pkg);
void _do(double *pkg);
void ilt(double *pkg);
void igt(double *pkg);
void iltoeq(double *pkg);
void igtoeq(double *pkg);
void ndo(double *pkg);
void inlt(double *pkg);
void ingt(double *pkg);
void inltoeq(double *pkg);
void ingtoeq(double *pkg);
void neg(double *pkg);
void mlock(double *pkg);
void lock(double *pkg);
void mulock(double *pkg);
void ulock(double *pkg);
void xreg(double *pkg);
void clx(double *pkg);
void wloop(double *pkg);
void endwl(double *pkg);
void _port(double *pkg);
void same(double *pkg);
void r_mv(double *pkg);
void rflush();
void _print(double *pkg);
void _printf(double *pkg);

#endif
