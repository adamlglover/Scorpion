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
string funcName(string token);
bool hasString(string *array, string value);
string typeToString(int type);
int tokenType(string token);
bool isDigit(char digit);
bool isLetter(char letter);

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
stringstream token, fName, lastFunc;
bool instring = false, processedcommand, charLiteral = false;
bool inclass = false, inmodule = false;
string tokens[ 4 ];
int argsize, argoverflow, labelOffset = 0, tpos = 0;
string special = "", member_func = "", WORKING_DIR = "";

int arg1Types[ 6 ];
int arg2Types[ 6 ];
int arg3Types[ 6 ];

string instructions[82] = { // native VM instruction code
            "halt","breakp","rhalt","chalt","add","sub","mult","div","rem","inc",
            "dec","and","or","xor","not","nand","nor","xnor",
            "loadi","loadbl","push","return","call","swp","loop",
            "end","endl","do","mov","rmov","invoke","ilt","igt","ile","ige",
            "ndo","inlt","ingt","inle","inge","neg","lock","ulock","xreg","clx","rloop",
            "wloop","endwl","same","nac","sr","sl","r_mv","cpuid","rdtsc",
            "print","rand_1","rand_2","rand_3","printf","loadc","dload","t_cast",
            "sload","loadf","rln","rload","ct_int","anum","sleep","cp",
            "string", "adr", "r_load", "strcp", "e2str", "strcpi", "swi", "array",
            "aload", "aaload", "throw"
    };

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
            special = "{";
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
            special = "";
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
   fName.str("");
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

void mapTokens(string token, int tType)
{
  cout << "mapping: " << token << " type: " << tType << endl;
}

bool hasint(int *arry, int val)
{
    for(int i = 0; i < sizeof(arry); i++){
        if(arry[i] == val)
          return true;
    }
   return false;
}

bool hasExpectedType(int argn, int arg)
{
    if(argn == 0)
      return hasint(arg1Types, arg);
    if(argn == 1)
      return hasint(arg2Types, arg);
    if(argn == 2)
      return hasint(arg3Types, arg);
    return false;
}

int etype(int argn, int index)
{
    if(argn == 0)
      return arg1Types[index];
    if(argn == 1)
      return arg2Types[index];
    if(argn == 2)
      return arg3Types[index];
    return UNKNOWN;
}

bool is_flabel(string label)
{
   if(label.at(0) == '.' && label.at(label.size() - 1) == ':'){
       bool hasLetter = false;
            for (int i = 1; i < label.size() - 1; i++) {
                if (!isDigit(label.at(i)) && !(label.at(i) == '_'))
                    return false;
                if(isLetter(label.at(i)) && !hasLetter)
                    hasLetter = true;

            }

           if(!hasLetter)
               return false;
           else
               return true;
   }
}

int errline = -1;
void parse()
{

   if(errline == -1) {
     if (hasString(instructions, tokens[0])) { // is command
                    mapTokens(tokens[0], COMMAND);

                for (int i = 0; i < argsize; i++) {
                    // parse arguments
                    if (hasExpectedType(i, tokenType(tokens[i + 1]))) {
                           if(tokens[0] == "push" && i == 0)
                              member_func = tokens[i + 1];
                           mapTokens(tokens[i + 1], tokenType(tokens[i + 1]));
                    } else {
                        Assembler::compile_only = true;
                        if(member_func != "!"){
                           cout << fName.str() << ": In member function " << member_func << ":" << endl;
                        }
                        cout << "nsc: " << fName.str() << ":" << linepos << ": error:  expected '" << typeToString(etype(i, 0)) << "' or '" <<
                                typeToString(etype(i, 1)) << "' or '" << typeToString(etype(i, 2)) <<
                                "'. Found type \"" << typeToString(tokenType(tokens[i + 1])) << "\".";
                    }

                }

                    if (flag != 3) {
                        for (int i = 0; i < argoverflow; i++)
                             mapTokens("", ARG_EMPTY);
                    } else
                       flag = 1;

            } else if(is_flabel(tokens[0])) { // .func:(this one done manually)

                    mapTokens("push", COMMAND);
                    mapTokens(funcName(tokens[0]), LABEL);
                    mapTokens(funcName(tokens[0]) + "_b", LABEL);
                    mapTokens("", ARG_EMPTY);
                    lastFunc.str("");
                    lastFunc << tokens[0];
                    member_func = funcName(tokens[0]);

            }
            else if (tokens[0] == "&&idx_offset:"){ // idx offset manipulation
                    if(tokenType(tokens[1]) == INTEGER_LITERAL)
                        labelOffset += atoi(tokens[1].c_str());
                    else {
                        Assembler::compile_only = true;
                        if (errline == -1)
                           errline = linepos;
                        if(member_func != "!"){
                           cout << fName.str() << ": In member function " << member_func << "():" << endl;
                        }
                        cout << "nsc: " << fName.str() << ":" << linepos << ": error:  expected integer literal. Found type \""
                        << typeToString(tokenType(tokens[1])) << "\".";
                    }

            }
            else if (tokens[0] == "&&working_dir:") { // idx offset manipulation
                stringstream dir;
                for(int i = 1; i < tokens[1].length() - 1; i++)
                    dir << tokens[1].at(i);
                WORKING_DIR = dir.str();
            }
            else if (tokens[0] == "ret") { // ret <function>(this one done manually)
                    mapTokens("return", COMMAND);
                    mapTokens(funcName(lastFunc.str()), LABEL);
                    mapTokens("0", INTEGER_LITERAL);
                    mapTokens("", ARG_EMPTY);
                    member_func = "!";
            }
            else if (tokens[0] == "import") { // import statement
               // skip this shit
            }
            else {
                Assembler::compile_only = true;
                if (errline == -1)
                    errline = linepos;
                cout << "nsc: " << fName.str() << ":" << linepos << ": error:  expected instruction before \"" << tokens[0] << "\".";

            }
   }
   else if (linepos > errline) // wait until a new line has been reached before assembling
        errline = -1;

  for(int i = 0; i < 4; i++)
        tokens[i] = "";
}

