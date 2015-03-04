# RPVM
Native Raspberry Pi VM implementation in C++ (can run in any Debian or Linux distribution)

# Info
This is a vm that i will be developing for quite a while that is made using the Raspberry Pi mofel B+.  The aim of this program it to make it easy to develope programs in assembly language  that solve problems alike a traditional vm would. NOTE : this vm is not based on any specific computer architecture. NOTE: All commits pushed to this repository will be 90% or beter performance wise. i.e. I will not commit code that does not work properly. All code will be put through a series of trials and tests before committing.
 
I will be developing a new language called **Scorpion. The high level part i will develope last because that is the hardest portion in this vm. Wtriting programs in the vm will operate at a low level allowing the simulation of programming a computer. 

# Specifications
The vm will have an organized process for executing code. Below is a simple representation of the process of writing programs in Scorpion.

              [source] ========> High level source code 'helloworld.sc'
                 ||
              [source] =========> Low level assembly source code 'helloworld.sasm'
                 ||
           [machine code] =======> Direct 'machine' code for the vm to execute 'hello.bexe'
                 ||
                [VM] =============> The virtural machiene can now run the object code
                 ||
              (output)
           
Th first part in the process is high level source code written in Scorpion. The file extention must end with .sc in order for the assembler to build a 'sasm' file. The source code in scorpion is alot alike c and java combined with some additional advantages. A 'sasm' file(scorpion assmebly) file is then generated by the language compiler. The sasm file is one step closer to machiene instructions that the vm can directly execute. The next stage is the generation of the machiene code instructions for the vm. The generated file will be a '.bexe'(binary executable) file that holds only 1's, 0's, and .'s. Once this file is generated you can then run the vm with the .bexe file. All programs will be written and built in c++.

# Programs
Based on the specifications defined, for everthing to work there are a total of 3 programs needed to run the vm.

Name | Description
---- | -----------
scpnc | (scorpion compiler) is used to compile the high level source code down to assembly language.
sasm | (scorpion assembler) translate the assembly code to binary object format.
svm | (scorpion vm) the vm itself runs the generated .bexe file([standard]can only run one single file as the entire program).

All programs reside in the programs directory.

# How to use
To use these programs you will have to folow the restrictions I have provoded. So far I only have the specifications for the vm(currently i only write programs in direct 'machine code').
In the console type:

      $  sudo ./svm file.bexe
 
The vm can only take a single object file that has all the instructions needed to run your program. In the future I plan to build a linker that will link multiple files together into a single file.  But for now you will only be able to have a single file as the full program to be run. i.e. when using the compiler you will not be able to reference other files. The vm will also print out in real-time a log of data that represents what the system is doing at that point in time. this file will be located in '/usr/share/svm/log.txt'. NOTE: If you have superuser access to all your files and or is logged in as root you do not need to type sudo before the program. Any system configs you will be having will go under the file '/usr/share/svm/system.conf'. Once I get the system fully up and running with all the specs I will write a file that lists all the possible error messages that might occur.

## Instruction set
Syntax for sasm is explained in SYNTAX.md
All registers are explained below
Full specs are in LINEUP.md

# Notes
I will program all these programs from the bottom up. i.e. first the vm, next the assembler, and finally the high level language compiler.
