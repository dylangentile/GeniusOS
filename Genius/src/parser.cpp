#include "parser.h"
using namespace std;
/*
Node::Node(){

}

Node::~Node(){

}
*/

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
		return (append+"\n\tIn File:\033[1m"+theTokenArray.at(where).sourceName + "\033[0m:\033[31;1m" + to_string(theTokenArray.at(where).lineIndex + 1) + "\033[0m:\033[31;1m" + to_string(theTokenArray.at(where).colIndex + 1) + "\033[0m...:\n\t\t"+ msg + "\n");
	}
	return (append+"\n\tIn File:"+theTokenArray.at(where).sourceName + ":" + to_string(theTokenArray.at(where).lineIndex+1) + ":" + to_string(theTokenArray.at(where).colIndex+1) + "...:\n\t\t"+ msg + "\n");

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
		case 5: retMsg += errFormat("\nDumb Error:\n\tCode:'5'", where, "Unexpected character(s)!");
			break;
		case 666: retMsg += "\nSatanic Error\n\tCode:'666'\n\t\tThis error sucks. It means something didn't work at: " + msg + "but the compiler doesn't know why, somehow.\n";
			break;
	}

	worked = false;
}


bool
Parser::commaedInits(int stBeg, int idTwothTokenPos){
	int j = idTwothTokenPos;
	while(true)
	{
		int mody = -1;
		if(theTokenArray.at(stBeg+j).cat == kCat_COMMA){
			mody = 1;
		}
		if(theTokenArray.at(stBeg+j).cat == kCat_IDENTIFIER)
		{
			if(theTokenArray.at(stBeg+1+j).cat == kCat_COMMA)
			{
				auto temp = make_tuple(stBeg+j, -1);

				//inputit
				mody = 2;
			} else if(theTokenArray.at(stBeg+1+j).type == kToken_SEMICOLON){
				auto temp = make_tuple(stBeg+j, -1);
				//inputit
				j++;
				break;
			}
			else if(theTokenArray.at(stBeg+1+j).type == kToken_EQUALS)
			{
				if(theTokenArray.at(stBeg+2+j).cat == kCat_VALUE)
				{
					if(theTokenArray.at(stBeg+2+j).type == theTokenArray.at(stBeg).type)
					{
						auto temp = make_tuple(stBeg+j, stBeg+2+j);
						//inputit

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
Parser::statement(FuncStatement *gFunc){
	cout << "\n";
	cout << "\n\nStbeg"<< stBeg;
	int stLen = stBeg;
	cout << "\n\nStleng" << stLen << "\n\n";
	while(theTokenArray.at(stLen).type != kToken_SEMICOLON && theTokenArray.at(stLen).type != kToken_CLOSE){
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
		if(theTokenArray.at(stBeg+1).cat == kCat_IDENTIFIER)
		{
			if(theTokenArray.at(stBeg+2).type == kToken_EQUALS)
			{
				if(theTokenArray.at(stBeg+3).cat == kCat_VALUE)
				{
					if(theTokenArray.at(stBeg+3).type == theTokenArray.at(stBeg).type){
						if(theTokenArray.at(stBeg+4).type == kToken_SEMICOLON){
							VarStatement *thestatement = new VarStatement;
							thestatement->mName = theTokenArray.at(stBeg+1).cargo;
							thestatement->mType = theTokenArray.at(stBeg);
							thestatement->mValue = theTokenArray.at(stBeg+3);
							gFunc->mStatementVector.push_back(thestatement);

						}
						else if(theTokenArray.at(stBeg+4).type == kToken_COMMA)
						{
							auto temp = make_tuple(stBeg+1, stBeg+3);
							//inputit
		
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
				auto temp = make_tuple(stBeg+1, -1);
				//inputit
			
			}
			else if(theTokenArray.at(stBeg+2).type == kToken_COMMA)
			{
				auto ter = make_tuple(stBeg+1, -1); 
				//inputit
				bool result = commaedInits(stBeg, 3);
				if(!result){
					return false;
				}
			} 
			else if(theTokenArray.at(stBeg+2).type == kToken_LPAREN)
			{
				cout << "\nlParen";
				if(theTokenArray.at(stBeg+3).type == kToken_RPAREN)
				{ cout << "\nrParen";
					if(theTokenArray.at(stBeg+4).type == kToken_OPEN)
					{
						cout << "\nFunction!\n";
						int tst = stBeg+4;
						while(theTokenArray.at(tst).type != kToken_CLOSE)
						{
							tst++;
							if(tst >= theTokenArray.size())
							{
								throwError(4, stBeg);
								return false;
							}
							else
							{
								stBeg = tst + 1;
								//make function;
							}
						}
					}
				} 
				else if(theTokenArray.at(stBeg+3).cat == kCat_TYPE)
				{
					cout << "\nType";
				} 
				else
				{
					throwError(5, stBeg+3);
					return false;
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
	if(theTokenArray.at(stBeg).cat == kCat_IDENTIFIER)
	{
		if(theTokenArray.at(stBeg+1).type == kToken_EQUALS)
		{
			if(theTokenArray.at(stBeg+2).cat == kCat_VALUE)
			{
							}
		}
		else if(theTokenArray.at(stBeg+1).type == kToken_DOT)
		{

		}
		else if(theTokenArray.at(stBeg+1).type == kToken_ARROW){

		} else{
			//followed by unknown.
		}
	}
	//continue to next statement;
	stBeg += (stLen - stBeg) + 1;
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
	FuncStatement *gFunc = new FuncStatement;
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


/*
	vector<Token> tokenVector;
	vector<Token>::iterator it;
	tokenVector = theTokenArray;


	for (it = tokenVector.begin(); it != tokenVector.end();  it++)
	{
		Token theToken = *it;
		





	}
*/
	//cout << "\nArrSz="<< arraySize << "\nCArrSize:" << theTokenArray.size() << "\n\n";
	for(int i = 0; i < theTokenArray.size(); i++){
		cout << i << ":" <<theTokenArray.at(i).cargo <<"\n";
	}
	bool x = true;
	while(worked == true && x == true){
		if(stBeg >= theTokenArray.size()){
			break;
		}
		x = statement(gFunc);
	}
	if(!x){
		retMsg +=  "\n\nGenius Compiler Version: " + retVersion() + " failed to compile " + srcFile + " during parsing.\n1\n";
	}
	//for(int i = 0; i < debugIndex.size(); i++)
	{
		gFunc->printem();

		//cout << "\n" << debugIndex.at(i) << ":" << j->second;
	}
	return retMsg;

}





