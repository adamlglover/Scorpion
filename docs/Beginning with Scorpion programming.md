# Beginning with Scorpion programming
This chapter will be explaining the most basic forms of scorpion source code.

## 3.1 Comments
Comments in scorpion are the most rudamentary thing that there is in scorpion. As with most programming languages there are both single line and multiline comments. Below is an example of comments in Scorpion.
      
          ; This is a comment
          ; This is another comment
          
          /*
          * This is a 
          * multi-line
          * comment
          */
          
Comments in Scorpion are completly ignored by the compiler and can be placed anywhere in the file in your source code. When using the single line comment ';', anything can be placed inside of that comment and will in-fact be ignored until the end of that line. However when using multiline comments, al information inside the comment block will be ignore until the first occurence of '*/'. When using multiline comments, do not nest comments together or you will confuse the assembler on where the end of the comment block ended. 

          Valid Single line comment
          ; This comment ; is /* ok /* ------*/ */ and will not throw an error
           
          Invalid multi-line comment
          /*
          * This multi-line
          * /* comment is wrong */ <- end of multi-line comment
          * <- err
          */ <- err
          
          Valid multi-line comment
          /* 
          * ; This comment
          * is ; valid
          * ----
          */
          

## 3.2 The print instruction
All instructions in scorpion are non-case sensitive, meaning that the instruction 'print' is the same as the instr. 'PRINT' or'PrINt', etc. You also do not have to declare functins or if statements to run a program in scorpion. you can simply type out any number of of instructions to be executed. Functions and if statements in Scorpion are simply control flow tools that you can use to write cleaner and more sophisticated code. Scorpion allows you to interface with the console using whats called the 'print' instruction. Print can print any character or sequence of characters that's printable by the computer and takes one argument. Below Is an examplle of using the print instruction.

           ; print <string_literal>
           print 'Hello World!/n'

The print instruction and takes a string literal as a single argument. In Scorpion, a string literal consists of 2 single quotes which begins and ends the string literal. DO NOT use double quotes to begin and end a string because it will not be considered a string literal by the assembler. You can however insert double quotes inside of single quotes.

           ; Invalid print statement
           print "Hello World"

           ; Valid print statement
           print '"Hello World"'; prints "Hello World"

#### 3.2.1 Escape sequences
In a string literal there are escape sequesequences allow you to put special characters in such as a new line or tab. In order to insert an escape sequence in a string literal, you must use the string escape insertion operator '/'.

           ; Scorpion string literal escape sequences 
                Newline:   /n    prints new line
                    Tab:   /t    prints tab
                  Slash:   /s    prints /
           Single quote:   /'    prints '
               LessThan:   /<    prints < (more on this later)

           ; example
           print '/'/<Hello/n World>/'/t/s'
           ; prints '<Hello
           ;         World>'    /

DO NOT insert a physical new line inside in a string literal otherwise the assembler will throw an error. Use the escape insertion operator.

## 3.3 Basic elements
In Scorpion, data types are considered eleements. Each element has rules and restrictions that define the element. There are a total of  7 different element types(`short`, `int`, `double`, `float`, `bool`, `char`, `string`).

#### 3.3.1. Numbers
We will discuss the number element types. Each numeric element type has a max and min. value of data that it can hold.

            short: max: 32,767  min: -32,767
              int: max: 2147483647 min: -2147483647
           double: max: 1.7*10^308 min: -1.7*10^308
            float: max: 1.175494351e–38F min: -1.175494351e–38F
            
The short element holds a very small ammount of data for simple math calculations. The int, double, and float elements holds very large values and could be used for big and or percise math atithmetic. Assigning an element type is simple, you first choose your element(which instruction), then pick a lable(more on labels below), then assign a value. Do not assign a value to an element if the value does not match the specified element. For instance, you would assign 5.63 to a short element because the value will simply be truncated to 5. Below is an example of this process.

           sload  cats   5   
             ^     ^     ^
          element  label value
          
A label is simply a refrence name that you give that points to a unique address in the ram that holds a value(basically a variable). For instance: the label cats may point to addr (@193 -> 5) which holds 5. An element can consist of and lowercase and or uppercase letters, numbers, and underscores. Labels also have to have at least 1 letter to be considered a label.

The instruction that is used to load a short value to a label is `sload`(short load). All the rules I've discussed also applies for all other numeric element types. 

          ; load a double
          dload pi 3.14159357 ; if you put 3 the number will be 3.0
          
          ; load a float
          loadf inches 12.3295  ; if you put 12 the number will be 12.0
          
          ; loadi a int
          loadi apples 6 ; if you put 6.2442, the number will be truncated to 6


#### 3.3.2 Strings
There are 2 types of string elements(char, string). In scorpion, a char represents a single character such as 'h'. This single character can be in string form such as 'l' or in numeric form such as 108(the ascii eq. of l). In order to assign a char element to a label, you would use the `loadc` instruction.

           ; load a char
           loadc char 'f'
           loadc char2 44
           
If you attempt to load a char with more than 1 character `loadc a 'df'`, then the assembler will complain. Strings however, are the opposite of a char. Instead of only holding a single char, strings hold multiple or a sequence of chars together to forulate text. In order to load a string into a label, yes the `string` instruction is needed.

            ; load a string
            string msg 'Hello, World'
            
In strings you can include some simple formatting by using the string excape sequence operator. Example: 

             string msg 'h/n/te/n/tl/n/tl/n/to'
             /*
             * prints: h\
             *             e
             *             l
             *             l
             *             o
             */

Strings in scorpion are a bit complex. In laymen's terms, a string is a continuing sequence of characters
