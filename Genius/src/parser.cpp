#include "parser.h"

using namespace std;

Parser::Parser(){

	mylexer = new Lexer;
	theToken.cargo = "GENIUSCOMPILERIMEMPTY";


}

Parser::~Parser(){

	delete mylexer;


}

Token Parser::fetchToken(){
	if(verbose){
		if(theToken != "GENIUSCOMPILERIMEMPTY"){
			
		}
	}
}


string Parser::parse(string srcFile, bool v){
	verbose = v;


	mylexer->lexerhandler(srcFile); 



}



