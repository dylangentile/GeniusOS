#include "token.h"
#include "scanner.h"
#include "character.h"
#include <string>

using namespace std;

string show(Token self, bool showLineNumbers, bool align){
	int tokenTypeLen;
	string s;
	string space;
	if(align == true){
		tokenTypeLen = 12;
		space = " ";
	} 
	else
	{
		tokenTypeLen = 0;
		space = "";
	}

	if(showLineNumbers == true){
		s = s + rjust(6, to_string(self.lineIndex)) + rjust(4, to_string(self.colIndex) + "  ");
	}
	else
	{
		s = "";
	}

	if(self.type == self.cargo){
		s = s + ljust(tokenTypeLen, '.', "Symbol") + ":" + " " + self.type;
	} else if (self.type == "Whitspace"){
		s = s + ljust(tokenTypeLen, '.', "Whitespace") + ":" + " " + self.cargo;
	} else {
		s = s + ljust(tokenTypeLen, '.', self.type) + ":" + " " + self.cargo;
	}
	return s;

}