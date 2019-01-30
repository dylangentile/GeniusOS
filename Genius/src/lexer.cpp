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
	mKeywordMap.insert(make_pair("push",kToken_PUSH));
	mKeywordMap.insert(make_pair("return",kToken_RETURN));
	mKeywordMap.insert(make_pair("quit",kToken_QUIT));
	mOperatorMap.insert(make_pair("{", kToken_OPEN));
	mOperatorMap.insert(make_pair(",", kToken_COMMA));
	mOperatorMap.insert(make_pair("}", kToken_CLOSE));
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
	mOperatorMap.insert(make_pair("->", kToken_ARROW));
	mTypeMap.insert(make_pair("\"",kToken_QUOTE));
	mTypeMap.insert(make_pair("string",kToken_STRING));
	mTypeMap.insert(make_pair("num",kToken_NUMBER));
	mTypeMap.insert(make_pair("bool",kToken_BOOL));
	
	myscanner = new Scanner;
	myljust = new UsefulFunc;
}
Lexer::~Lexer()
{
	delete myscanner;
	delete myljust;
}


//type search begin

TokenID
Lexer::typeLookAhead(TokenID y, int &o_look){
	string temp;
	if (y == kToken_NUMBER){
		temp = c2 + myscanner->lookahead(2);
		temp +=  myscanner->lookahead(3, true); //look for whitespace
		if(temp == "num "){
			o_look = 1;
			return kToken_NUMBER;
		}

	}
	if (y == kToken_STRING){
		temp = c2 + myscanner->lookahead(2);
		temp += myscanner->lookahead(3);
		temp += myscanner->lookahead(4);
		temp += myscanner->lookahead(5);
		temp += myscanner->lookahead(6, true); //look for whitespace



		if(temp == "string "){
			o_look = 5;
			return kToken_STRING;
		}
	}
	if (y == kToken_BOOL){
		temp = c2 + myscanner->lookahead(2);
		temp += myscanner->lookahead(3);
		temp += myscanner->lookahead(4, true); //look for whitespace

		if(temp == "bool "){
			o_look = 3;
			return kToken_BOOL;
		}
	}
	o_look = 0;
	return kToken_UNKNOWN;
}


TokenID
Lexer::isTypeStartChars(string x){
	if(x == "nu"){
		return kToken_NUMBER;
	}
	if(x=="st"){
		return kToken_STRING;
	}
	if(x=="bo"){
		return kToken_BOOL;
	}

	return kToken_UNKNOWN;
}


//Type search end



