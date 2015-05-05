# Introdunction
Scorpion is a dynamic bare metal programming language supporting various programming paradigms. 
It provides a set of features that allow for easy text and data processing as well as programming the 
physical hardware on a specific device. If you like programming a computer from a low level where you 
have full control over memory managment and data manipulation, Scorpion is the language for you. It is 
designed to be simple enough that you can achieve fluency in the language. It's commands and syntax 
resembles that of an assembly programming language(not of any specific processor) but is organized differently 
with extended capabilities and features that make this language simpler than a traditional assembly language.

The Scorpion programming language contains a miniture internal system(The Scorpion Virtual Machine) that handles 
all information and data processing. This system allows for Scorpion source code to be portable considering that 
this system does not change across devices. Unfortunatley however, this system tremendously slows down the execution 
time of running programs in scorpion.

Scorpion allows you to split your program into modules that can be reused in other Scorpion programs. It comes with a 
large collection of standard modules and built-in functions that you can use as the basis of your programs — or as 
examples to start learning to program in Scorpion. Some of these modules provide things like file I/O, system calls, 
text processing, and exception and interrupt managment.

Scorpion source code does not have to be written in any particular editer or IDE - which is great for quick throw away programs.

This general guide ia a quick guide to get you started with Scorpion programming and is not an in-depth explination on how to 
program in Scorpion.

## Invoking The interpreter
If you have yet to set up Scorpion, see: "Setting Things Up". Once Scorpion is set up correctly it will be set in your path on your 
machine ans can be directly typed in as a command. The Scorpion Virtual Machine takes 2 types of arguments when invoking the interperater.

                Arg 1:
                $  scorpion [option]
                Arg 2:
                $  scorpion [program] [args...]

The first argument simply passes an option to the VM, prints out the result, and exits the program. An option may consist of "-help", 
"-version", and more. Each option will perform something different for telling the Scorpion VM to perform an action. The second argument 
that is passed to the VM is an example of running a program in Scorpion. When running a program in Scorpion, you can pass arguments 
to your program to be used as arguments for your program. For example, you may be developing a file-reader program that prints out what 
is in the files that you passed to the VM.

## A simple explination
The Scorpion Virtual machine in laymen's terms is a fictional machine that resides in your computer's memory and emulates the components 
that are on that device. The end user will have a very similar experience on the Scorpion VM as they would have on the dedicated hardware.
Scorpion is a extreemly low level language and provides access to all the hardware on a specific machine ready to be programmed.

#### Memory
Depending on the machine the Scorpion VM is running on will determine the ammout of memory that it can access. Insead of having "heap memory" 
or a pool of memory addresses that holds all variables and data, the Scorpion VM provides a virtualized ram chip that emulates the physical chip 
that is on your device. 

If you are more intrested in learning about this virtual ram chip, see: "Advanced Memory Concepts" to learn more.
