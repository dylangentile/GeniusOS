#pragma once

#include "usefulFunctions.h"
#include "lexer.h"


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

