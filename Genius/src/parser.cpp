#include "parser.h"

using namespace std;


Parser::Parser(){
	worked = true;
	stBeg =0;
	mylexer = new Lexer;
	reachedit = false;
	errcount = 0;
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
	errcount++; 
	switch(errorId)
	{
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
		case 6: retMsg += errFormat("\nDumb Error:\n\tCode:'6'", where, "Cannot have a function within a function.");
			break;
		case 7: retMsg += errFormat("\nWildcard Error:\n\tCode:'7'", where, msg);
			break;
		case 8: retMsg += errFormat("\nSilly Error:\n\tCode:'8'", where, "Reallocation of variable/function: " + msg);
			break;
		case 666: retMsg += "\nSatanic Error\n\tCode:'666'\n\t\tThis error sucks. It means something didn't work at: " + msg + "but the compiler doesn't know why, somehow.\n";
			break;
	}

	worked = false;
}





bool 
Parser::equation(FuncStatement *theFunc)
{
	int j;
	vector<TokenID> *opVect;
	if(theTokenArray.at(stBeg).cat == kCat_IDENTIFIER)
	{
		if(theTokenArray.at(stBeg+1).type == kToken_EQUALS)
		{
			if(theTokenArray.at(stBeg+2).cat == kCat_VALUE)
			{
				opVect->push_back(theTokenArray.at(stBeg+2).type);
				j =1;
				while(true)
				{
					int mody;
					if(theTokenArray.at(stBeg+j).type == kToken_SEMICOLON)
					{
						opVect->push_back(kToken_SEMICOLON);
						break;
					}
					else if(theTokenArray.at(stBeg+j).cat == kCat_VALUE)
					{
						if(theTokenArray.at(stBeg).type == theTokenArray.at(stBeg+j).type)
						{
							opVect->push_back(theTokenArray.at(stBeg).type);
							mody = 1;
						}
						else
						{
							throwError(2, stBeg+j, "Invalid value for type.");
							return false;
						}
					} 
					else if(theTokenArray.at(stBeg+j).cat == kCat_OPERATOR)
					{
						if(theTokenArray.at(stBeg+j+1).cat == kCat_VALUE)
						{
							opVect->push_back(theTokenArray.at(stBeg+j).type);
							mody = 1;
						} else{
							throwError(5, stBeg+j, theTokenArray.at(stBeg+j).cargo + " is Followed by a non-value: " +theTokenArray.at(stBeg+j+1).cargo);
							return false;
						}
					} 
					else
					{
						throwError(666, stBeg+j);
						return false;
					}
					j += mody;

				}

			} 
			else
			{
				throwError(5, stBeg, theTokenArray.at(stBeg).cargo + " is Followed by a non-value: " +theTokenArray.at(stBeg+2).cargo);
				return false;
			}
		}
		else 
		{

		}
	} 
	else 
	{

	}

	for(int i = stBeg; i < (stBeg+j); i++)
	{
		int z = i - stBeg;
		if(opVect->at(z) == kToken_LPAREN)
		{
			int qtmp = z + 1;
			while(true)
			{
				while(true)
				{
					if(((qtmp - 1)+stBeg) >= stBeg+j){
						throwError(5, (qtmp+stBeg)-1, "didn't find a closing parenthese!");
						return false;
					}
					if(opVect->at(qtmp) == kToken_LPAREN)
					{
						break;
					}
					if(opVect->at(qtmp) == kToken_RPAREN)
					{
						break;
					}
					qtmp++;
				}
				if(opVect->at(qtmp) == kToken_RPAREN){
					break;
				}
				if(!(opVect->at(qtmp) == kToken_LPAREN)){
					throwError(5, (qtmp+stBeg)-1);
					return false;
				}
			}
		}

	}


}

