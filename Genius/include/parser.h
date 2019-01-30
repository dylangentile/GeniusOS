#pragma once

#include "usefulFunctions.h"
#include "lexer.h"
#include <vector>
#include <tuple>
#include <stdexcept>

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
	void throwError(int errorId, int where, std::string msg = "");
	
	std::string errFormat(std::string append, int where, std::string msg);
private:
	Lexer *mylexer;
	bool verbose;
	std::vector <Token> theTokenArray;
	std::map<std::string, std::tuple<int, Token, std::vector<int>>> identifierNameMap; //the map_key is the identifier, tuple(location in token array, the token, which tokens it's connected too.)
	std::map<int, std::tuple<std::string, Token, std::vector<int>>> identifierMap; // map that is keyed with the token's id number.
	std::vector<std::tuple<int, int>> initId; //idetifer token id num to be init, and the token with the value's id(not its value) 

	std::string retMsg;
	int stBeg;
};

