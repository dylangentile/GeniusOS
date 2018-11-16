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

	std::string lookahead(int offset);


private:
	std::string sourceText;
 	int lastIndex, sourceIndex, lineIndex, colIndex;
};