#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include "Assembler.h"
using namespace std;

extern bool isempty(string str);
extern long l_size;
extern int flag;

void parse();

#define nullptr ((void *)0)

struct map {
    string name;
    string module;
    string _class;
    long index;
} ;

struct dmap {
    string data;
    int type;
} ;

/* Token types */
int COMMAND = 0, STRING_LITERAL = 1,
    INTEGER_LITERAL = 2,
    HEX_LITERAL = 3,
    RAM_ADDRESS = 4,
    REGISTER = 5,
    LABEL = 6,
    NULLPTR = 7,
    ARG_EMPTY = 8, // the arg is not provided
    FUNCTION_LABEL = 9,
    RESERVED = 10,
    UNKNOWN = 11,
    SPECIAL = 12;

dmap *obj;  // our obj file mapped
map *labels; // out labels
long linepos = 0, mapsize;
stringstream token, fName;
bool instring = false, processedcommand, charLiteral = false;
bool inclass = false, inmodule = false;
string tokens[ 4 ];
int argsize, argoverflow, tpos = 0;

int arg1Types[ 6 ];
int arg2Types[ 6 ];
int arg3Types[ 6 ];

bool iswhitespace(char ch)
{
  if((ch == ' ') || (ch == '\t') || (ch == '\n')
          || (ch == 10) || (ch == 13))
      return true;
 return false;
}

void umap()
{
  delete[] obj;
  delete[] labels;
}

