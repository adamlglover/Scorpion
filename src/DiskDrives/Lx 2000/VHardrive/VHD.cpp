#include "vhd.h"
#include <fstream>
#include <sstream>
#include "../../Log/Log.h"
#include "../../Bus/bus.h"
#include <iostream>
#include <string>
using namespace std;

int accport = 0x80;
string sys_stat(long);

bool file_exists(const char *file);

/* States */
   bool mounted = false;
   bool IsRunning = false;

int  DISK_IMG = 0;
int DISK_STATUS = 0;
int HARDRIVE_STATUS = 0;

/* COMMANDS */
#define boot 0
#define vhalt 1
#define lr 2   // load data into a special registerdefined by the V$
#define find 3 // search for specified disk image
#define limg 4 // load the imade to the drive
#define dstatus 5 // send the current disk status(used when mountin$
#define hstatus 6 // send the current hardrive status to the port
#define log 7 // log either the dstat or the hstat
#define dump 8

// status codes
#define DISK_NOT_MOUNTED 0x0000000014
#define DEVICE_CORRUPTED 0x0000000015
#define DISK_NOT_FOUND 0x0000000016
#define DISK_DISCOVERED 0x0000000017
#define DISK_IDLE 0x0000000018
#define DISK_MOUNTED 0x0000000019
#define DEVICE_BOOTED 0x0000000020
#define DEVICE_SHUTDOWN 0x0000000021
#define DISK_UNMOUNTED 0x0000000022

int VHD::Write(int addr, long *input)
{
 cout << "writing to v-hd" << endl;
 return STATUS_OPEN;
}

void _boot()
{
 if(!IsRunning) {
   IsRunning = true;
   DISK_IMG = 0;
   DISK_STATUS = DISK_IDLE;
   HARDRIVE_STATUS = DEVICE_BOOTED;
 }
  else {
    Log ll;
    ll.v("HardriveInfo","Fatal err: hardrive is already running, please shutdown before booting");
  }
}

void halt()
{
  if(IsRunning) {
    Bus _bus;
    IsRunning = false;
    _bus.output(0);  //  output data to port 0x80
    mounted = false;
    DISK_IMG = 0;
    DISK_STATUS = DISK_IDLE;
    HARDRIVE_STATUS = DEVICE_SHUTDOWN;
  }
  else {
    Log ll;
    ll.v("HardriveInfo","Fatal err: hardrive is not running, please boot before halting");
  }
}

void _lr(long *input)
{
 switch(input[0]){
     case 1: // load the specified disk image
       DISK_IMG = input[1];
     break;
 }
}

const char *dimg = "";
void _find()
{
   switch(DISK_IMG){
     case 1:
       dimg = "/usr/share/scorpion/disks/ooua1.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 2:
	dimg = "/usr/share/scorpion/disks/ooua2.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 3:
	dimg = "/usr/share/scorpion/disks/ooua3.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 4:
	dimg = "/usr/share/scorpion/disks/ooua4.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 5:
	dimg = "/usr/share/scorpion/disks/ooua5.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 6:
	dimg = "/usr/share/scorpion/disks/ooua6.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 7:
	dimg = "/usr/share/scorpion/disks/ooua7.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 8:
	dimg = "/usr/share/scorpion/disks/ooua8.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 9:
	dimg = "/usr/share/scorpion/disks/ooua9.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
     case 10:
	dimg = "/usr/share/scorpion/disks/ooua10.img";
       if(file_exists(dimg))
        DISK_STATUS = DISK_DISCOVERED;
       else
        DISK_STATUS = DISK_NOT_FOUND;
     break;
    default:
      DISK_STATUS = DISK_NOT_FOUND;
    break;
   }
}

string v_img(const char *file)
{
      string tmp;
     string img = "";
     ifstream input(file);

     while(!input.eof()) {
         tmp = "";
         getline(input, tmp);
         img += tmp;
         img += "\n";
     }

   return img;
}

void _limg()
{
  if(!mounted){
    if(DISK_STATUS == DISK_DISCOVERED){
    	string image = v_img(dimg);
    	//load(image);
   	mounted = true;
    	DISK_STATUS = DISK_MOUNTED;
    }
    else
    {
       Log L;
       L.v("HardriveInfo","Fatal err occured: the current disk img does not exist....mount failure!");
    }
  }
  else {
   Log _lg;
     _lg.v("HardriveInfo", "Load err: disk already mounted, please unmount disk before re-mounting");
  }
}

void _dump()
{
  mounted = false;
  DISK_STATUS = DISK_UNMOUNTED;
  //dumpMem();
  //dumpEPMem();
}

void _log(long input)
{
  switch( input ) {
      case 0:
      break;
      case 1:
       {
	Log _log;
        std::ostringstream ss;
        ss << "current disk status is " << sys_stat(DISK_STATUS);
         _log.v("HardriveInfo",ss.str());
       }
      break;
      case 2:
       {
        Log _log2;
        std::ostringstream ss1;
        ss1 << "current hardrive status is " << sys_stat(HARDRIVE_STATUS);
         _log2.v("HardriveInfo",ss1.str());
       }
      break;
  }
}

int VHD::Process(int addr, long command,long *input)
{
 Bus _bus;
  if(addr == 0x80){
      switch( command ){
          case boot:
	    _boot();
           //cout << "boot" << endl;
          break;
 	  case vhalt:
            halt(); // power off the VHD
           //cout << "halt" << endl;
          break;
          case lr:
          if(IsRunning)
            _lr(input);
           else {
              Log ll;
              ll.v("HardriveInfo","Fatal err: hardrive is not running, please boot before running lr");
           }
           //cout << "lr " << input[0] << " " << input[1] << endl;
          break;
          case find:
           if(IsRunning)
	     _find();
            else {
              Log ll;
              ll.v("HardriveInfo","Fatal err: hardrive is not running, please boot before searching for disk image");
           }
           //cout << "find" << endl;
           break;
          case limg:
            if(IsRunning)
	     _limg();
            else {
              Log ll;
              ll.v("HardriveInfo","Fatal err: hardrive is not running, please boot before loading disk img");
           }
           //cout << "limg" << endl;
           break;
          case dump:
            if(IsRunning){
            if(mounted)
              _dump();
            else {
                 Log ll;
              ll.v("HardriveInfo","Fatal err: disk not mounted, please mount a disk img before dumping");
            }
           }
            else {
              Log ll;
              ll.v("HardriveInfo","Fatal err: hardrive is not running, please boot before dumping img");
           }
           //cout << "limg" << endl;
           break;
          case dstatus:
             _bus.output(DISK_STATUS);
           //cout << "output " << DISK_STATUS << endl;
          break;
          case hstatus:
             _bus.output(HARDRIVE_STATUS);
            //cout << "output " << HARDRIVE_STATUS << endl;
          break;
          case log:
            _log(input[0]); // 1 = dstst : 2 = hstat
             //cout << "log " << input[0] << endl;
          break;
      }
  }
  return STATUS_OPEN;
}
