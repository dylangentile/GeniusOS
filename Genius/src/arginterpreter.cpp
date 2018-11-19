#include "arginterpreter.h"
#include <string>

using namespace std;

ArgReader::ArgReader(){
	verbosity = false;
	quickly = false;

}

ArgReader::~ArgReader(){


}

ArgReader::readArgs(int argcNum, char const *args[]){
	string tempArg;
	int g, i = 3;
	tempArg = args[2];
	if(tempArg[0] == "-"){
		i = 2;
	}
	for (i < argcNum; i++) //we start at 3 since 1 & 2 are the input/output dirs
	{
		tempArg = args[i];
		g = 0;
		if(tempArg == "--verbose" || tempArg = "-v"){
			verbosity = true;
			g++;
		}
		if(tempArg == "--quick" || tempArg == "-q"){
			quickly = true;
			g++:
		}
		if(g <= 0){
			//invalid args exception blah blah.
		}


	}
}