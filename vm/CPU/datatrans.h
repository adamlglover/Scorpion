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

#endif
