// Calculator.sc : main project file.

#include <stdio>
#include "prog.r"
#include "fncs.r"


// different types of variable 'types'
(**
* The different types are 
*  [  bool  | char  ]
*  [  int   | float ]
*  [  short | long  ]
*  [      double    ]
*)

void bueatify
{
        o_stream << "=========================================" << endl;
	o_stream << "            Scorpion CALCULATOR" << endl;
	o_stream << "=========================================" << endl;
}

int main()
{

	bueatify();

	GetUserInput();

	GetMatmaticialOpr();

	GetUserInput();

	// check the program for exiting
	ck_p();

    return 0;
}
