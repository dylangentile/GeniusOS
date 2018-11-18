#include "character.h"
#include "usefulFunctions.h"
using namespace std;
//#define ENDMARK "\0"

UsefulFunc *myrjust = new UsefulFunc;


string str(Character token){
	if(token.cargo == " "){
		token.cargo = "   space";
	}
	else if(token.cargo == "\n")
	{
		token.cargo = "   newline";
	}else if(token.cargo == "\t")
	{
		token.cargo = "   tab";
	}else if(token.cargo == "\0")
	{
		token.cargo = "   eof";
	}


string ret = (myrjust->rjust(6, to_string(token.lineIndex))) + (myrjust->rjust(4, to_string(token.colIndex))) + "  " + token.cargo;

return ret;
}