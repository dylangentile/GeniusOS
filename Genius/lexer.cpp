//#include "tokenizer.h"
#include "lexer.h"
//#include "geniusSymbols.h"
#include <algorithm> //for find
//#include <iterator>
#include <vector>
#include <iostream>
#include <utility>


using namespace std;

Lexer::Lexer(){


//insert(std::make_pair(key, T()))


	mKeywordMap.insert(make_pair("if", kToken_IF));
	mKeywordMap.insert(make_pair("then",kToken_THEN));
	mKeywordMap.insert(make_pair("else",kToken_ELSE));
	mKeywordMap.insert(make_pair("while",kToken_WHILE));
	mKeywordMap.insert(make_pair("loop",kToken_LOOP));
	mKeywordMap.insert(make_pair("endloop",kToken_ENDLOOP));
	mKeywordMap.insert(make_pair("print",kToken_PRINT));
	mKeywordMap.insert(make_pair("return",kToken_RETURN));
	mKeywordMap.insert(make_pair("exit",kToken_EXIT));

	mOperatorMap.insert(make_pair("=",kToken_EQUALS));
	mOperatorMap.insert(make_pair("(",kToken_LPAREN));
	mOperatorMap.insert(make_pair(")",kToken_RPAREN));
	mOperatorMap.insert(make_pair("<",kToken_LESSTHAN));
	mOperatorMap.insert(make_pair(">",kToken_GREATERTHAN));
	mOperatorMap.insert(make_pair("/",kToken_DIVIDE));
	mOperatorMap.insert(make_pair("*",kToken_MULTIPLY));
	mOperatorMap.insert(make_pair("+",kToken_PLUS));
	mOperatorMap.insert(make_pair("-",kToken_MINUS));
	mOperatorMap.insert(make_pair("!",kToken_BANG));
	mOperatorMap.insert(make_pair("&",kToken_AND));
	mOperatorMap.insert(make_pair(".",kToken_DOT));
	mOperatorMap.insert(make_pair(";",kToken_SEMICOLON));
	mOperatorMap.insert(make_pair("==",kToken_EQUALITY));
	mOperatorMap.insert(make_pair("<=",kToken_LESSEQUAL));
	mOperatorMap.insert(make_pair(">=",kToken_GREATEREQUAL));
	mOperatorMap.insert(make_pair("!=",kToken_NOTEQUAL));
	mOperatorMap.insert(make_pair("++",kToken_INCREMENT));
	mOperatorMap.insert(make_pair("^",kToken_EXP));
	mOperatorMap.insert(make_pair("--",kToken_DECREMENT));
	mOperatorMap.insert(make_pair("+=",kToken_PLUSEQUALS));
	mOperatorMap.insert(make_pair("-=",kToken_MINUSEQUALS));
	mOperatorMap.insert(make_pair("||",kToken_OR));
	mIdentifierMap.insert(make_pair("\"",kToken_QUOTE));
	mIdentifierMap.insert(make_pair("string",kToken_STRING));
	mIdentifierMap.insert(make_pair("num",kToken_NUMBER));
	
	
	




myscanner = new Scanner;


	/*	["if"] = kToken_IF;
	mKeywordMap["then"] = kToken_THEN;
	mKeywordMap["else"] = kToken_ELSE;
	mKeywordMap["while"] = kToken_WHILE;
	mKeywordMap["loop"] = kToken_LOOP;
	mKeywordMap["endloop"] = kToken_ENDLOOP;
	mKeywordMap["print"] = kToken_PRINT;
	mKeywordMap["return"] = kToken_RETURN;
	mKeywordMap["exit"] = kToken_EXIT;
	*/



	//vector<string> OneCharSymbols{'=','(',')','<','>','/','*','+','-','!','&','.',';'};

	//vector<string> TwoCharSymbols{'==','<=','>=','<>','!=','++','**','--','+=','-=','||'};
	//vector<string> StringStartChars{"'",'"'};
	//vector<string> WhitespaceChars{' ', '\t','\n'};




}
Lexer::~Lexer()
{
	delete myscanner;
}

string
Lexer::tokenWrapper(Token self, bool showLineNumbers, bool align)
{
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
		s = s + myljust->rjust(6, to_string(self.lineIndex)) + myljust->rjust(4, to_string(self.colIndex) + "  ");
	}
	else
	{
		s = "";
	}

	if((isTwoCharOperator(self.cargo) == self.type) || (isOneCharSymbol(self.cargo) == self.type)){
		s = s + myljust->ljust(tokenTypeLen, "SYMBOL", ".") + ":" + space + "tokentype";
	} else if (self.type == kToken_WHITESPACE){
		s = s + myljust->ljust(tokenTypeLen, "WHITESPACE", ".") + ":" + space + self.cargo;
	} else {
		s = s + myljust->ljust(tokenTypeLen, "tp", ".") + ":" + space + self.cargo;
	}
	return s;

}


void Lexer::abort(Token x, string msg){
	cout << "You made a boo boo. Here descriptive error description: " << msg;
}

