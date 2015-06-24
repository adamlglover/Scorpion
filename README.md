# What is Scorpion?
Scorpion is a dynamic bare metal programming language supporting various programming paradigms. It provides a set of features that allow for easy text and data processing as well as programming the physical hardware on a specific device. It is very simple and easy to use. Scorpion is intended to be used for embedded systems and consumer applications that runs on micro-electronics.

# Features Of Scorpion
- Very Simple Syntax
- Fast
- Exception Handling(soon to come)
- Portable(Cross compatible between linux/windows Operating Systems.)
- Extremely low level
- Dynamic module and internal structure

# Supported Devices

#### Linux / Debian
- Raspberry pi model B+
- Raspberry pi model B+ 2

#### Windows
(coming soon)

#### Mac/OSX
(coming soon)

# How it works
Scorpion represents a miniature system that lives on your computer's ram and can be programmed to do anything from processing a text file to sending a signal to physical hardware on a device. The size of accessible memory on a specific device might affect the power and performance of how fast Scorpion runs on that device. Scorpion's runtime environment consists of a Virtual machine that virtualizes all the physical hardware on the device it is running on to be programmed. This VM allows for scorpion source code to be portable considering that the only thing that changes is the hardware access. Below is an example of running a scorpion program on 2 different operating systems.

![alt tag](https://github.com/AndroDevcd/Scorpion/blob/master/diagrams/platfom_execution.png)

# Specifications
The vm will have an organized process for executing code. Below is a simple representation of the process of writing programs in Scorpion.

![alt tag](https://github.com/AndroDevcd/Scorpion/blob/master/diagrams/Scorpion.png)

In order to run programs in scorpion, you need to use nsc(Native Scorpion Compiler) to compile your source code down to binary format. During the compilation process, nsc will add the included library modules, built-in function, as well as any custom defined modules that you have created to your project. After this process is completed, nsc will generate a binary file that is fully executable by the Scorpion Virtual Machine. When the file is given to the VM, it will first be verified for any unusual elements inside the file, then executed by the virtual hardware.



# Programs
Based on the specifications defined, for everything to work there are a total of 2 programs needed to run scorpion source code.

Name | Description
---- | -----------
nsc | (Native Scorpion Compiler) translates the assembly code to binary format.
scorpion | The Scorpion virtual machine itself runs the (single)generated .b file as the entire program.

All programs reside in the bin/ directory(version specific).

# Additional Info
If you are seeking any additional info on scorpion, please check out my [wiki](https://github.com/AndroDevcd/Scorpion/wiki) I've created for Scorpion.


# How to use
To use these programs you will have to follow the restrictions I have provided. So far I only have the specifications for the vm(currently I only write programs in direct 'machine code').
In the console type:

      $  sudo scorpion file [args...]
 
You do not have to type the .b extension of the file(program) to run the program(if you do, an error will be thrown).
The vm can only take a single binary file that has all the instructions needed to run your program. The vm will also print out in real-time a log of data that represents what the system is doing at that point in time. This file will be located in '/usr/share/scorpion/log.txt'. NOTE: If you have superuser access to all your files and or is logged in as root you do not need to type sudo before "scorpion". Any system configs you will be having will go under the file '/usr/share/svm/system.conf'(not yet implemented).

# Contributing
 If you have any questions about the Scorpion programming language, you can email me at braxtonnunnally@gmail.com. However if you would like to help in the development of the Scorpion programming language, simply fork the repository and send me a pull request. All pull requests will be carefully evaluated and tested before accepting.