int getbounds(string token)
{
    if(token == "halt"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "breakp"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "rhalt"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "chalt"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "add"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        //    System.out.println("adding etypes for add";
        }
        else if(token == "sub"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "mult"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "div"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "rem") {
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "inc"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "dec"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "and"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "or"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   


            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "xor"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   


            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "not"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "nand"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   


            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "nor"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   


            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "xnor"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   


            arg1Types[2] = REGISTER;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = REGISTER;
            arg3Types[5] = REGISTER;   
            return 3;
        }
        else if(token == "loadi") {
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = HEX_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = RAM_ADDRESS;
            arg2Types[2] = NULLPTR;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "loadbl"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = RESERVED;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "push"){
            arg1Types[0] = LABEL;
            arg2Types[0] = LABEL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "return"){
            arg1Types[0] = LABEL;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "call"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   


            arg1Types[2] = LABEL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "swp"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   


            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "loop"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = INTEGER_LITERAL;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = INTEGER_LITERAL;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "end"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "endl"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "do"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = REGISTER;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "mov"){
            arg1Types[0] = REGISTER;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = REGISTER;
            arg2Types[1] = HEX_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = HEX_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = RESERVED;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "rmov"){
            arg1Types[0] = REGISTER;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = REGISTER;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "invoke"){
            arg1Types[0] = HEX_LITERAL;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = HEX_LITERAL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = HEX_LITERAL;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "ilt"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "igt"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "ige"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "ile"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "ndo"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "inlt"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "ingt"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "inle"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "inge"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = REGISTER;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "neg"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "lock"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "ulock"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "xreg"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "clx"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "rloop"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = LABEL;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = LABEL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "wloop"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "endwl"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "same"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = REGISTER;
            arg2Types[1] = REGISTER;
            arg3Types[1] = REGISTER;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = LABEL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "nac"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "sr"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "sl"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "r_mv"){
            arg1Types[0] = REGISTER;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = REGISTER;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "cpuid"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "rdtsc"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "print"){
            arg1Types[0] = STRING_LITERAL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = STRING_LITERAL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = STRING_LITERAL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            if(Assembler::compile_only)
                flag = 3;
            return 1;
        }
        else if(token == "rand_1"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "rand_2"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "rand_3"){
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "printf"){
            arg1Types[0] = STRING_LITERAL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = STRING_LITERAL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = STRING_LITERAL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            if(Assembler::compile_only)
                 flag = 3;
            return 1;
        }
        else if(token == "loadc"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = STRING_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            charLiteral = true;
            return 2;
        }
        else if(token == "dload"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = NULLPTR;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "t_cast"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = INTEGER_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "sload"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = HEX_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = NULLPTR;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "loadf"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = INTEGER_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = NULLPTR;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "rln"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = STRING_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = INTEGER_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = RAM_ADDRESS;
            arg2Types[2] = STRING_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            charLiteral = true;
            return 2;
        }
        else if(token == "rload"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "ct_int"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = RAM_ADDRESS;
            arg2Types[2] = RAM_ADDRESS;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "anum"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = RAM_ADDRESS;
            arg2Types[2] = RAM_ADDRESS;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "sleep"){
            arg1Types[0] = INTEGER_LITERAL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = INTEGER_LITERAL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = INTEGER_LITERAL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "cp"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "import"){
            arg1Types[0] = STRING_LITERAL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = STRING_LITERAL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = STRING_LITERAL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "string"){
            arg1Types[0] = RAM_ADDRESS;
            arg2Types[0] = STRING_LITERAL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = STRING_LITERAL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = RAM_ADDRESS;
            arg2Types[2] = STRING_LITERAL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            if(Assembler::compile_only)
                flag = 3;
            return 2;
        }
        else if(token == "adr"){
            arg1Types[0] = LABEL;
            arg2Types[0] = LABEL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = RAM_ADDRESS;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "r_load"){
            arg1Types[0] = LABEL;
            arg2Types[0] = LABEL;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = LABEL;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = RAM_ADDRESS;
            arg2Types[2] = RAM_ADDRESS;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "&&idx_offset:"){  
            arg1Types[0] = INTEGER_LITERAL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = INTEGER_LITERAL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = INTEGER_LITERAL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "&&working_dir:"){    
            arg1Types[0] = STRING_LITERAL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = STRING_LITERAL;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = STRING_LITERAL;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "strcp"){    
            arg1Types[0] = LABEL;
            arg2Types[0] = LABEL;
            arg3Types[0] = LABEL;   

            arg1Types[1] = RAM_ADDRESS;
            arg2Types[1] = RAM_ADDRESS;
            arg3Types[1] = RAM_ADDRESS;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "e2str"){    
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "strcpi"){      
            arg1Types[0] = LABEL;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = RAM_ADDRESS;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = REGISTER;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 1;
        }
        else if(token == "swi"){    
            arg1Types[0] = ARG_EMPTY;
            arg2Types[0] = ARG_EMPTY;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = ARG_EMPTY;
            arg2Types[1] = ARG_EMPTY;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = ARG_EMPTY;
            arg2Types[2] = ARG_EMPTY;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 0;
        }
        else if(token == "array"){      // array values 5 int
            arg1Types[0] = LABEL;
            arg2Types[0] = REGISTER;
            arg3Types[0] = RESERVED;   

            arg1Types[1] = LABEL;
            arg2Types[1] = RAM_ADDRESS;
            arg3Types[1] = RESERVED;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = INTEGER_LITERAL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "aload"){      // aload numbers 0 value
            arg1Types[0] = LABEL;
            arg2Types[0] = REGISTER;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = RAM_ADDRESS;
            arg3Types[1] = REGISTER;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = LABEL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "aaload"){      // aaload numbers 0 value
            arg1Types[0] = LABEL;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = RAM_ADDRESS;   

            arg1Types[1] = LABEL;
            arg2Types[1] = REGISTER;
            arg3Types[1] = REGISTER;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = LABEL;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 3;
        }
        else if(token == "throw"){ 
            arg1Types[0] = LABEL;
            arg2Types[0] = RAM_ADDRESS;
            arg3Types[0] = ARG_EMPTY;   

            arg1Types[1] = LABEL;
            arg2Types[1] = RAM_ADDRESS;
            arg3Types[1] = ARG_EMPTY;   

            arg1Types[2] = LABEL;
            arg2Types[2] = LABEL;
            arg3Types[2] = ARG_EMPTY;   

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;   

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;   

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;   
            return 2;
        }
        else if(token == "module:"){
            arg1Types[0] = LABEL;
            arg2Types[0] = SPECIAL;
            arg3Types[0] = ARG_EMPTY;

            arg1Types[1] = RAM_ADDRESS;
            arg2Types[1] = SPECIAL;
            arg3Types[1] = ARG_EMPTY;

            arg1Types[2] = LABEL;
            arg2Types[2] = SPECIAL;
            arg3Types[2] = ARG_EMPTY;

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;
            return 2;
        }
        else if(token == "%Class"){
            arg1Types[0] = LABEL;
            arg2Types[0] = SPECIAL;
            arg3Types[0] = ARG_EMPTY;

            arg1Types[1] = RAM_ADDRESS;
            arg2Types[1] = SPECIAL;
            arg3Types[1] = ARG_EMPTY;

            arg1Types[2] = LABEL;
            arg2Types[2] = SPECIAL;
            arg3Types[2] = ARG_EMPTY;

            arg1Types[3] = ARG_EMPTY;
            arg2Types[3] = ARG_EMPTY;
            arg3Types[3] = ARG_EMPTY;

            arg1Types[4] = ARG_EMPTY;
            arg2Types[4] = ARG_EMPTY;
            arg3Types[4] = ARG_EMPTY;

            arg1Types[5] = ARG_EMPTY;
            arg2Types[5] = ARG_EMPTY;
            arg3Types[5] = ARG_EMPTY;
            return 2;
        }
        else {
            arg1Types[0] = UNKNOWN;
            arg2Types[0] = UNKNOWN;
            arg3Types[0] = UNKNOWN;   

            arg1Types[1] = UNKNOWN;
            arg2Types[1] = UNKNOWN;
            arg3Types[1] = UNKNOWN;   

            arg1Types[2] = UNKNOWN;
            arg2Types[2] = UNKNOWN;
            arg3Types[2] = UNKNOWN;   

            arg1Types[3] = UNKNOWN;
            arg2Types[3] = UNKNOWN;
            arg3Types[3] = UNKNOWN;   

            arg1Types[4] = UNKNOWN;
            arg2Types[4] = UNKNOWN;
            arg3Types[4] = UNKNOWN;   

            arg1Types[5] = UNKNOWN;
            arg2Types[5] = UNKNOWN;
            arg3Types[5] = UNKNOWN;   
            return 0;
        }
}

