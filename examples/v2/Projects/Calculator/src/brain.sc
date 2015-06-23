#include <stdio>
#include "fncs.r"

bool hasInp1 = false;
int inp1 = -203;
int inp2 = -203;
char chOp;

long CalculateResult(int inpt1, char op, int inpt2)
{
	if(op == '*')
	return (inpt1) * (inpt2);

    if(op == '-')
	return (inpt1) - (inpt2);

    if(op == '+')
	return (inpt1) + (inpt2);
	
    if(op == '/')
	return (inpt1) / (inpt2);

    if(op == '%')
	return (inpt1) % (inpt2);

	return 0;
}

void GetUserInput()
{

	o_stream << "Type a number : ";
	if(hasInp1 == false)
	{
		hasInp1 = true;	
		i_stream >> inp1;
	}
	else
	{
		hasInp1 = false;
		i_stream >> inp2;
		print(CalculateResult(inp1, chOp, inp2));
	}

}

void check()
{
	if(chOp == '*' || chOp == '-' || chOp == '+' || chOp == '/' || chOp == '%'){ }
	else 
	{
		i_stream << "Err : ";
		GetMatmaticialOpr();
	}
}

void GetMatmaticialOpr()
{
	
	o_stream << "Please type an operator (*, +, -, %, or /)  : "; 
	i_stream >> chOp;

	// check to see if you typed the correct operator
	check();
}