string funcName(string token) {
    string name = "";
    for (int i = 1; i < token.size() - 1; i++) {
        name += "" + token.at(i);
    }
    return name;
}


bool hasString(string *array, string value){

            for(int i = 0; i < sizeof(array); i++){

                if(value == array[i])
                    return true;

            }

        return false;
}

string typeToString(int type)
{
        if(type == NULLPTR)
           return "nullptr";
        else {

            if(type == RESERVED)
               return "reserved";
            if(type == SPECIAL)
               return "special";
            else if(type == STRING_LITERAL)
               return "string literal";
            else if(type == RAM_ADDRESS)
               return "ram address";
            else if(type == REGISTER)
               return "register";
            else if(type == INTEGER_LITERAL)
               return "integer";
            else if(type == HEX_LITERAL)
               return "hex literal";
            else if(type == LABEL)
               return "label";
            else
                return "type unknown";
        }
}

bool isReserved(token);
bool isSpecial(token);
bool isStringLiteral(token);
bool isRamAddress(token);
bool isRegister(token);
bool isIntegerLiteral(token);
bool isHexLiteral(token);
bol

int tokenType(string token){ // find type
        if(token == "null")
            return NULLPTR;
        else {

            if(isReserved(token))
                return RESERVED;
            if(isSpecial(token))
                return SPECIAL;
            else if(isStringLiteral(token))
                return STRING_LITERAL;
            else if(isRamAddress(token))
                return RAM_ADDRESS;
            else if(isRegister(token))
                return REGISTER;
            else if(isIntegerLiteral(token))
                return INTEGER_LITERAL;
            else if(isHexLiteral(token))
                return HEX_LITERAL;
            else if(isLabel(token))
                return LABEL;
            else
                return UNKNOWN;
      }
}

bool isReserved(string token) {
        if(token == "true" )
            return true;
        else if (token == "false")
            return true;
        else if (token == "int")
            return true;
        else if (token == "bool")
            return true;
        else if (token == "char")
            return true;
        else if (token == "float")
            return true;
        else if (token == "double")
            return true;
        else if (token == "short")
            return true;
        return false;
}

bool isSpecial(string token)
{
  return (token == special);
}

bool isStringLiteral(string token) {
        if(charLiteral){
            if((token.size() == 3) && (token.at(0) == '\'' && token.at(token.size() - 1) == '\''))
                return true;
            else if(((token.size() == 3) && (token.at(0) == '\'' && token.at(token.size() - 1) == '\'')) && (token.at(1) == '/')
        }
        else {
            if (token.at(0) == '\'' && token.at(token.size() - 1) == '\'')
                return true;
        }
        return false;
}

bool isDigit(char digit)
{
  if(digit == '0')
     return true;
  else if(digit == '1')
     return true;
  else if(digit == '2')
     return true;
  else if(digit == '3')
     return true;
  else if(digit == '4')
     return true;
  else if(digit == '5')
     return true;
  else if(digit == '6')
     return true;
  else if(digit == '7')
     return true;
  else if(digit == '8')
     return true;
  else if(digit == '9')
     return true;
  return false;
}

bool isLetter(char letter)
{
   return ((((int) letter) >= 65) && ((int) letter) <= 90)) || ((((int) letter) >= 97) && ((int) letter) <= 122));
}

bool isRamAddress(string token) {
        if(token.at(0) == '@' || token.at(0) == '*'){
            for(int i = 1; i < token.size();i++){
                if(isDigit(token.at(i))) { }
                else
                    return false;
            }
            return true;
        }
        return false;
}

