#include <iostream>
#include "system_color.h"
#include "runtime_exception.h"
#include <string>
using namespace std;

struct Color {
    int ctone;
    int ccolor;
} ;

Color syscolor;

void _sys_color_init()
{
  syscolor.ctone = 0;
  syscolor.ccolor = 38; // no color
}

int SystemColor::getSystemColorInfo(int info)
{
   if(info == 0)
    return syscolor.ctone;
   else if(info == 1)
    return syscolor.ccolor;
   else
    return 0;
}

bool SystemColor::isColor(int color, int tone)
{
   if((tone != 1) && (tone != 0))
     return false;

   if(color < 30 && color > 38)
     return false;

   syscolor.ctone = tone;
   syscolor.ccolor = color;
   return true;
}

/* C-Style Supported Colors */
int LIGHT = 1, REG = 0;

#define BLACK 30
#define DARK_GRAY 30

#define BLUE 34
#define LIGHT_BLUE 34

#define GREEN  32
#define LIGHT_GREEN 32

#define CYAN 36
#define LIGHT_CYAN 36

#define RED 31
#define LIGHT_RED 31

#define PURPLE 35
#define LIGHT_PURPLE 35

#define BROWN 33

#define YELLOW 33

#define WHITE 37
#define LIGHT_GRAY 37

#define NO_COLOR 38

string d_gray = "\033[1;30m", l_blue = "\033[1;34m",
       l_green = "\033[1;32m", l_cyan = "\033[1;36m",
       l_red = "\033[1;31m", l_purple = "\033[1;35m",
       yellow = "\033[1;33m", white = "\033[1;37m";

string n_color = "\033[0m", black = "\033[0;30m", blue = "\033[0;34m",
       green = "\033[0;32m", cyan = "\033[0;36m",
       red = "\033[0;31m", purple = "\033[0;35m",
       brown = "\033[0;33m", l_gray = "\033[0;37m";

void SystemColor::changeColor()
{
  RuntimeException re;
  if(syscolor.ctone == LIGHT)
  {
     switch(syscolor.ccolor)
    {
       case DARK_GRAY:
          cout << d_gray;
          return;
       break;
       case LIGHT_BLUE:
          cout << l_blue;
          return;
       break;
       case LIGHT_GREEN:
          cout << l_green;
          return;
       break;
       case LIGHT_CYAN:
          cout << l_cyan;
          return;
       break;
       case LIGHT_RED:
          cout << l_red;
          return;
       break;
       case LIGHT_PURPLE:
          cout << l_purple;
          return;
       break;
       case YELLOW:
          cout << yellow;
          return;
       break;
       case WHITE:
          cout << white;
          return;
       break;
       case NO_COLOR:
          cout << n_color;
          return;
       break;
    }
  }
  else if(syscolor.ctone == REG)
  {
    switch( syscolor.ccolor )
    {
      case BLACK:
          cout << black;
          return;
      break;
      case BLUE:
          cout << blue;
          return;
       break;
       case GREEN:
          cout << green;
          return;
       break;
       case CYAN:
          cout << cyan;
          return;
       break;
       case RED:
          cout << red;
          return;
       break;
       case PURPLE:
          cout << purple;
          return;
       break;
       case BROWN:
          cout << brown;
          return;
       break;
       case LIGHT_GRAY:
          cout << l_gray;
          return;
       break;
       case NO_COLOR:
          cout << n_color;
          return;
       break;
    }
  }
  else
   re.introduce("SystemColorFaultException","unknown color tone");
}
