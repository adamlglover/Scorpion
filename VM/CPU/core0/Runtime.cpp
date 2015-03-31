#include "runtime.h"
#include "core0.h"
#include <sstream>
#include "cpuf.h"
#include "../../Log/Log.h"
#include "runtime_exception.h"
#include "../../program.h"
#include "../../Ram/ram.h"
using namespace std;
Ram _r;
void checkreg(long _register)
{
   if(_register <= _r.info(0)){}
   else {
    stringstream ss;
    ss << _register;
    Log logg;
    logg.v("System","cpu loigc err: register *^" + ss.str() + " does not exist!");
    EBX = 1;
    p_exit();
   }
}
