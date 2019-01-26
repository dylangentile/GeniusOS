#pragma once

//stl includes, etc.
#include <string>
#include <vector> 
#include <set>

//local includes
#include "lexer.h"
/*
typedef struct{
	Token token;
	int level;
	std::set<std::string> children;
	void add(Node self);
	void addNode(Node self);
	std::string toString(Node self);

} Node;
*/

class Parser{
public:

	Parser();
	~Parser();

	std::string parse(std::string srcFile, bool verbosity);

private:
	Token fetchToken();
	

private:
	Lexer *mylexer;
	bool verbose;
	Token theToken;
	std::string retMsg;
};

