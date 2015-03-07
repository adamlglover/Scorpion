#include "cpuf.h"

   /*
   * Open for input
   * This flag signifies that the data iside of the register 
   * is not being used for any special purpose 
   */
   // int CPUFlags::OI   = 0x0;
   
   /*
   * Uninitalized Function
   * This flag is set when you fowar decare a function
   * using %func but do not use push to initalize 
   */
   //int CPUFlags::UFN  = 0x1;

   /*
   * Main
   * This function is a special flag that the cpu reconizes the 
   * register as the entry point of execution
   */
   //int CPUFlags::MN   = 0x2;

   /*
   * Corrupted Unit
   * This is a dangerous flag that the cpu will set oif a register
   * is and or has corrupted data
   */
   //int CPUFlags::CU   = 0x3; 
   
   /*
   * Functions
   * This is a flag that signifies the register as a 
   * working function that has been initalized
   */
   //int CPUFlags::FN   = 0x4;
  
   /*
   * Loop
   * This is a flag that signifies the register as a
   * working loop.
   */
   //int CPUFlags::LP   = 0x5; 

   int   OI  = 0x0;
   int   UFN = 0x1;
   int   MN  = 0x2;
   int   CU  = 0x3;
   int   FN  = 0x4;
   int   LP  = 0x5;
   int   IC  = 0x6;
   int   LC  = 0x7;
   int   BC  = 0x8;
   int   SC  = 0x9;
   int   CC  = 0x10;
