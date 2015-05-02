#ifndef DATA_TRANS
#define DATA_TRANS

void loadi(double *pkg);
void loadbl(double *pkg);
void loadc(double *pkg);
void dload(double *pkg);
void mov(double *pkg);
void rmov(double *pkg);
void invoke(double *pkg);
void push(double *pkg);
void _return(double *pkg);
void call(double *pkg);
void swp(double *pkg);
void loop(double *pkg);
void rloop(double *pkg);
void end();
void endl(double *pkg);
void _do(double *pkg);
void ilt(double *pkg);
void igt(double *pkg);
void ile(double *pkg);
void ige(double *pkg);
void ndo(double *pkg);
void inlt(double *pkg);
void ingt(double *pkg);
void inle(double *pkg);
void inge(double *pkg);
void neg(double *pkg);
void lock(double *pkg);
void ulock(double *pkg);
void xreg(double *pkg);
void clx(double *pkg);
void wloop(double *pkg);
void endwl(double *pkg);
void same(double *pkg);
void r_mv(double *pkg);
void _print(double *pkg);
void _printf(double *pkg);
void t_cast(double *pkg);
void rln(double *pkg);
void sload(double *pkg);
void loadf(double *pkg);
void rload(double *pkg);
void ct_int(double *pkg);
void anum(double *pkg);
void _sleep(double *pkg);
void c_update();
void cp(double *pkg);
void _string(double *pkg);
void adr(double *pkg);
void r_load(double *pkg);

#endif
