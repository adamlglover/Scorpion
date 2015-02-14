#include <iostream>
#include <string>
#include "../../Log/Log.h"
#include <fstream>
using namespace std;

bool file_exists(const char *file);

string image = "";
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

int loadBIOS(int addr)
{
  const char *usb = "/usr/share/ooua1.bo";
  if(file_exists(usb)){
    image = v_img(usb);
     // handle img
  }
  else {
    Log u_log;
    u_log.v("System","fatal err occurred: err mounting usb...creating one...");
    image = "";
  }
}
