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
* rx.ss
* simple 433Mhz rf reciever
* driver.
*
* Author: Braxton Nunnally
* Date: 6/24/2015
*/

import <io/gpio>
import <io/signal>

class: 433Rf {
   loadi PIN 10
   loadi BIT 0
   .recieveBit:
     loadi readBit 1
     cp GPIO.PIN PIN
     wloop readBit readBitb
           call GPIO.read
           ile GPIO.SIG[signal.HIGH]
               cp BIT GPIO.SIG
               return recieveBit 1 
           end
     endwl readBit readBitb     
     ret

   string packet '00000000'
   .recievePacket:
     adr ref packet
     loadi packet 8
     inc ref
     loop getPacket getPacketb 8
          call recieveBit
          r_load ref BIT
     endl getPacket getPacketb
     ret
}

class: Main {
   .main:
     call 433Rf_Setup
     call loop
     ret

   .433Rf_Setup:
     cp GPIO.PIN 433Rf.PIN
     cp GPIO.DIR signal.IN
     call GPIO.export
     call GPIO.direction
     print 'Rf Reciever setup.../n' 
     ret

   .loop: ; loop recieving bits of information
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     call recieveBit
     print 'recieved bit: <v,433Rf.BIT>/n'
     ret
}
