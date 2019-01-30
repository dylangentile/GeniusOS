#include "parser.h"
using namespace std;

Node::Node(){

}

Node::~Node(){

}


Parser::Parser(){
	worked = true;
	stBeg =0;

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
		case 3: retMsg = errFormat("Common Error:\n\tCode:'3'", where, "Expected Semicolon, Comma, or another statement");
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
	cout << "\n\n\n";

	if(theTokenArray.at(stBeg).cat == kCat_TYPE)
	{
		if(theTokenArray.at(stBeg+1).cat == kCat_IDENTIFIER)
		{
			if(theTokenArray.at(stBeg+2).type == kToken_EQUALS)
			{
				if(theTokenArray.at(stBeg+3).cat == kCat_VALUE)
				{
					if(theTokenArray.at(stBeg+3).type == theTokenArray.at(stBeg).type){
						if(4 == stLen){
							//create initialized variable
						}
						else
						{
							throwError(3, stBeg+4);
						}
					} 
					else
					{
						throwError(2, stBeg+1, ("The value: " + theTokenArray.at(stBeg+3).cargo + " is an invalid value for " + theTokenArray.at(stBeg+1).cargo + " of type " + theTokenArray.at(stBeg).cargo));
					}
				} 
				else
				{
					throwError(1, stBeg+3, ("Identifier: " + theTokenArray.at(stBeg+1).cargo + " was a assigned a non-value: " + theTokenArray.at(stBeg+3).cargo));
				}
			}
			else if (theTokenArray.at(stBeg+2).type == kToken_SEMICOLON)
			{
				//create uninitialized variable;
			}
			else if(theTokenArray.at(stBeg+2).type == kToken_COMMA)
			{
				int j = 3;
				//vector<tuple<int, int>> initId; //idetifer token id num to be init, and the token with the value's id(not its value) 
				auto ter = make_tuple(stBeg+1, -1); 
				initId.push_back(ter);
				while(true)
				{
					int mody = 0;
					//cout << "yodawg";
					if(theTokenArray.at(stBeg+j).cat == kCat_IDENTIFIER)
					{
						cout << "\nidentifier";
						if(theTokenArray.at(stBeg+1+j).cat == kCat_COMMA)
						{
							cout << "\ncomma";
							auto temp = make_tuple(stBeg+j, -1);
							initId.push_back(temp);
							mody = j + 2;
						}
						else if(theTokenArray.at(stBeg+1+j).type == kToken_SEMICOLON)
						{
							cout << "\nsemi";
							break;
							
						}
						else if(theTokenArray.at(stBeg+1+j).type == kToken_EQUALS)
						{
							cout << "\nfound equals";
							if(theTokenArray.at(stBeg+2+j).cat == kCat_VALUE)
							{
								cout << "\nfound value";
								if(theTokenArray.at(stBeg+2+j).type == theTokenArray.at(stBeg).type)
								{
									cout << "\nFound matching types";
									auto temp = make_tuple(stBeg+j, stBeg+2+j);
									cout << "\nasdfsadf";
									initId.push_back(temp);
									cout << "\nyodawg";
									mody = j + 3;
									cout << "\nassigned";

								} 
								else
								{
									cout << "\nthrwo me a frickin bone hweer?";
									throwError(2, stBeg+1, ("The value: " + theTokenArray.at(stBeg+3).cargo + " is an invalid value for " + theTokenArray.at(stBeg+1).cargo + " of type " + theTokenArray.at(stBeg).cargo));
									break;
								}
							} 
							else
							{
								throwError(1, stBeg+3+j, ("Identifier: " + theTokenArray.at(stBeg+1).cargo + " was a assigned a non-value: " + theTokenArray.at(stBeg+3).cargo));
								break;
							}
						}
						else
						{
							throwError(3, stBeg+1+j);
							break;
						}
					}
					j = mody;
				}
			}
			else
			{
				throwError(0, stBeg+2,("Identifier: " + theTokenArray.at(stBeg+1).cargo + " was cast to type " + theTokenArray.at(stBeg+0).cargo + " but it was followed by: " + theTokenArray.at(stBeg+2).cargo));
				return false;
			}
		}
		else
		{
			throwError(0, stBeg+1, ("The type: \033[33;1m" + theTokenArray.at(stBeg).cargo + "\033[0m is followed by a non identifier: \033[33;1m" + theTokenArray.at(stBeg+1).cargo + "\033[0m"));
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
	for(int i = 0; i < 2; i++){
		auto t = initId.at(i);
		cout << "\n" << get<0>(t) << ":" << get<1>(t);
	}
	return retMsg;

}





