#include "tokenizer.h"
#include "scanner.h"
#include "character.h"
#include "usefulFunctions.h"
#include <string>

using namespace std;
Tokenizer::Tokenizer(){



}

Tokenizer::~Tokenizer(){



	
}



string Tokenizer::show(Token self, bool showLineNumbers, bool align){
	UsefulFunc *myljust = new UsefulFunc;
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
		s = s + myljust->ljust(tokenTypeLen, ".", "Symbol") + ":" + space + self.type;
	} else if (self.type == "Whitspace"){
		s = s + myljust->ljust(tokenTypeLen, ".", "Whitespace") + ":" + space + self.cargo;
	} else {
		s = s + myljust->ljust(tokenTypeLen, ".", self.type) + ":" + space + self.cargo;
	}
	return s;

}

void Tokenizer::abort(Token x, string message){
	lines = x.sourceText.
}