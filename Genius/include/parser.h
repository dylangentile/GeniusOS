#pragma once

#include "usefulFunctions.h"
#include "lexer.h"
#include <vector>

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



class Parser{
public:

	Parser();
	~Parser();
	bool statement();
	std::string parse(std::string srcFile, bool verbosity);
	bool worked;

private:
	Token fetchToken();
	void throwError(int errorId, std::string msg = "");
	

private:
	Lexer *mylexer;
	bool verbose;
	std::vector <Token> theTokenArray;
	std::string retMsg;
};

