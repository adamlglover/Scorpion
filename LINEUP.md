This file contails the full lineup of the the entire computer system 'Scorpion Virtural Machine'

Note: All parts of computer and or components are a combination of fictonal and real concepts. Information, names, etc. are all made up by the developer of the system and do not truly exist only for the sole purpose to be used as a reference point. 
Each virturalized hardware part of the machine is quantified into the groups below

##### Systems

 * [MMC4080(Multifunctional Micro Computer)](#mmc4080)
 
##### Micro processors

  * [RMD 8208](#rmd-8280)
  
##### Random Access Memory Devices

  * [DM3 100](#dm3-100)
  * [DM3 101](#dm3-101)
  
##### Disk Image Harvrives

  * [Lx 2000](#lx-2000)
  

--------------------------------------------------------------------- 
# MMC4080
This computer is the first of its kind developed by RMD. It features a full set of hardware that allows you to run almost any program on the board without little restrictions. The board witholds a very low ammount of accessable ram w/ a high ammount of program ram. The extreemly slow CPU clock speed poses a problem for running big energy consuming programs. The microprocessor is manufactured with RMDv1 Architecture which is perfect for simple programs and beginner Algebra computational power.

  * Manufacturer: [RMD](#rmd)
  * CPU: [RMD 8208](#rmd-8208)
  * RAM: [DM3 101](#dm3-101)
  * SRam: [DM3 100(standard)](#dm3-100)
  * Additional Hardware: [Lx 2000](#ix-2000) 
  
---------------------------------------------------------------------

X-1 Series

# RMD 8208
The X-1 Series RMD 8208 CPU features all the nessicary instructions needed for data manipulation and arithmatic proccessing. Below is a chart explaining the specs of the CPU .

| Essentials              |            | 
| ----------------------- | :--------- |
| Production Date         | 3-15       |
| Processor Number        | 8208       |
| Cache                   | none       |
| Instruction Set         | 64-bit     |
| [IFT](#instruction-filter-type) | 4          |
| Architecture            | [RMDv1](#rmdv1)    |

Performance           |        |
--------------------- | :----- |
# of Cores            | 1
# of Threads          | 1
Processor Frequency   | .030Mhz
Max Frequency         | .033Mhz

Advanced Technologies                                |      |
---------------------------------------------------- | :--- |
Hyper Threading Technology                           | no
[Safe Guard Technology](#safe-guard-technology)      | no
[Security Key](#security-key)                        | no
[Data Shift Technology](#number-shift-technology)    | no   |

All information provided is subject to change at any time, without nnotice. Information provided is presented "as-is" and performance levels are but not limited to the raspberry pi model B+.
--------------------------------------------------------------------

# DM3 100(Standard)
The DM3 100 Ram Chip is standard in all RMD distributions. It features a very high ammout of fast access ram w/ status reports of the current state of the program. This type of Ram Chip is the only chip that will be engineered to be used for the sole purpose of holding the entire program on it. i.e. This Chip will frequently be edited.
Below is a chart explaining the specs of the chip .

| Essentials                                        |      |
| ------------------------------------------------- | :--- |
| [# of Cells](#number-of-cells)                    | 1    |
| [Max Program Size](#program-size)                 | 30mb |

All information provided is subject to change at any time, without nnotice. Information provided is presented "as-is" and performance levels are but not limited to the raspberry pi model B+.

# DM3 101
The DM3 101 Ram Chip features a very low ammout of ram and is the first of its kind to be engineered by RMD.
Below is a chart explaining the specs of the chip.

| Essentials                                        |      |
| ------------------------------------------------- | :--- |
| [# of Cells](#number-of-cells)                    | 4    |
| Max Size                                          | 4mb  |
| [R\C ratio](#number-of-cells)                     | 1mb  |

All information provided is subject to change at any time, without nnotice. Information provided is presented "as-is" and performance levels are but not limited to the raspberry pi model B+.
--------------------------------------------------------------------


All information below pertains to all the information provided above to clear any mis conceptions.
--------------------------------------------------------------------

--------------------------------------------------------------------

# Data Shift Technology 
Data Shift Technology allows for shifting a data value to the left or right a certain ammount of bits by manipulationg the instructions inside the SRam.

# Max Program SIze
This represents the total ammount of machine instructions that the VM can take to execute. Each instruction is represented as 1 byte. A board with 30mb of SRam can execute a program with a total of 30000000 instructions.

# Number of Cells
The Ram chips designed by RMD are designed to have multiple cells with each cell pertating to a specified use. A cell is computer chip that rests on the Ram chip  and holds a certain ammount of data( in mb). The more cells the ram chip holds, the slower the ram and the R\C(Ram per Cell) rate drops. For instance the very first Ram chip designed by RMD had 4 cells with a total memory of 4mb. The R\C rate is calculated by this formula ( R\C = T/C ). Where T represents the total ammount of Ram and C represents the total ammount of cells on the chip.

# Security Key
Security Key consists of a digital random number generator that creates truly random numbers to strengthen encryption algorithms.

# Safe Guard Technology
SGT provides safe code execution of embeded api's while running a program on the device. This is perfect for preventing Ram data collision when executing a program. For instance:

              Load.sasm(Ex. API File)
              0   loadi r1 #3
              1
              
              Test.sasm(Ex. Program file)
              0    include<Load>
              1    loadi r1 #7
              
Altough this is a very simple example, you can see how data colision is a very big issue in a very big API running in apralell with a big program considering that they operate on the same Ram.

# Instruction Filter Type
IFT simply describes the ammount of instructions the CPU takes in as input to perform a full operation. For instance:

      Instructions
      10.100.1.0.10010.111111110.10111.0.0.0.0.0
                ^-----------------------^ << the next 4 instructions
                           |
                           V
                10010.111111110.10111.0
                loadi r510 #23
       
When the CPU access the SRam, it requests the next 4 instructions to be executed and handled accordingly. In the example above we see a CPU with an IFT of 4. Those fout instructions can be interpreted as "loadi r510 #23". Considering that the load command only requires 2 operands, the fourth or last operand is simply ignored.

# RMD
RMD(Remixed Micro Devices) is a makeshift company that I have created to represent a 'pretend' manufacturer of the computer

RMD manufactures hybrid or technology that is soley limited to my imagination but also somewhat limited to reality in how a computer should be made as well as the limitations that come with it. 

        Products
          - Random Access Memory Chips
          - Microprocessors
          - Disk Image Hardrives
    
# SRAM
SRam(Secondary Ram) represents a piece of crucal memory on the computer that is solely used for holding program instructions.
This componennt will also be the largest component(in terms of actual physical memory) in the system considering it will be controlling the computer.


Opcode |Arguments | Description
------ | -------- | -----------
halt   | bool     | Halts the vm. 'bool' wether or not to reboot the vm and empty all data in registers and reloads the program back onto the cpu.
rhalt  |          | Resets the cpu
chalt  |          | Halts the cpu
loadi  | r# value | Load an integer to the specified register
add    | eax[], r# r#:r# | Add the specified data sets and store it in a register
sub    | eax[], r# r#:r# | Subtract the specified data sets and store it in a register
dout   | r#       | Output the data in the register with decomal format
scmnd  |          | Tells the cpu to show the next operation
loadbl | r# bool  | Loads a boolean to the specified register
same   | r# r#:r# | Test if the data in both registers are the same and store the result in a register
size   |          | Get the size if the current running program in bytes
mv     | r#<-r#   | Move the value of one register in the specified register
rm     | r#       | Wipe the data inside of a register
mult   | eax[], r# r#:r# | Multiply the specified data sets and store it in a register
div    | eax[], r# r#:r# | Divide the specified data sets and store it in a register
%func  | r#       | specify a register as a function
push   | r#       | Initalize a function and fill the funtion with operations
return |          | Tell the cpu to jump ahead to the specified instruction
call   | r#       | Call a function 
swp    | r#:r#    | Swap the contents that are inside the registers
eof    | r#       | Dump the flags for the specified register
loop   | r# r# (i)| Loop through a command for the specified ammount of iterations and store it in the specified register
bout   | r#       | Output the data inside the specified register in boolean format
rem    | eax[], r#  r#:r# | Get the remainder of the two operands and store them inside the specified register
and    | eax[], r#  r#:r# | Simulated a logical and gate
or     | eax[], r# r#:r#  | Simulated a logical or gate 
xor    | eax[], r# r#:r#  | Simulated a logical xor gate
not    | eax, r#  | Simulated a logical not gate
nand   | eax[], r# r#:r#  | Simulated a logical nand gate
nor    | eax[], r# r#:r#  | Simulated a logical nor gate
xnor   | eax[], r# r#:r#  | Simulated a logical xnor gate
loadr  | r#<-eax, r#<-r#    | Load the contents in one register into another register
end    |          | End an if statment
endl   | r# r#    | End a loop or loop again
do     | r# == 1  | Logical if
mov    | #        | Move imediate data into a special register
rmov   | r#       | Move data in a register into a special register
init   | #        | Perform a system call with the given params
ilt    | r# < r#  | Logical if
igt    | r# > r#  | Logical if
iltoeq | r# <= r# | Logical if
igtoeq | r# >= r# | Logical if
ndo    | r# == 0  | Logical if
inlt    | !(r# < r#)  | Logical if
ingt    | !(r# > r#)  | Logical if
inltoeq | !(r# <= r#) | Logical if
ingtoeq | !(r# >= r#) | Logical if
neg     | r#      | Mutiply the data in a register by -1
cadd    | eax[], r# r#:r# | Add the specified data sets and add it to the current contents of the specified register
csub    | eax[], r# r#:r# | Subtract the specified data sets and subtract it to the current contents of the specified register
cmult    | eax[], r# r#:r# | Multiply the specified data sets and multiply it to the current contents of the specified register
cdiv     | eax[], r# r#:r# | Divide the specified data sets and divide it to the current contents of the specified register
crem     | eax[], r# r#:r# | Modulate the specified data sets and modulate it to the current contents of the specified register
mlock    |            | Mass lock all data in all registers to the ram 
lock     | r#         | Lock the data in the specified register to the ram
mulock   |            | Mass unlock all data from the ram and store it in all registers
ulock    | r#         | Unlock the data in the specifed register from the ram and store it in the register
xreg     | r#         | Exclude/Include a register mass locking/unlocking data from the ram 
clx      |            | Clear all excluded flagged registers
rloop    | r# r# (r#) | Loop through a command for the specified ammount of iterations and store it in the specified register
wloop    | r# r#      | While loop(while the data in the first reg is == 1 loop)
endwl    | r# r#      | Either pass or loop through again(while the data in the first reg is == 1 loop)
port     | r# (i)     | Read/Write data from the current accessed port(if read the data will be stored inside the specified register)
nac      |            | Not a command(basically do nothing)










# Registers
More registers will be added, the present registers are not final 

Name   | Parameters | Description
------ | ---------- | -----------
r0-r10,028 |  any       | The basic registers from 0 to 10,028 that can hold any type of data
eax    | [int,int]  | This is a special register used only for quick math arithmetic. The two values passed to this register will be evaluated directly and stored inside the register.
tmp    |  any       | This is a register that is used to temporarily hold irrelivant data
ip     |   [int]    | (instruction pointer)Tells the cpu where in the program to execute the next instruction
ebx    |   [int]    | The program's potential exit code
sdx    |   [int]    | Data to be used in a system call
sfc    |   [int]    | Special code to determine the format of a system call i.e.(you may format a int to be a boolean)
scx    |   [int]    | System command
bp     |   [int]    | The current port to be accessed
exc    |   [int]    | Wether or not to invoke a system exit call
ps     |   [int]    | The current port status
lg     |   [int]    | Wether or not logging is on
lsl    |   [int]    | The current log stack lvl(verbose,debug,assert,etc.)
i1     |   [int]    | Param 1 for I/O
i2     |   [int]    | Param 2 for I/O
