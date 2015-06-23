; This will be a simple kernal for our os
; This kernal will mainly just print out all the content 
; feed of what the os is doing at the current point in time

import 'C:\Users\Braxton\Desktop\ScorpionProjects\BMOS\os\sys_info.ss' ; some cpu info functions

.kernal:
   print 'Booting Fake-Linux on virtual CPU 0xf00/n' ; The device has already booted, however we still print it
   print 'Initalizing subsys processees cpu/n'        ; set up processee system for cpu
   print 'Linux Version: 1.0.37-v1+ #755 SMP PREEMPT Mon April 27 12:10:47 GMT 2015/n'
   call cpu_info                                      ; Get Cpu Information
   printf 'Cpu: RMD Atrix X1 340K Cortex digital processor revision 2(<v,PID>)/n'
   printf '         cores=<v,NCORES>; prod-date=<v,PDATE>;/n'
   print 'Machine model: Raspberry Pi 2 Model B+/n'
   ; map the ramand prepare for low mem for the ram
   print 'Virtual kernel memory layout:/n'
   print '        Rmap    : 0xffc00000 - 0xffe00000    ( 2048 B)/n'
   print '        vmalloc : 0xbb800000 - 0xff000000    ( 0 B)/n'
   print '        lowmem  : 0x80000000 - 0xbb000000    ( 944 B)/n'
   print '        modules : 0x7f000000 - 0x80000000    ( /<cp-mem>)/n'
   ret

; -b C:\Users\Braxton\Desktop\ScorpionProjects\BMOS\bmos-img.b C:\Users\Braxton\Desktop\ScorpionProjects\BMOS\boot\boot.ss C:\Users\Braxton\Desktop\ScorpionProjects\BMOS\os\*.ss 

