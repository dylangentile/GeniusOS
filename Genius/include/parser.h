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
/*
typedef enum {
	kNode_OPERATOR,
	kNode_NUMBER
} NodeID;



class Node{
public:
	Node();
	~Node();
	NodeID type;
	NodeID value;
	Node *children;    
};

*/

struct{
	int memOf;
	int assignsTo;
} Function;


class Parser{
public:

	Parser();
	~Parser();
	bool statement(FuncStatement *gFunc);
	std::string parse(std::string srcFile, bool verbosity);
	bool worked;

private:
	Token fetchToken();
	void throwError(int errorId, int where, std::string msg = "");
	bool commaedInits(int stBeg, int idTwothTokenPos);
	std::string errFormat(std::string append, int where, std::string msg, bool color = false);
private:
	Lexer *mylexer;
	bool verbose;
	std::vector <Token> theTokenArray;
	
	std::string retMsg;
	int stBeg;
};

