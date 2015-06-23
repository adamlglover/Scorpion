#include <stdio>

#def INIT -203

int response = INIT;
int main();

(**
* function to end the program
*)

int end_prog() 
{
	
	o_stream << "-----------------------------------------" << endl;
	o_stream << "           ($---- EXIT ? ----$)" << endl;
	o_stream << "-----------------------------------------" << endl;
	i_stream >> response;

	// verify response
	if(response == 1){ return 1; }
	else if (response == 0)
	{
		return 0;
	}
	else 
	{
		o_stream << "Error invalid response";
		return 0;
	}

	return 0;
}

void ck_p()
{
	int r = end_prog();

	if(r == 0)
	{
		main();
	}
	else if(r == 1)
	{
		// close prog
	}
	else 
	{
		// err close
	}

}

