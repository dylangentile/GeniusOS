#pragma once
#include <string>
//Thank you...http://parsingintro.sourceforge.net/#contents_item_4.1

typedef struct {
	char cargo;
	int sourceIndex, lineIndex, colIndex;
	std::string sourceText;
} Character;

std::string str();