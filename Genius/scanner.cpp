#include "scanner.h"
#include "character.h"
#include <string>
#include <fstream>

using namespace std;





Scanner::Scanner(){




}
Scanner::~Scanner(){




}



void Scanner::initialize(string sourceTextArg){
	
	std::ifstream ifs(sourceTextArg);
  	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
	sourceText = content;
	lastIndex = sourceText.length() - 1;
	sourceIndex = -1;
	lineIndex = 0;
	colIndex = -1;
}

Character Scanner::getChar(){
	sourceIndex += 1;
	if(sourceIndex > 0){
		if(sourceText[sourceIndex - 1] == '\n'){
			//previous character was a newline so we start a new line and increment;
			lineIndex += 1;
			colIndex = -1;
		}
	}
	colIndex += 1;
	Character w;
	if(sourceIndex > lastIndex){
		w.cargo = "\0";
		w.lineIndex = lineIndex;
		w.colIndex = colIndex;
		w.sourceIndex = sourceIndex;
		w.sourceText = sourceText;
	}
	else
	{
		w.cargo = sourceText[sourceIndex];
		w.lineIndex = lineIndex;
		w.colIndex = colIndex;
		w.sourceIndex = sourceIndex;
		w.sourceText = sourceText;
	}

	return w;
}
