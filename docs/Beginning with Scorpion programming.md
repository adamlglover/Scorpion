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
          
Comments in Scorpion are completly ignored by the compiler and can be placed anywhere in the file in your source code. When using the single line comment ';', anything can be placed inside of that comment and will in-fact be ignored until the end of that line in the file. However when using multiline comments, do not nest comments together or you may confuse the assembler on where the end of the comment block ended.

          Valid Single line comment
          ; This comment ; is /* ok /* ------*/ */ and will not throw an error
           
          Invalid multi-line comment
          /*
          * This multi-line
          * /* comment is wrong */
          *
          */
          
          Valid multi-line comment
          /* 
          * ; This comment
          * is ; valid
          * ----
          */
          
When using multiline comments be sure to not nest another multi-line comment inside of each other, otherwise the compiler will assume that the first '*/' that it reaches is the end of the comment block

## 3.2 The print command
Scorpion allows you to interface with the console using whats called the 'print' command