bool
Parser::commaedInits(int idTwothTokenPos, FuncStatement *theFunc){
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
				Token temp;
				temp.type = theTokenArray.at(stBeg+j).type;
				temp.cat = kCat_VALUEUNSET;
				if(theFunc->compare(theTokenArray.at(stBeg+j).cargo)){
					throwError(8, stBeg+j, theTokenArray.at(stBeg+j).cargo);
					return false;
				}
				VarStatement *thestatement = new VarStatement;
				thestatement->mName = theTokenArray.at(stBeg+j).cargo;
				thestatement->mType = theTokenArray.at(stBeg);
				thestatement->mValue = temp;
				theFunc->mStatementVector.push_back(thestatement);				
				mody = 2;
			} 
			else if(theTokenArray.at(stBeg+1+j).type == kToken_SEMICOLON)
			{
				Token temp;
				temp.type = theTokenArray.at(stBeg+j).type;
				temp.cat = kCat_VALUEUNSET;
				if(theFunc->compare(theTokenArray.at(stBeg+j).cargo)){
					throwError(8, stBeg+j, theTokenArray.at(stBeg+j).cargo);
					return false;
				}
				VarStatement *thestatement = new VarStatement;
				thestatement->mName = theTokenArray.at(stBeg+j).cargo;
				thestatement->mType = theTokenArray.at(stBeg);
				thestatement->mValue = temp;
				theFunc->mStatementVector.push_back(thestatement);
				j++;
				break;
			}
			else if(theTokenArray.at(stBeg+1+j).type == kToken_EQUALS)
			{
				if(theTokenArray.at(stBeg+2+j).cat == kCat_VALUE)
				{
					if(theTokenArray.at(stBeg+2+j).type == theTokenArray.at(stBeg).type)
					{
						
						if(theFunc->compare(theTokenArray.at(stBeg+j).cargo)){
							throwError(8, stBeg+j, theTokenArray.at(stBeg+j).cargo);
							return false;
						}
						VarStatement *thestatement = new VarStatement;
						thestatement->mName = theTokenArray.at(stBeg+j).cargo;
						thestatement->mType = theTokenArray.at(stBeg+j);
						thestatement->mValue = theTokenArray.at(stBeg+j+2);

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

#include <stdlib.h>

bool 
Parser::statement(FuncStatement *theFunc){
	
	int stLen = stBeg;
	if(theTokenArray.at(stBeg).type  == kToken_CLOSE){
		reachedit = true;
		return true;
	}
	while(theTokenArray.at(stLen).type != kToken_SEMICOLON && theTokenArray.at(stLen).type != kToken_CLOSE){
		stLen++;
		if(stLen >= theTokenArray.size()){
			throwError(4, theTokenArray.at(stBeg).lineIndex);
			return false;
		}
	}
	

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
							if(theFunc->compare(theTokenArray.at(stBeg+1).cargo)){
								throwError(8, stBeg+1, theTokenArray.at(stBeg+1).cargo);
								return false;
							}

							VarStatement *thestatement = new VarStatement;
							thestatement->mName = theTokenArray.at(stBeg+1).cargo;
							thestatement->mType = theTokenArray.at(stBeg);
							thestatement->mValue = theTokenArray.at(stBeg+3);
							theFunc->mStatementVector.push_back(thestatement);

						}
						else if(theTokenArray.at(stBeg+4).type == kToken_COMMA)
						{
							if(theFunc->compare(theTokenArray.at(stBeg+1).cargo)){
								throwError(8, stBeg+1, theTokenArray.at(stBeg+1).cargo);
								return false;
							}
							VarStatement *thestatement = new VarStatement;
							thestatement->mName = theTokenArray.at(stBeg+1).cargo;
							thestatement->mType = theTokenArray.at(stBeg);
							thestatement->mValue = theTokenArray.at(stBeg+3);
							theFunc->mStatementVector.push_back(thestatement);
		
							bool result = commaedInits(5, theFunc);
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
				Token temp;
				temp.type = theTokenArray.at(stBeg).type;
				temp.cat = kCat_VALUEUNSET;
				if(theFunc->compare(theTokenArray.at(stBeg+1).cargo)){
					throwError(8, stBeg+1, theTokenArray.at(stBeg+1).cargo);
					return false;
				}
				VarStatement *thestatement = new VarStatement;
				thestatement->mName = theTokenArray.at(stBeg+1).cargo;
				thestatement->mType = theTokenArray.at(stBeg);
				thestatement->mValue = temp;
				theFunc->mStatementVector.push_back(thestatement);
			
			}
			else if(theTokenArray.at(stBeg+2).type == kToken_COMMA)
			{
				Token temp;
				temp.type = theTokenArray.at(stBeg).type;
				temp.cat = kCat_VALUEUNSET;
				if(theFunc->compare(theTokenArray.at(stBeg+1).cargo)){
					throwError(8, stBeg+1, theTokenArray.at(stBeg+1).cargo);
					return false;
				}
				VarStatement *thestatement = new VarStatement;
				thestatement->mName = theTokenArray.at(stBeg+1).cargo;
				thestatement->mType = theTokenArray.at(stBeg);
				thestatement->mValue = temp;
				theFunc->mStatementVector.push_back(thestatement);
				bool result = commaedInits(3, theFunc);
				if(!result){
					return false;
				}
			} 
			else if(theTokenArray.at(stBeg+2).type == kToken_LPAREN)
			{
	

				if(theTokenArray.at(stBeg+3).type == kToken_RPAREN)
				{ 
					if(theTokenArray.at(stBeg+4).type == kToken_OPEN)
					{
						int tst = stBeg+4;
						while(theTokenArray.at(tst).type != kToken_CLOSE)
						{
							tst++;
							if(tst >= theTokenArray.size())
							{

								throwError(4, stBeg);
								return false;
							}
						}
						if(theFunc->mName != "global")
						{
							throwError(6, stBeg);
							return false;
						}

						if(theFunc->compare(theTokenArray.at(stBeg+1).cargo)){
							throwError(8, stBeg+1, theTokenArray.at(stBeg+1).cargo);
							return false;
						}
						FuncStatement *pointfunc = new FuncStatement;
						pointfunc->mName = theTokenArray.at(stBeg+1).cargo;
						pointfunc->mType = theTokenArray.at(stBeg);
						stBeg = stBeg+5;
						int verytemp = stBeg;
						parse(pointfunc);
						theFunc->mStatementVector.push_back(pointfunc);
						stBeg = verytemp;
						stLen = tst;
						

					}
					else
					{
						throwError(7, stBeg+4, "Expected: '{'  but got: '" + theTokenArray.at(stBeg+4).cargo + "'");
						return false;
					}
				} 
				else if(theTokenArray.at(stBeg+3).cat == kCat_TYPE)
				{
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
				if(theTokenArray.at(stBeg+3).type == kToken_SEMICOLON){

				}
				else{
					equation(theFunc);
				}
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

string
Parser::begin(std::string srcFile, bool verbosity, FuncStatement *gFunc){
	verbose = verbosity;
	filesrc = srcFile;
	Token tok, initializer;
	initializer = mylexer->lexerhandler(srcFile);
	while(true){
		tok = fetchToken();


		if(tok.type == kToken_EOF){
			break;
		}
		if(mylexer->doabort == true){
			retMsg = "Genius Compiler Version: " + retVersion() + " failed to compile " + srcFile + " during tokenization."; 
			worked = false;
			break;
		}
		theTokenArray.push_back(tok);
	}

	delete mylexer;
	/*
	for(int i = 0; i < theTokenArray.size(); i++){
		cout << i << ":" <<theTokenArray.at(i).cargo <<"\n";
	}
	*/
	
	
	gFunc->mName = "global";
	if(!parse(gFunc)){
		retMsg +=  "\n\nGenius Compiler Version: " + retVersion() + " failed to compile " + filesrc + " during parsing.\n\nGenius[Errors]: " + to_string(errcount);
	}
	//gFunc->print(1);
	return retMsg;
}



bool Parser::parse(FuncStatement *theFunc){
	
	bool x = true;
	while(worked == true && x == true){
		if(stBeg >= theTokenArray.size()){
			break;
		}
		x = statement(theFunc);
		if(reachedit){
			break;
		}
	}
	reachedit = false;
	if(!worked){
		return false;
	}


	if(!x){
		return false;
	}
	return true;

}





