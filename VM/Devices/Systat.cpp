#include <string>
#include <sstream>
using namespace std;

string sys_stat(long input)
{
    switch( input ) {
       case 0x000000000:
         return "STATUS_OPEN";
       break;
       case 0x000000001:
         return "STATUS_BUSY";
       break;
       case 0x000000002:
         return "STATUS_INPUT";
       break;
       case 0x000000003:
         return "STATUS_BROKEN";
       break;
       case 0x000000004:
         return "DEVICE_UNKNOWN";
       break;
       case 0x000000005:
         return "DEVICE_BUSY";
       break;
       case 0x000000006:
         return "PORT_ADDRESS_UNKNOWN";
       break;
       case 0x0000000014:
        return "DISK_NOT_MOUNTED";
       break;
       case 0x0000000015:
          return "DEVICE_CORRUPTED";
       break;
       case 0x0000000016:
          return "DISK_NOT_FOUND";
       break;
       case 0x0000000017:
          return "DISK_DISCOVERED";
       break;
       case 0x0000000018:
          return "DISK_IDLE";
       break;
       case 0x0000000019:
          return "DISK_MOUNTED";
       break;
       case 0x0000000020:
          return "DEVICE_BOOTED";
       break;
       case 0x0000000021:
          return "DEVICE_SHUTDOWN";
       break;
       default:
          stringstream ss;
          ss << "SYS_STAT_UNKNOWN[" << input << "]";
          return ss.str();
       break;
    }
}
