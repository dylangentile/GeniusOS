#pragma once
#include <string>
//Thank you...http://parsingintro.sourceforge.net/#contents_item_4.1


//python def __init__(self, c, lineIndex, colIndex, sourceIndex, sourceText) order in which he'll input variables;
typedef struct {
	std::string cargo;
	int sourceIndex, lineIndex, colIndex;
	std::string sourceText;
} Character;


std::string rjust(int x, std::string s);
std::string ljust(int x, char filler, std::string s);

std::string str(Character token);