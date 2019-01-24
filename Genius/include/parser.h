#pragma once

//stl includes, etc.
#include <string>

//local includes
#include "lexer.h"

class Parser{
public:

	Parser();
	~Parser();

	std::string parse(std::string srcFile, bool verbose);

private:
	Token fetchToken()
	

private:
	Lexer *mylexer;
	bool verbose;
	Token theToken;
	std::string retMsg;
};

