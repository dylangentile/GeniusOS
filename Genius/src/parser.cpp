#include "parser.h"
using namespace std;

Node::Node(){

}

Node::~Node(){

}


Parser::Parser(){
	worked = true;

	mylexer = new Lexer;
}
Parser::~Parser(){

}

string
Parser::errFormat(string append, int where, string msg){
	return (append+"\n\tIn File:\033[1m"+theTokenArray.at(where).sourceName + "\033[0m:\033[31;1m" + to_string(theTokenArray.at(where).lineIndex) + "\033[0m:\033[31;1m" + to_string(theTokenArray.at(where).colIndex) + "\033[0m...:\n\t\t"+ msg + "\n");
}

void
Parser::throwError(int errorId, int where, string msg){
	//0 improper casting
	//1 improper Syntax
	//2 wrong value for type 
	switch(errorId){
		case 0: retMsg = errFormat("General Error\n\tCode:'0'", where, msg);
			break;
		case 1: retMsg = errFormat("General Error:\n\tCode:'1'",where, msg);
			break;
		case 2: retMsg = errFormat("General Error:\n\tCode:'2'",where, msg);
			break;
		case 666: retMsg = "Satanic Error\n\tCode:'666'\n\t\tThis error sucks. It means something didn't work at: " + msg + "but the compiler doesn't know why, somehow.\n";
			break;
	}

	worked = false;
}


bool 
Parser::statement(){
	cout << "\n";
	for(int i = 0; i < theTokenArray.size(); i++){
		cout << i << ":" <<theTokenArray.at(i).cargo <<"\n";
	}

	int stLen = 0;
	while(theTokenArray.at(stLen).type != kToken_SEMICOLON){
		stLen++;
	}

	if(theTokenArray.at(0).cat == kCat_TYPE)
	{
		if(theTokenArray.at(1).cat == kCat_IDENTIFIER)
		{
			if(theTokenArray.at(2).type == kToken_EQUALS)
			{
				if(theTokenArray.at(3).cat == kCat_VALUE)
				{
					if(theTokenArray.at(3).type == theTokenArray.at(0).type){
						if(4 == stLen){
							//create initialized variable
						}
					} 
					else
					{
						throwError(2, 1, ("The value: " + theTokenArray.at(3).cargo + " is an invalid value for " + theTokenArray.at(1).cargo + " of type " + theTokenArray.at(0).cargo));
					}
				} 
				else
				{
					throwError(1, 3, ("Identifier: " + theTokenArray.at(1).cargo + " was a assigned a non-value: " + theTokenArray.at(3).cargo));
				}
			}
			else if (theTokenArray.at(2).type == kToken_SEMICOLON)
			{
				//create uninitialized variable;
			}
			else
			{
				throwError(0, 2,("Identifier: " + theTokenArray.at(1).cargo + " was cast to type " + theTokenArray.at(0).cargo + " but it was followed by: " + theTokenArray.at(2).cargo));
				return false;
			}
		}
		else
		{
			throwError(0, 1, ("The type: \033[33;1m" + theTokenArray.at(0).cargo + "\033[0m is followed by a non identifier: \033[33;1m" + theTokenArray.at(1).cargo + "\033[0m"));
			return false;
		}
	}
	return true; 

}

Token Parser::fetchToken(){
		Token temp = mylexer->lexerhandler();
		while(temp.type == kToken_WHITESPACE || temp.type == kToken_COMMENT){
			temp = mylexer->lexerhandler();
		}
		return temp;
}


string Parser::parse(std::string srcFile, bool verbosity){
	verbose = verbosity;
	Token tok, initializer;
	initializer = mylexer->lexerhandler(srcFile);
	int q = 0;
	while(true){
		tok = fetchToken();


		if(tok.type == kToken_EOF){
			break;
		}
		if(mylexer->doabort == true){
			retMsg = "Genius Compiler Version: " + retVersion() + " failed to compile " + srcFile + " during tokenization.\n1\n"; 
			worked = false;
			break;
		}
		theTokenArray.push_back(tok);
	}
	delete mylexer;
	bool x = true;
	if(worked){
		x = statement();
	}
	if(!x){
		retMsg +=  "\n\nGenius Compiler Version: " + retVersion() + " failed to compile " + srcFile + " during parsing.\n1\n";
	}
	return retMsg;

}





