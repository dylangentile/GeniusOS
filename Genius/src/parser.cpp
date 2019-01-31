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
Parser::errFormat(string append, int where, string msg, bool color){
	if(color)
	{
		return (append+"\n\tIn File:\033[1m"+theTokenArray.at(where).sourceName + "\033[0m:\033[31;1m" + to_string(theTokenArray.at(where).lineIndex) + "\033[0m:\033[31;1m" + to_string(theTokenArray.at(where).colIndex) + "\033[0m...:\n\t\t"+ msg + "\n");
	}
	return (append+"\n\tIn File:"+theTokenArray.at(where).sourceName + ":" + to_string(theTokenArray.at(where).lineIndex) + ":" + to_string(theTokenArray.at(where).colIndex) + "...:\n\t\t"+ msg + "\n");

}

void
Parser::throwError(int errorId, int where, string msg){
	//0 improper casting
	//1 improper Syntax
	//2 wrong value for type 
	switch(errorId){
		case 0: retMsg += errFormat("\nGeneral Error\n\tCode:'0'", where, msg);
			break;
		case 1: retMsg += errFormat("\nGeneral Error:\n\tCode:'1'",where, msg);
			break;
		case 2: retMsg += errFormat("\nGeneral Error:\n\tCode:'2'",where, msg);
			break;
		case 3: retMsg += errFormat("\nCommon Error:\n\tCode:'3'", where, "Expected Semicolon, Comma, or another statement");
			break;
		case 4:	retMsg += errFormat("\nCommon Error:\n\tCode:'4'", where, "Reached EndOfFile before EndOfStatement");
			break;
		case 666: retMsg += "\nSatanic Error\n\tCode:'666'\n\t\tThis error sucks. It means something didn't work at: " + msg + "but the compiler doesn't know why, somehow.\n";
			break;
	}

	worked = false;
}


bool
Parser::commaedInits(int stBeg, int idTwothTokenPos){
	cout << "\n\n";
	int j = idTwothTokenPos;
	cout << "\nStart";
	cout << "\n\nJ="<<j;
	while(true)
	{
		cout << "\nBegin";
		int mody = -1;
		if(theTokenArray.at(stBeg+j).cat == kCat_COMMA){
			cout << "\nComma";
			mody = 1;
		}
		if(theTokenArray.at(stBeg+j).cat == kCat_IDENTIFIER)
		{
			cout << "\nID";
			if(theTokenArray.at(stBeg+1+j).cat == kCat_COMMA)
			{
				cout << "\nId+Comma";
				auto temp = make_tuple(stBeg+j, -1);
				cout << "\nAdded to vector: " << stBeg+j << "=-1\n";

				initId.push_back(temp);
				mody = 2;
			} else if(theTokenArray.at(stBeg+1+j).type == kToken_SEMICOLON){
				cout << "\nId+Semi";
				auto temp = make_tuple(stBeg+j, -1);
				cout << "\nAdded to vector: " << stBeg+j << "=-1\n";
				initId.push_back(temp);
				j++;
				break;
			}
			else if(theTokenArray.at(stBeg+1+j).type == kToken_EQUALS)
			{
				cout << "\nEquals";
				if(theTokenArray.at(stBeg+2+j).cat == kCat_VALUE)
				{
					cout << "\nValue";
					if(theTokenArray.at(stBeg+2+j).type == theTokenArray.at(stBeg).type)
					{
						cout << "\nMatching Types";
						auto temp = make_tuple(stBeg+j, stBeg+2+j);
						initId.push_back(temp);
						cout << "\nAdded to vector: " << stBeg+j << "=" << stBeg+j+2 << "\n";
						mody = 3;

					} 
					else
					{
						throwError(2, stBeg+1, ("The value: " + theTokenArray.at(stBeg+3).cargo + " is an invalid value for " + theTokenArray.at(stBeg+1).cargo + " of type " + theTokenArray.at(stBeg).cargo));
						return false;
					}
				} 
				else
				{
					throwError(1, stBeg+3+j, ("Identifier: " + theTokenArray.at(stBeg+1).cargo + " was a assigned a non-value: " + theTokenArray.at(stBeg+3).cargo));
					return false;
				}
			}
			else
			{
				throwError(3, stBeg+1+j);
				return false;
			}
		}
		else if(theTokenArray.at(stBeg+j).type == kToken_SEMICOLON)	
		{
				break;		
		}
		if(mody == -1){
			throwError(1, stBeg, "SubCode:'***' You managed to get the file reader to run in an infinte loop. You're probably missing a semicolon, so I've spit out that error. It could be something else that no error has been written for...");
			throwError(3, stBeg);
			return false;
		}
		j += mody;
	}
	return true;
}

