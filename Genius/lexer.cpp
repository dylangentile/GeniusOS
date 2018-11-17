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

void Lexer::getCharPackage(){
	Character readChar;
	readChar = myscanner->getChar();
	c1 = readChar.cargo;
	c2 = c1 + myscanner->lookahead(1);
}

Token Lexer::lexerMain()
{
	Token *mytoken = new Token;
	Token retPackage;
	while(find(begin(WhitespaceChars), end(WhitespaceChars), c1) || c2== "/*")
	{
		while (find(begin(WhitespaceChars), end(WhitespaceChars), c1))
		{
			retPackage.type = "Whitespace";
			getCharPackage();
			while (find(begin(WhitespaceChars), end(WhitespaceChars), c1))
			{
			retPackage.cargo += c1;
			getCharPackage();
			}
			return retPackage;
		} 
		while(c2 == "/*")
		{
			retPackage.type = "Comment";
			retPackage.cargo = c2;
			getCharPackage();
			getCharPackage();

			while(c2 != "*/")
			{
				if(c1 ==  "\0")
				{
					mytoken->abort(retPackage, "Found end of file before end of comment");
				}
				retPackage.cargo += c1;
				getCharPackage();	
			}
			retPackage.cargo += getCharPackage();
			getCharPackage();
			getCharPackage();
		}

	}





	if(c1 == "\0")
	{
		retPackage.type = "EOF";
	}
	if(c1 in IDENTIFIER_STARTCHARS)
	{
		retPackage.type = "IDENTIFIER";
		getCharPackage();
		while(c1 in IDENTIFIER_CHARS)
		{
			retPackage.cargo += c1;
			getCharPackage();
		}
		if(retPackage in Keywords){retPackage.type = retPackage.cargo;} //c++ implementation of this concept needed... :(
		return retPackage;
	}

	if (c1 in NUMBER_STARTCHARS)
	{
		retPackage.type = "NUMBER";
		getCharPackage();

		while (c1 in NUMBER_CHARS)
		{
			retPackage.cargo += c1;
			getCharPackage();
		}
		return retPackage;
	}
	if(c1 in STRING_STARTCHARS){
		string quoteChar = c1;
		getCharPackage();

		while(c1 != quoteChar){
			if (c1 == "\0"){
				mytoken->abort(retPackage, "Found end of file before string literal");
			}
			retPackage.car += c1;
			getCharPackage();
		}
		retPackage.cargo += c1;
		getCharPackage();
		retPackage.type = "STRING";
		return retPackage;
	}
	if(c2 in TwoCharacterSymbols){
		retPackage.cargo = c2;
		retPackage.type = retPackage.cargo;
		getCharPackage();
		getCharPackage();
		return retPackage;
	}
	if(c1 in OneCharacterSymbols){
		retPackage.type = retPackage.cargo;
		getCharPackage();
		return retPackage;
	}

	mytoken->abort(retPackage, "I've found a character or symbol that's unrecognizeable: \"" + c1 + "\"");
	return retPackage;
}