boolean isRegister(string token) {
        if(token == "eax")
            return true;
        else if(token == "ebx")
            return true;
        else if(token == "sdx")
            return true;
        else if(token == "bp")
            return true;
        else if(token == "exc")
            return true;
        else if(token == "ps")
            return true;
        else if(token == "lg")
            return true;
        else if(token == "lsl")
            return true;
        else if(token == "sfc")
            return true;
        else if(token == "scx")
            return true;
        else if(token == "i1")
            return true;
        else if(token == "i2")
            return true;
        else if(token == "tmp")
            return true;
        else if(token == "ai")
            return true;
        else if(token == "ipi")
            return true;
        else if(token == "ip")
            return true;
        else if(token == "scr")
            return true;
        else if(token == "i3")
            return true;
        else if(token == "i5")
            return true;
        else if(token == "i6")
            return true;
        else if(token == "i7")
            return true;
        else if(token == "i8")
            return true;
        else if(token == "i9")
            return true;
        else if(token == "i10")
            return true;
        else if(token == "i11")
            return true;
        else if(token == "i12")
            return true;
        else
            return false;
}

bool isIntegerLiteral(string token) {
        int dotCount;
        if(token.at(0) == '#'){
            dotCount = 0;
            for (int i = 1; i < token.length(); i++) {
                if (isDigit(token.at(i)) || (token.at(i) == '.')) {
                    if (token.at(i) == '.') {
                         flag = 3;
                         dotCount++;
                    }

                    if (dotCount > 1)
                        return false;
                } else
                    return false;
            }
        }
        else {
            dotCount = 0;
            for (int i = 0; i < token.length(); i++) {
                if (isDigit(token.at(i)) || (token.at(i) == '.')) {
                    if (token.at(i) == '.') {
                         flag = 3;
                         dotCount++;
                    }

                    if (dotCount > 1)
                        return false;
                } else
                    return false;
            }
        }
        return true;
}

bool array(char txt, char *arry)
{
   for(int i = 0 i < arry.length(); i++){
       if(txt == arry[i])
          return true;
   }
  return false;
}

bool isHexadecimal(String text) {

        char hexDigits[24] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                'a', 'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F', 'x' };

        int hexDigitsCount = 0;

        for (int i = 0; i < text.size(); i++) {
                if (array(text.at(i), hexDigit)) {
                    hexDigitsCount++;
                    break;
                }
        }

        return (hexDigitsCount == text.size());
}

bool isHexLiteral(String token) {
        if(token.charAt(0) == '0' && token.charAt(1) == 'x') {
            if (isHexadecimal(token))
                return true;
        }
        return false;
}

bool isLabel(string token) {
    bool t1  = false, t2 = false, t3 = false;

   {
        bool hasLetter = false;
            for (int i = 0; i < token.size(); i++) {
                if (!isDigit(token.at(i)) && !(token.at(i) == '_') && !isLetter(token.at(i)) && !(token.at(i) == '.'))
                    t1 = false;
                if(isLetter(token.at(i)) && !hasLetter)
                    hasLetter = true;

            }

           if(!hasLetter)
               t1 = false;
           else
               t1 = true;
   }
   {
      bool hasLetter = false, reachedDot = false;
            for (int i = 0; i < token.size(); i++) {
                if(((token.at(i) == '.') && (i == 0)) || ((token.at(i) == '.') && ((i + 1) !< token.size())))
                    return false;

                if (!isDigit(token.at(i)) && !(token.at(i) == '_') && !isLetter(token.at(i)) && !(token.at(i) == '.'))
                    t2 = false;
                if(isLetter(token.at(i)) && !hasLetter)
                    hasLetter = true;
                if(token.at(i) == '.' && !reachedDot)
                    reachedDot = true;
                else if(token.at(i) == '.' && reachedDot)
                    reachedDot = false;
            }

           if(!hasLetter || !reachedDot)
               t2 = false;
           else if(hasLetter && reachedDot)
               t2 = true;
           else
               t2 = false;
   }
   {
      bool hasLetter = false, reachedDot = false;
      int count = 2;
            for (int i = 0; i < token.size(); i++) {
                if(((token.at(i) == '.') && (i == 0)) || ((token.at(i) == '.') && ((i + 1) !< token.size())))
                    return false;

                if (!isDigit(token.at(i)) && !(token.at(i) == '_') && !isLetter(token.at(i)) && !(token.at(i) == '.'))
                    t3 = false;
                if(isLetter(token.at(i)) && !hasLetter)
                    hasLetter = true;
                if(token.at(i) == '.' && !reachedDot){
                    reachedDot = true;
                    count++;
                }
                else if(token.at(i) == '.' && !(count >= 2)){
                    reachedDot = false;
                    count++;
                }
                else
                 reachedDot = false;
            }

           if(!hasLetter || !reachedDot)
               t3 = false;
           else if(hasLetter && reachedDot)
               t3 = true;
           else
               t3 = false;
   }
     if(t1 == true || t2 == true || t3 == true)
        return true;
     else
        return false;
}

