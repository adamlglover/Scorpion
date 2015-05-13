/*
* Copyright 2015 Braxton Nunnally
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*/
#include "io.h"
#include "core0.h"
#include "../../GPIO/gpio.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

extern string p;
extern void tostring(const char *name);
extern bool file_exists(const char *file);
int ibool(long);

string file_name = "";
std::ofstream stream;
long InputOutput::Write(int device,  long *data)
{
   switch( device ) {
      case 0:  // GPIO
        return GPIOWrite(SDX, TMP);
      break;
      case 1:
       {
         if(data[0] == 1) // open a file
         {
            if(file_exists(file_name.c_str())){
               const char *f = file_name.c_str();
               stream.open(f);
               if (stream.is_open())
                 return 1;
               else
                 return 0;
            }
            else
             return -1;
         }
         else if(data[0] == 2)
         {
           if (stream.is_open()){
             //char fstream[1000000];
             long start_addr = SCX;
             start_addr++;
             int ch;
             char wrd;
             for(int i = 0; i < core0.getr(0, SCX); i++){
                 ch = core0.getr(0, start_addr++);
                 wrd = ch;
                 stream << wrd;
             }
           }
           else
            return -1;
         }
         else if(data[0] == 3)
         {
           if (stream.is_open()){
             stream.close();
           }
           else
            return -1;
         }
         else
          return -3;
       }
      break;
  }
   return 0;
}

long InputOutput::Read(int device,  long *data)
{
   switch( device ) {
      case 0:  // GPIO
        return GPIORead(SDX);
      break;
      case 1: // File IO
       {
           if(data[0] == 1) // check for a file's presence
          {
             long start_addr = SCX;
             file_name = "";
             for(int i = start_addr + 1; i < (core0.getr(0, SCX) + SCX) + 1; i++)
                 file_name += core0.getr(0, i);
             return ibool(file_exists(file_name.c_str()));
          }
          else if(data[0] == 3) // empty temporary file's contents
          {
             p = "";
          }
          else if(data[0] == 6) // load the temporary file data to the ram
          {
             long start_addr = SDX + 1;
             int ch;
             for(long i = 0; i < p.length(); i++)
             {
                  ch = p.at(i);
                  core0.setr(0, start_addr++, ch);
             }
          }
          else if(data[0] == 2) // save the file in a temporary location
          {
             if(file_exists(file_name.c_str())){
                 const char *f = file_name.c_str();
                 tostring(f);
                 core0.setr(0, SDX, p.length());
             }
             else
               return -1;
          }
          else
           return -3;
       }
      break;
  }
   return 1;
}

