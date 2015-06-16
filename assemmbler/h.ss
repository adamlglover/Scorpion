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
* main.ss
* Reboot the Raspberry Pi
*
* Author: Braxton Nunnally
* Date: 6/1/2015
*/ 

extern Mod.M1.m1
extern Mod.M1.m2

import '/home/pi/Desktop/GitHub/Scorpion/assemmbler/part.ss'

module: Mod {
  class: M1 {
    .m1:
      print 'm1/n'
      ret

     .m2:
       print 'm2/n'
       ret
  }
}

call Mod.M1.m1
call Mod.M1.m2