void Lexer::lexerInit(string srcTxtArg)
{
	myscanner->initialize(srcTxtArg);
}

TokenID 
Lexer::isTwoCharOperator(string op){
	if(op.length() != 2){
		return kToken_UNKNOWN;
	}

	map<string, TokenID>::iterator j = mOperatorMap.find(op);
	if(j == mOperatorMap.end()){
		return kToken_UNKNOWN;
	}

	return j->second;
}

TokenID
Lexer::isOneCharSymbol(string sy){
	if(sy.length() != 1){
		return kToken_UNKNOWN;
	}
	map<string, TokenID>::iterator z = mOperatorMap.find(sy);
	if(z == mOperatorMap.end()){
		return kToken_UNKNOWN;
	}

	return z->second;
}

void Lexer::getCharPackage(){
	Character readChar;
	readChar = myscanner->getChar();
	c1 = readChar.cargo;
	c2 = c1 + myscanner->lookahead(1);
}

bool Lexer::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool
Lexer::isNumberStart(string num){
return (is_number(to_string(num[0])));
}

TokenID
Lexer::isKeyword(string i_keyword)
{
	map<string,TokenID>::iterator it = mKeywordMap.find(i_keyword);
	if (it == mKeywordMap.end())
		return kToken_UNKNOWN;
		
	return it->second;

}

bool 
Lexer::isWhitespaceChar(std::string i_char)
{
	int len = i_char.length(); 

	return (len == 1 && (
		i_char.compare(" ") == 0 || 
		i_char.compare("\n")  == 0 || 
		i_char.compare("\t")  == 0 || 
		i_char.compare("\r") ==0 ));
}

bool 
Lexer::isIdentifierStartChar(std::string i_char)
{


	//IDENTIFIER_CHARS      = string.letters + string.digits + "_"


	char theChar = i_char[0];
	return  (theChar >= 'a' && theChar <= 'z') ||
	 		(theChar >= 'A' && theChar <= 'Z');
}

bool 
Lexer::isIdentifierChar(std::string i_char)
{
	char theChar = i_char[0];
	
	return (isIdentifierStartChar(i_char) ||
		(theChar >= '0' && theChar <= '9') ||
		(theChar == '_'));
}




Token Lexer::lexerMain()
{
	Token retPackage;


	while(isWhitespaceChar(c1) || c2 == "/*")
	{
		while (isWhitespaceChar(c1))
		{
			retPackage.type = kToken_WHITESPACE;
			getCharPackage();
			while (isWhitespaceChar(c1))
			{
			retPackage.cargo += c1;
			getCharPackage();
			}
			return retPackage;
		} 
		while(c2 == "/*")
		{
			retPackage.type = kToken_COMMENT;
			retPackage.cargo = c2;
			getCharPackage();
			getCharPackage();

			while(c2 != "*/")
			{
				if(c1 ==  "\0")
				{
					abort(retPackage, "Found end of file before end of comment");
				}
				retPackage.cargo += c1;
				getCharPackage();	
			}
			retPackage.cargo += c1;
			getCharPackage();
			getCharPackage();
		}

	}





	if(c1 == "\0")
	{
		retPackage.type = kToken_EOF;
	}

	if(isIdentifierStartChar(c1))
	{
		retPackage.type = kToken_IDENTIFIER;
		getCharPackage();
		while(isIdentifierChar(c1))
		{
			retPackage.cargo += c1;
			getCharPackage();
		}


		if (isKeyword(retPackage.cargo) != kToken_UNKNOWN)
		{
			retPackage.type = isKeyword(retPackage.cargo);


		}	

		//if(retPackage in Keywords){retPackage.type = retPackage.cargo;} //c++ implementation of this concept needed... :(
		return retPackage;
	}

	if (isNumberStart(c1)){

		retPackage.type = kToken_NUMBER;
		getCharPackage();

		while (is_number(c1))
		{
			retPackage.cargo += c1;
			getCharPackage();
		}
		return retPackage;
	}
	if(c1 == "\""){
		string quoteChar = c1;
		getCharPackage();

		while(c1 != quoteChar){
			if (c1 == "\0"){
				abort(retPackage, "Found end of file before string literal");
			}
			retPackage.cargo += c1;
			getCharPackage();
		}
		retPackage.cargo += c1;
		getCharPackage();
		retPackage.type = kToken_STRING;
		return retPackage;
	}
	if(isTwoCharOperator(c2) != kToken_UNKNOWN){
		retPackage.cargo = c2;
		retPackage.type = isTwoCharOperator(c2);
		getCharPackage();
		getCharPackage();
		return retPackage;
	}
	if(isOneCharSymbol(c1) != kToken_UNKNOWN){
		retPackage.cargo = c1;
		retPackage.type = isOneCharSymbol(c1);
		getCharPackage();
		return retPackage;
	}

	abort(retPackage, "I've found a character or symbol that's unrecognizeable: \"" + c1 + "\"");
	return retPackage;
}


