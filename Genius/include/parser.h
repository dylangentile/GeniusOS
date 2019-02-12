#pragma once

#include "usefulFunctions.h"
#include "lexer.h"
#include "statement.h"
#include <vector>
#include <tuple>
#include <stdexcept>
#include <utility>
#include <algorithm> 
#include <iterator>


typedef struct 
{
	int level;
	std::vector<Token> mTermTokVect;
	
}Term;

class Parser{
public:

	Parser();
	~Parser();
	bool statement(FuncStatement *gFunc);
	bool parse(FuncStatement *theFunc);
	std::string begin(std::string srcFile, bool verbosity, FuncStatement *outfunc);
	std::string filesrc;
	bool worked;

private:
	Token fetchToken();
	void throwError(int errorId, int where, std::string msg = "");
	bool commaedInits(int idTwothTokenPos, FuncStatement *theFunc);
	std::string errFormat(std::string append, int where, std::string msg, bool color = true);
	bool equation(FuncStatement *theFunc);

private:
	Lexer *mylexer;
	bool verbose, reachedit;
	std::vector <Token> theTokenArray;
	
	std::string retMsg;
	int stBeg, errcount;
};

