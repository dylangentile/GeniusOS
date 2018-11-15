#pragma once
//Thank you...http://parsingintro.sourceforge.net/#contents_item_4.1

typedef struct {
	char cargo;
	int sourceIndex, lineIndex, colIndex, sourceText;
} Character;