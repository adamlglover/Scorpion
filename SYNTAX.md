The syntax looks like most ASM with instructions and arguments and whatnot.

Subject to change:

1. Special commands are pre-fixed with %, like so: %loop.
2. Function calls must reference a register: call r2.
3. Registers are prefixed with a 'r', like so: r12.
4. Instruction arguments are separated by commas (thuogh actually they don't have to be).
5. All comments start with a ';' and omith anything after it until the next line
6. All sasm files must end with a blank line.

Example:

Low-Level version ===========>

          ; Brginning of the program
          loadi r3 #5   ; fill the parameter with value 5 and 2
          loadi r4 #2
          
          ; here we declare 2 functions
          %func r1
          %func _main   ; main is a special register r0 
          
          push r1       
             add r5 r3,r4   ; add the 2 specified values
             dout r5
             ip _main       ; tell the cpu to jump back to main
          return      
          
          push _main
             call r1
          return
          call _main     ; call the main function
          
          halt  0          ;   shutdown the vm and do not reboot
output:

          $    7
          
High-Level version ===========>

          void add(int x, int y)
          {
             o_stream(x + y); // output the value
          }
          
          int main()
          {
             add(5,2);
            return 0;
          }
          
          
