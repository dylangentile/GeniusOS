#include "character.h"
#include <string>
using namespace std;
//#define ENDMARK "\0"
string rjust(int x, string s){
	for(int i = 0; i < x - s.size(); i++)
	{
			s = " " + s;
	}
	return s;
}
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

string ret = rjust(6, to_string(token.lineIndex)) + rjust(4, to_string(token.colIndex)) + "  " + token.cargo;

return ret;
}