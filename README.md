# Scorpion
A dynamic new computer language implemented in C++ 

# Info
I will be developing a new Computer language called Scorpion. Scorpion, alike java, is a platform independant language. Scorpion will have a VM that works as the middle layer between the Operating System and the source code. Once the High level source code is compiled all the way down to binary level(the code that the VM understands) the program can run seemlessly on any operating system that has the Scorpion VM on it. The high level language rules and syntax will be developed after the VM. Writing programs in the vm will operate at a low level allowing the simulation of programming a real computer. Below is a diagram of how it is platform independant(alot like java):

![alt tag](https://github.com/AndroDevcd/Scorpion/blob/master/Diagrams/platfom_execution.png)

# Specifications
The vm will have an organized process for executing code. Below is a simple representation of the process of writing programs in Scorpion.

              [source] ========> High level source code 'helloworld.sc'
                 ||
              [source] =========> Low level assembly source code 'helloworld.ss'
                 ||
           [machine code] =======> Direct 'machine' code for the vm to execute 'hello.b'
                 ||
                [VM] =============> The virtural machiene can now run the object code
                 ||
         (Operating System)  >> output
           
Th first part in the process is high level source code written in Scorpion. The file extention must end with .sc in order for the assembler to build a 'ss' file. The source code in scorpion is alot alike c and java combined with some additional advantages. A '.ss' file(scorpion source[assembly]) file is then generated by the language compiler. The ss file is one step closer to machiene instructions that the vm can directly execute(The machine code instructions are NOT the actual machine code instructions for the processor to execute). The next stage is the generation of the byte code instructions for the vm. The generated file will be a '.b'(binary) file that can contain only 1's, 0's, .'s, and whitespace. Once this bytecode file is generated you can then run the vm with the .b file. Below is an example of this structure:



![alt tag](https://github.com/AndroDevcd/Scorpion/blob/master/Diagrams/source_to_bytecode.png)


# Programs
Based on the specifications defined, for everthing to work there are a total of 3 programs needed to run the vm.

Name | Description
---- | -----------
(undecided) | (scorpion compiler) is used to compile the high level source code down to assembly language.
sasm | (scorpion assembler) translate the assembly code to binary object format.
scorpion | The Scorpion virtural machine itself runs the (single)generated .b file as the entire program.

All programs reside in the bin/ directory(version specific).

# How to use
To use these programs you will have to folow the restrictions I have provoded. So far I only have the specifications for the vm(currently i only write programs in direct 'machine code').
In the console type:

      $  sudo ./scorpion file
 
You do not have to type the .b extention of the file(program) to run the program(if you do, an error will be thrown).
The vm can only take a single object file that has all the instructions needed to run your program. The vm will also print out in real-time a log of data that represents what the system is doing at that point in time. this file will be located in '/usr/share/scorpion/log.txt'. NOTE: If you have superuser access to all your files and or is logged in as root you do not need to type sudo before the program. Any system configs you will be having will go under the file '/usr/share/svm/system.conf'(not yet implemented).

## Instruction set
Read LINEUP.md for information on system.

