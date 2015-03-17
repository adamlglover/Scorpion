#ifndef DATA_TRANS
#define DATA_TRANS

void loadi(long *pkg);
void loadbl(long *pkg);
void loadr(long *pkg);
void mv(long *pkg);
void mov(long *pkg);
void rmov(long *pkg);
void _init(long *pkg);
void rm(long *pkg);
void func(long *pkg);
void push(long *pkg);
void _return(long *pkg);
void call(long *pkg);
void swp(long *pkg);
void eof(long *pkg);
void loop(long *pkg);
void rloop(long *pkg);
void end();
void endl(long *pkg);
void _do(long *pkg);
void ilt(long *pkg);
void igt(long *pkg);
void iltoeq(long *pkg);
void igtoeq(long *pkg);
void ndo(long *pkg);
void inlt(long *pkg);
void ingt(long *pkg);
void inltoeq(long *pkg);
void ingtoeq(long *pkg);
void neg(long *pkg);
void mlock(long *pkg);
void lock(long *pkg);
void mulock(long *pkg);
void ulock(long *pkg);
void xreg(long *pkg);
void clx(long *pkg);
void wloop(long *pkg);
void endwl(long *pkg);
void _port(long *pkg);
void same(long *pkg);
void r_mv(long *pkg);
void rflush();
void _print(long *pkg);

#endif
