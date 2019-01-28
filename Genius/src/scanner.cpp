#include "scanner.h"
#include "character.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;





Scanner::Scanner(){




}
Scanner::~Scanner(){




}
void Scanner::initialize(string sourceTextArg){
	
	std::ifstream ifs(sourceTextArg);
  	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
	msourceText = content;
	filename = sourceTextArg;
	mlastIndex = msourceText.length() - 1;
	msourceIndex = -1;
	mlineIndex = 0;
	mcolIndex = -1;
}

Character Scanner::getChar(){
	msourceIndex += 1;
	if(msourceIndex > 0){
		if(msourceText[msourceIndex - 1] == '\n'){
			//previous character was a newline so we start a new line and increment;
			mlineIndex += 1;
			mcolIndex = -1;
		}
	}
	mcolIndex += 1;
	Character w;
	if(msourceIndex > mlastIndex){
		w.cargo = "\0";
		w.lineIndex = mlineIndex;
		w.colIndex = mcolIndex;
		w.sourceIndex = msourceIndex;
		w.sourceText = msourceText;
	}
	else
	{
		w.cargo = msourceText[msourceIndex];
		w.lineIndex = mlineIndex;
		w.colIndex = mcolIndex;
		w.sourceIndex = msourceIndex;
		w.sourceText = msourceText;
	}
	w.memberofFile = filename;
	return w;
}

string Scanner::lookahead(int offset){
	int index = msourceIndex + offset;
	stringstream ss;
	string target;
	if(index > mlastIndex){
		return "\0";
	} else{
		ss << msourceText[index];
		ss >> target;
		return target;
	}
}