bool 
Parser::statement(){
	cout << "\n";
	cout << "\n\nStbeg"<< stBeg;
	int stLen = stBeg;
	cout << "\n\nStleng" << stLen << "\n\n";
	while(theTokenArray.at(stLen).type != kToken_SEMICOLON || theTokenArray.at(stLen).type != kToken_CLOSE){
		stLen++;
		if(stLen >= theTokenArray.size()){
			throwError(4, theTokenArray.at(stBeg).lineIndex);
			return false;
		}
	}
	cout << "\n\nStLeng = " << stLen;
	cout << "\n\n\n";

	if(theTokenArray.at(stBeg).cat == kCat_TYPE)
	{
		cout << "\nType";
		if(theTokenArray.at(stBeg+1).cat == kCat_IDENTIFIER)
		{
			cout << "\nID";
			if(theTokenArray.at(stBeg+2).type == kToken_EQUALS)
			{
				cout << "\nEquals";
				if(theTokenArray.at(stBeg+3).cat == kCat_VALUE)
				{
					cout << "\nValue";
					if(theTokenArray.at(stBeg+3).type == theTokenArray.at(stBeg).type){
						cout << "\nMatching type";
						if(theTokenArray.at(stBeg+4).type == kToken_SEMICOLON){
							auto temp = make_tuple(stBeg+1, stBeg+3);
							initId.push_back(temp);
						}
						else if(theTokenArray.at(stBeg+4).type == kToken_COMMA)
						{
							cout << "\nBegin commed inits";
							auto temp = make_tuple(stBeg+1, stBeg+3);
							initId.push_back(temp);
							bool result = commaedInits(stBeg, 5);
							if(!result){
								return false;
							}

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
				cout << "\nSemi";
				auto temp = make_tuple(stBeg+1, -1);
				initId.push_back(temp);
			}
			else if(theTokenArray.at(stBeg+2).type == kToken_COMMA)
			{
				//vector<tuple<int, int>> initId; //idetifer token id num to be init, and the token with the value's id(not its value) 
				cout << "\nOGCommaedINITS";
				auto ter = make_tuple(stBeg+1, -1); 
				initId.push_back(ter);
				bool result = commaedInits(stBeg, 3);
				cout << "\ndiod it";
				if(!result){
					return false;
				}
			} 
			else if(theTokenArray.at(stBeg+2).type == kToken_LPAREN)
			{
				if(theTokenArray.at(stBeg+3).type == kToken_RPAREN){
					if(theTokenArray.at(stBeg+4).type = kToken_OPEN){
						cout << "\nFunction!\n";
						int tst = stBeg+4;
						while(theTokenArray.at(tst).type != kToken_CLOSE){
							tst++;
							if(tst >= theTokenArray.size()){
								throwError(4, stBeg);
								return false;
							}
							else{
								stBeg = tst + 1;
								//make function;
							}
						}
					}
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
	//continue to next statement;
	stBeg += stLen + 1;
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
	//cout << "\nArrSz="<< arraySize << "\nCArrSize:" << theTokenArray.size() << "\n\n";
	for(int i = 0; i < theTokenArray.size(); i++){
		cout << i << ":" <<theTokenArray.at(i).cargo <<"\n";
	}
	bool x = true;
	while(worked == true && x == true){
		if(stBeg >= theTokenArray.size()){
			break;
		}
		x = statement();
	}
	if(!x){
		retMsg +=  "\n\nGenius Compiler Version: " + retVersion() + " failed to compile " + srcFile + " during parsing.\n1\n";
	}
	for(int i = 0; i < initId.size(); i++){
		auto t = initId.at(i);
		cout << "\n" << get<0>(t) << ":" << get<1>(t);
	}
	return retMsg;

}