string
Lexer::tokenWrapper(Token self, bool showLineNumbers, bool align)
{
	int tokenTypeLen;
	string s;
	string space;
	if(align == true){
		tokenTypeLen = 16;
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
		

	if(self.type == kToken_WHITESPACE){
		s = s + myljust->ljust(tokenTypeLen, "WHITESPACE", ".") + ":" + space + self.cargo;
	} else if(self.type == kToken_COMMENT){
		s = s + myljust->ljust(tokenTypeLen, "Comment", ".") + ":" + space + self.cargo;
	} else if (self.cat == kCat_OPERATOR){
		s = s + myljust->ljust(tokenTypeLen, "Operator", ".") + ":" + space + self.cargo;
	} else if(self.cat == kCat_VALUE){
		if(self.type == kToken_NUMBER){
		s = s + myljust->ljust(tokenTypeLen, "Value(NUM)", ".") + ":" + space + self.cargo;
		}
		if(self.type == kToken_STRING){
		s = s + myljust->ljust(tokenTypeLen, "Value(STR)", ".") + ":" + space + self.cargo;
		}
		if(self.type == kToken_BOOL){
		s = s + myljust->ljust(tokenTypeLen, "Value(BOOL)", ".") + ":" + space + self.cargo;
		}
	} else if(self.cat == kCat_KEYWORD){
		s = s + myljust->ljust(tokenTypeLen, "Keyword", ".") + ":" + space + self.cargo;
	} else if(self.cat == kCat_TYPE){
		if(self.type == kToken_NUMBER){
		s = s + myljust->ljust(tokenTypeLen, "Type(NUM)", ".") + ":" + space + self.cargo;
		}
		if(self.type == kToken_STRING){
		s = s + myljust->ljust(tokenTypeLen, "Type(STR)", ".") + ":" + space + self.cargo;
		}
		if(self.type == kToken_BOOL){
		s = s + myljust->ljust(tokenTypeLen, "Type(BOOL)", ".") + ":" + space + self.cargo;
		}
	} else if(self.cat == kCat_IDENTIFIER){
		s = s + myljust->ljust(tokenTypeLen, "Identifier", ".") + ":" + space + self.cargo;
	} else if(self.cat == kCat_UNKNOWN){
		s = s + myljust->ljust(tokenTypeLen, "UNKNOWN", ".") + ":" + space + self.cargo;
	}  else if(self.cat == kCat_EOS){
		s = s + myljust->ljust(tokenTypeLen, "EOS", ".") + ":" + space + self.cargo;
	} 
	else {
		s = s + myljust->ljust(tokenTypeLen + 2, "OTHER", ".") + ":" + space + self.cargo;
	}
	return s;

}


void Lexer::abort(Token x, string msg){
	cout << "You made a boo boo. Here's descriptive error description: \n\tIn file "<< fileMbrSv << " at " << lnDex <<":" << clDex << "\n";
	cout <<  "\t\t[" << msg << "]\n";
	getCharPackage();
	doabort = true;
}

void Lexer::lexerInit(string srcTxtArg)
{
	myscanner->initialize(srcTxtArg);
    getCharPackage();
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

	tempSourceTextName = readChar.memberofFile;

	tempSourceText = readChar.sourceText;
	tempLineIndex = readChar.lineIndex;
	tempcolIndex = readChar.colIndex;
}



bool Lexer::isNumberStart(string num, string &finishedCargo, int &loops){
    loops = 0;
    if((num <= "9" && num >= "0"))
    {
        if(num <= "9" && num >= "0")
        {
            if(myscanner->lookahead(1) <= "9" && myscanner->lookahead(1) >= "0")
            {
                loops = 1;
                finishedCargo = num;
                while(true){
                    if(myscanner->lookahead(loops) == " " || isOneCharSymbol(myscanner->lookahead(loops)) || isTwoCharOperator(myscanner->lookahead(loops))){
                        break;
                    }
                    finishedCargo += myscanner->lookahead(loops);
                    loops++;
                }
                return true;
            }
        }
    
        while(true){
            if(myscanner->lookahead(loops) == " " || isOneCharSymbol(myscanner->lookahead(loops)) || isTwoCharOperator(myscanner->lookahead(loops))){
                break;
            }
            finishedCargo += myscanner->lookahead(loops);
            loops++;
        }
        return true;
    
    }
    return false;
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
    //getCharPackage();
    if(c1 == "\0"/* && c1 != ""*/)
    {
        retPackage.type = kToken_EOF;
        return retPackage;
    }
    
    
    if(c1 == ""){
        retPackage.type = kToken_UNKNOWN;
        retPackage.cargo= "GeniusStartofProgramEmptyStringC1";
        getCharPackage();
        return retPackage;
    }
	while(isWhitespaceChar(c1) || c2 == "/*" || c2 == "//")
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
				if(c2 == "/*"){
					getCharPackage();
					abort(retPackage, "ELIMINATE ALL NESTED COMMENTS!!!");
				}
				retPackage.cargo += c1;
				getCharPackage();	
			}
			retPackage.cargo += c1;
			getCharPackage();
			getCharPackage();

            return retPackage;
		}
		while(c2 == "//"){
			retPackage.cargo = c2;
			retPackage.type = kToken_COMMENT;
			getCharPackage();
			getCharPackage();
			while(c1 != "\n"){
				getCharPackage();
			}
			return retPackage;

		}

	}


	if(c1 == ";"){
		retPackage.type = kToken_SEMICOLON;
		retPackage.cargo = ";";
		retPackage.cat = kCat_EOS;
		getCharPackage();
		return retPackage;
	}
	if(c1 == ","){
		retPackage.type = kToken_COMMA;
		retPackage.cat = kCat_COMMA;
		retPackage.cargo = ",";
		getCharPackage();
		return retPackage;
	}		


