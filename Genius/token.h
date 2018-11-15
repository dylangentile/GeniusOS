#pragma once
#include <string>
typedef struct{
	std::string cargo, sourceText;
	int lineIndex, colIndex; 
	std::string type;
} Token;

std::string show(Token self, bool showLineNumbers, bool align);