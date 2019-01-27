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
	}
		return mylexer->lexerhandler();
}


string Parser::parse(std::string srcFile, bool verbosity){
	verbose = verbosity;
	Token tok, initializer;

	mylexer = new Lexer;
	initializer = mylexer->lexerhandler(srcFile);

	while(true){
		tok = mylexer->lexerhandler();
		if(tok.type == kToken_EOF){
			std::cout << "EOF\n";
		}else if(tok.type != kToken_WHITESPACE && tok.type != kToken_TAB && tok.type != kToken_NEWLINE && tok.type != kToken_COMMENT && tok.type != kToken_UNKNOWN){
		std::cout << mylexer->tokenWrapper(tok, true, true) << "\n";
        }else if (tok.type == kToken_UNKNOWN){
            std::cout << "UNKNOWN:UNKNOWN" << "\n";
        } else{
        std::string output = "WHITESPACE";
        std::cout << "        WHITESPACE..:" << output <<"\n";
        }
		if(tok.type == kToken_EOF){
			break;
		}
		if(mylexer->doabort == true){
			retMsg = "Genius Compiler Version: " + retVersion() + " failed to compile " + srcFile + "\n1\n"; 
			break;
		}
	}

	return retMsg;

}