void add(string token)
{
   
   if(!processedcommand){
       argsize = getbounds(token);
       argoverflow = 3 - argsize;

       tokens[ tpos++ ] = token;
       processedcommand = true;
       
      if(argsize == 0){
         processedcommand = false;
         tpos = 0;
         parse();
         return;
      }
   }
   else{
   
       if(tpos > argsize){
           processedcommand = false;
           tpos = 0;
           parse();
           add(token);
       }
       else
        tokens[ tpos++ ] = token;
   }
}

void assemble(string filen, string content)
{
   cout << "nsc:   assembling file: " << filen << endl;
   filen.str(""):
   fName << filen;
   if(isempty(content)){
      cout << "nsc:   error: " << filen << ": Is empty\n";
      Assembler::compile_only = true;
      return;
   }
   
   if(flag == 0){
      flag = 1;
      labels = new (nothrow) map[ l_size ];
      obj = new (nothrow) dmap[ l_size ];
      if(labels == nullptr || obj == nullptr){
        cout << "nsc:   error: Could not allocate resources.\nA fatal error has occured: Program will now exit." << endl;
        exit(-1039439);
      }
      for(int i = 0; i < 4; i++)
        tokens[i] = "";
   }
   
   for(int i = 0; i < content.length(); i++){
        if(content.at(i) == '\n')
                  linepos++;

        if((content.at(i) == '\'') && ((content.at(i - 1) != '/'))){
            if(instring)
                instring = false;
            else
                instring = true;
        }

        if((content.at(i) == '/') && !instring && (content.at(i + 1) == '*')){ // multi line comment
            for(int l = i; l < content.length(); i++){
                if(content.at(l) == '\n')
                    linepos++;

                if((content.at(l) == '*') && (content.at(l + 1) == '/')) { // \n
                    i++;
                    break;
                }
                l++;
            }
                linepos++;
        }
        else if(content.at(i) == ';'&& !instring){ // single line comment
             for(int l = i; l < content.length(); i++){
                 if((content.at(l) == 10) || (content.at(l) == '\n')) // \n
                      break;
                 l++;
             }
             linepos++;
        }
         else if((iswhitespace(content.at(i)) || content.at(i) == ',') && !instring) { // if <whitespace> -> add new token
              if(token.str() != "") {
                if(token.str() == "}" && inclass)
                       inclass = false;
                else if(token.str() == "}" && inmodule)
                       inmodule = false;
                else
                  add(token.str()); // parse data
                //  cout << "adding token: " << token.str() << " pos: " << tpos << endl;
                  token.str("");
              }
         }
         else
            token << content.at(i);
   }

   linepos = 0;
   parse();
}

