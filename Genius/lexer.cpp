#include "scanner.h"
#include "tokenizer.h"
#include "character.h"
#include "geniusSymbols.h"
#include <algorithm> //for find
#include <iterator>
#include <vector>


Lexer::Lexer(){

}
Lexer::~Lexer(){

}

void Lexer::lexerInit(string srcTxtArg){
	static Scanner *myscanner = new Scanner;
	myscanner->initialize(srcTxt);
}

Token Lexer::lexerMain()
{
	Token retPackage;
	if(g != 5){
		x1 = getChar();
	}
	g = 7;
	Character x2 = getChar();//fix this!!!!
	x2.cargo = x1.cargo + x2.cargo;
	if(find(begin(WhitespaceChars), end(WhitespaceChars), x1.cargo) || x2.cargo == "/*")
	{
		if(find(begin(WhitespaceChars), end(WhitespaceChars), x1.cargo))
		{
		retPackage.type = "Whitespace";
		retPackage.cargo += x1;
		return retPackage;
		} else{
			retPackage.type = "Comment";
			retPackage.cargo = x2;
			Character g;
			while(true){
				Character z = getChar();
				if(g.cargo + z.cargo == "*/" || z.cargo == "\0"){
					break;
				}
				g = z;
			}
		}

	}

}

void Lexer::getCharPackage(){
	Character readChar;
	readChar = myscanner->getChar();
	c1 = readChar.cargo;
	c2 = c1 + myscanner->lookahead(1);
}
