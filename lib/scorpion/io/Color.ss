/*
* Copyright (C) 2015 Braxton Nunnally
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
* Color.ss
* Library module
*
* This file manipulates
* the color of text that is 
* being outputted to the console.
* 
* Author: Braxton Nunnally
* Date: 6/16/2015
*/
module: scorpion_io {
   class: Color {
      /* -------( Declare Console Colors )------- */
	 
	  loadi LIGHT_SH 1           /* Color shades */
	  loadi REG_SH 0
	  
      loadi NORM 38               /* default console color */
      loadi RED 31                
	  loadi BLACK 30
	  loadi DARK_GRAY 30
	  loadi BLUE 34 
	  loadi GREEN 32 
	  loadi CYAN 36
	  loadi PURPLE 35
	  loadi BROWN 33
	  loadi YELLOW 33
	  loadi WHITE 37
	  loadi LIGHT_GRAY 37
	  
	  /* System Color info selectors */
	  
	  loadi TONE 0          ; get current System color tone
	  loadi COLOR 1         ; get current System color 
	  loadi INFO 0
	  loadi SYS_COL 0 &&idx_offset: 50 ; system color string
	  
	  /*
	  * Returns the numeric value of the current 
	  * system color or shade
	  *
	  * The numeric value can then be compared to 
	  * the list of colors and shades that the system 
	  * supports
	  */
	  .currSysColor:
	     same requestTone TONE,INFO
		 do requestTone 
		     rmov sdx INFO
			 invoke 0x84 0
             r_mv scr INFO 
		 end 
		 
	     same requestColor COLOR,INFO
		 do requestColor 
		     rmov sdx INFO
			 invoke 0x84 0
             r_mv scr INFO 
		 end 
		 printf 'Color:  error: Invalid option /'<v,INFO>/' '
	     ret 
	  
	   .sysColorToString:
	   
	      ret 
	  
   }
}