int errline = -1;
void parse()
{

   if(errline == -1) {
     if (hasString(instructions, tokens[0])) { // is command
                    mapTokens(tokens[0], COMMAND);

                for (int i = 0; i < argsize; i++) {
                    // parse arguments
                    if (hasExpectedType(i, TokenType.type(tokens[i + 1]))) {
                           mapToken(tokens[i + 1], tokenType(tokens[i + 1]));
                    } else {
                        Assembler::compile_only = true;
                        cout << "nsc: " << fName.str() << ":" << linepos << "  fatal error parsing " <<
                                tokens[i + 1] << " token in file. Expected types <" << typeToString(etype(i, 1)) << "," <<
                                typeToString(etype(i, 2)) << "," << typeToString(etype(i, 3)) <<
                                ">, found type <" << typeToString(type(tokens[i + 1])) << ">.");
                    }

                }

                    if (flag != 3) {
                        for (int i = 0; i < argoverflow; i++)
                             mapTokens("", ARG_EMPTY);
                    } else
                       flag = 1;

            } else if(is_flabel(tokens[0])) { // ~func:(this one done manually)

                    mapTokens("push", COMMAND);
                    mapTokens(funcName(tokens[0]), LABEL);
                    mapTokens(funcName(tokens[0]) + "_b");
                    mapTokens(funcName(tokens[0]) + "_b", LABEL);
                    mapTokens("", ARG_EMPTY);
                    lastFunc = tokens[0];

            }
            else if (tokens[0].equals("&&idx_offset:")) // idx offset manipulation
                    labelOffset += tokens[1]);
            else if (tokens[0].equals("&&working_dir:")) { // idx offset manipulation
                String dir = "";
                for(int i = 1; i < tokens[1].length() - 1; i++)
                    dir += tokens[1].charAt(i);
                WORKING_DIR = dir;
            }
            else if (tokens[0].equalsIgnoreCase("ret")) { // ret <function>(this one done manually)
                    mapTokens("return", COMMAND);
                    mapTokens(funcName(lastFunc), LABEL);
                    mapTokens("0", LITERAL);
                    mapTokens("", ARG_EMPTY);

            }
            else if (tokens[0].equals("import")) { // import statement
               // skip this shit
            }
            else {
                Assembler::only_compile = true;
                if (errline == -1)
                    errline = linepos;
                cout << "nsc: " << Tokenizer.filen << ":" << Tokenizer.linePos << "  fatal error parsing " << tokens[0] << " token in file. Expected <instruction>.";

            }
   }
   else if (linepos > errline) // wait until a new line has been reached before assembling
        errline = -1;

  for(int i = 0; i < 4; i++)
        tokens[i] = "";
}