if(isTypeStartChars(c2) != kToken_UNKNOWN)
	{
		TokenID fill;
		fill = isTypeStartChars(c2);
		int a_lookahead = 0;
		if(typeLookAhead(fill, a_lookahead) != kToken_UNKNOWN)
		{
			string retCargo = c2;
			retPackage.type = fill;//typeLookAhead(fill, a_lookahead);
			getCharPackage();
			for (int i = 0; i < a_lookahead; i++)
			{
				getCharPackage();
				retCargo += c1;
			}
			retPackage.cargo = retCargo;
			retPackage.cat = kCat_TYPE;
			getCharPackage();
			return retPackage;
		}
		
	}


	if(isIdentifierStartChar(c1))
	{
		retPackage.type = kToken_IDENTIFIER;
        retPackage.cargo = c1;
		getCharPackage();
		while(isIdentifierChar(c1))
		{
			retPackage.cargo += c1;
			getCharPackage();
		}


		if (isKeyword(retPackage.cargo) != kToken_UNKNOWN)
		{
			retPackage.type = isKeyword(retPackage.cargo);
			retPackage.cat = kCat_KEYWORD;
			return retPackage;
		}	

		retPackage.cat = kCat_IDENTIFIER;
		//if(retPackage in Keywords){retPackage.type = retPackage.cargo;} //c++ implementation of this concept needed... :(
		return retPackage;
	}

	


    string xy;
    int loopage;
	if (isNumberStart(c1, xy, loopage)){

		retPackage.type = kToken_NUMBER;
        retPackage.cargo = xy;
        for(int x = 0; x < loopage; x++){
            getCharPackage();
        }
        retPackage.cat = kCat_VALUE;
		return retPackage;
	}
	if(c1 == "\""){
		string quoteChar = "\"";
		getCharPackage();
		while(c1 != quoteChar){
			if (c1 == "\0"){
				abort(retPackage, "Found end of file before string literal");
			}
			retPackage.cargo += c1;
			getCharPackage();
		}
		getCharPackage();
		retPackage.type = kToken_STRING;
		retPackage.cat = kCat_VALUE;
		return retPackage;
	}
	if(isTwoCharOperator(c2) != kToken_UNKNOWN){
		retPackage.cargo = c2;
		retPackage.type = isTwoCharOperator(c2);
		getCharPackage();
		getCharPackage();
		retPackage.cat = kCat_OPERATOR;
		return retPackage;
	}
	if(isOneCharSymbol(c1) != kToken_UNKNOWN){
		retPackage.cargo = c1;
		retPackage.type = isOneCharSymbol(c1);
		getCharPackage();
		retPackage.cat = kCat_OPERATOR;
		return retPackage;
	}

	abort(retPackage, "I've found a character or symbol that's unrecognizeable: \"" + c1 + "\"");
	return retPackage;
}




Token Lexer::lexerhandler(string doInit){
	Token finishRet;
	if (doInit == "NULL"){
		finishRet = lexerMain();
		
//cannot call NULL first....
		finishRet.sourceText = srcTxtSv;
		finishRet.sourceName = fileMbrSv;
		finishRet.lineIndex = lnDex;
		finishRet.colIndex = clDex;

		srcTxtSv = tempSourceText;
		fileMbrSv = tempSourceTextName;
		lnDex = tempLineIndex;
		clDex = tempcolIndex;

		return finishRet;
	}
	else
	{
		lexerInit(doInit);
		fileMbrSv = tempSourceTextName;
		srcTxtSv = tempSourceText;
		lnDex = tempLineIndex;
		clDex = tempcolIndex;
		finishRet.type = kToken_UNKNOWN;
		return finishRet;
	}

	return finishRet;

}

