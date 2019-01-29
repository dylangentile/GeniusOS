#pragma once
#include "character.h"
#include <string>

//test
class Scanner{


public:
	Scanner();
	~Scanner();


	void initialize(std::string file);
	Character getChar();

	std::string lookahead(int offset, bool retwps = false);


private:
	std::string msourceText, filename;
 	int mlastIndex, msourceIndex, mlineIndex, mcolIndex;
};