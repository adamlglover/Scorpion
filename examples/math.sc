(*
* This is a very High level source code
* That will express the very first source 
* code to begin utilizing the api library 
* for my vm
*)

// add the math bexe file to the high level 
// source( i.e. the .sc version might not exist..you 
// are refercing the .bexe version of the file )
#include <math>
#include <console>  // add console functions

int x = 30;
int y = 4; 

void math(int index, int a, int b) 
{
   switch( index ) {

       case 0:
         o_stream("fact " + fact(a) + "\n");  // print out fctorial
       break;
       case 1:
         o_stream("root " + pow(2,a) + "\n");
       break;
       case 2:
         o_stream("sin " + sin(a) + "\n");
       break;
       case 3:
         o_stream("cos " + cos(a) + "\n");
       break;
       case 4:
         o_stream("tan " + tan(a) + "\n");
       break;
       case 1:
         o_stream("sq root " + sqrt(a) + "\n");
       break;

   }
}

int main(int argc, int[] args)
{
   o_stream("x : " + x + " y : " + y ); // print out x and y to console
   math(0, x, y); // factorial
   math(1, x, y); // root
   math(2, x, y); // sin
   math(3, x, y); // cos
   math(4, x, y); // tan
   math(5, x, y); // square root
   return 0; // attempt to close the prog w/ exit code 0
}
