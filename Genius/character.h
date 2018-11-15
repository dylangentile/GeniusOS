#pragma once
#include <string>
//Thank you...http://parsingintro.sourceforge.net/#contents_item_4.1

std::string rjust(int x, std::string s);


typedef struct {
	std::string cargo;
	int sourceIndex, lineIndex, colIndex;
	std::string sourceText;
} Character;

std::string str(Character token);