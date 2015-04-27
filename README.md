# What is Scorpion?
Scorpion is a dynamic bare metal programming language supporting various programming paradigms. It provides a set of features that allow for easy text and data processing as well as programming the physical hardware on a specific device. It is very simple and easy to use.

# Features Of Scorpion
- Very Simple Syntax
- Fast
- Exception Handling(soon to come)
- Portable(Write once. Run Everywhere.)
- Extreemly low level
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
Scorpion represents a miniture system that lives on your computers ram and can be programmed to do anything from processing a text file, to sending a signal to physical hardware on a device. Depending on the size of accessable memory on a specific device might affect the power and performance of how fast scorpion runs on that device. Sorpion's runtime enviornment consits of a Virtural machine that virturalizes all the physical hardware on the device it is running on to be programmed. This VM allows for scorpion source code to be portable considering that the only thing that changes is the hardware access. Below is an example of running a scorpion program on 2 different operating systems.

![alt tag](https://github.com/AndroDevcd/Scorpion/blob/master/diagrams/platfom_execution.png)

# Specifications
The vm will have an organized process for executing code. Below is a simple representation of the process of writing programs in Scorpion.

![alt tag](https://github.com/AndroDevcd/Scorpion/blob/master/diagrams/Scorpion.png)

In order to run programs in scorpion, you need to use nsc(Native Scorpion Compiler) to compile your source code down to binary format. During the compilation process nsc will add the included library modules, built-in function, as well as any custom defined modules that you have created to your project. After this process is completed, nsc will generate a binary file that is fully executableby the Scorpion Virtural Machine. When the file is given to the VM, it will be verified for any unusal elements inside the file then executed by the virtural hardware.



# Programs
Based on the specifications defined, for everthing to work there are a total of 2 programs needed to run scorpion source code.

Name | Description
---- | -----------
nsc | (Native Scorpion Compiler) translates the assembly code to binary format.
scorpion | The Scorpion virtural machine itself runs the (single)generated .b file as the entire program.

All programs reside in the bin/ directory(version specific).

# Getting Scorpion
### For linux/Mac
1. Go to the bin/ folder in the respository and click on the folder with your specific operating system. Then choose your device that is supported.
2. Download the raw file of scorpion and move scorpion to your /bin folder from your current directory


              your-name~:>  mv <your-curr-dir>/scorpion /bin
              
3. Scorpion is now ready for use!!

### For windows
1. Go to the bin/ folder in the respository and click on the folder with your specific operating system. Then choose your device that is supported.
2. Download the raw file of scorpion.
3. Go to where Scorpion was downloaded and move the file to any desired location, then copy the path to where it is located.
4. Go to your system settings and add Scorpion to your path via your system's envirnment variables
5. Scorpion is now ready for use!!


# How to use
To use these programs you will have to folow the restrictions I have provoded. So far I only have the specifications for the vm(currently i only write programs in direct 'machine code').
In the console type:

      $  sudo scorpion file [args...]
 
You do not have to type the .b extention of the file(program) to run the program(if you do, an error will be thrown).
The vm can only take a single binary file that has all the instructions needed to run your program. The vm will also print out in real-time a log of data that represents what the system is doing at that point in time. this file will be located in '/usr/share/scorpion/log.txt'. NOTE: If you have superuser access to all your files and or is logged in as root you do not need to type sudo before "scorpion". Any system configs you will be having will go under the file '/usr/share/svm/system.conf'(not yet implemented).

# Contributing
 If you have any questions concerns about the Scorpion programming language, you can email me at braxtonnunnally@gmail.com. However if you would like to help in the development of the Scorpion programming language, simply fork the repository and send me a pull request. All pull requests will be carefully evaluated and tested before accepting. 

