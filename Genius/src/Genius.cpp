#include <stdio.h>
#include <iostream>
#include <fstream>
#include "statement.h"
#include "lexer.h"
#include "parser.h"
#include "arginterpreter.h"
#include "usefulFunctions.h"
#include "interpreter.h"
#define BUFSIZE 100000
//sytax == input outputdir --verbose/-v ||/&& --quick/-q
int main(int argc, char const *argv[])
{
	std::string temp;
	std::string thefile = argv[1];
	std::string theoutput = "a.txt";
	/*if (argc > 1 ){
		if(temp[0] != "-"){
		theoutput = argv[2];
		}
	}
	else{
	theoutput = "a.txt";
	}
	*/











// OLD Lexer Handler. --Works well for testing, prints out the tokens along with what it thinks they are...


	Token tok, initializer;

	Lexer *mylexer = new Lexer;
	initializer = mylexer->lexerhandler(thefile);

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
            //std::cout << "hello:" << tok.cargo << '\n';
		if(tok.type == kToken_EOF){
			break;
		}
	}
	
	std::cout << "\n\n\n";




	//END OLD CODE/HANDLERS

	ArgReader *myargreader = new ArgReader;
	myargreader->readArgs(argc, argv);
	
	Parser *myparser = new Parser;
	FuncStatement *gFunc = new FuncStatement;
	Interpreter *theInterpreter = new Interpreter;
	//UsefulFunc *myrecursor = new UsefulFunc;
	std::string msg = myparser->begin(thefile, true, gFunc);
	msg += theInterpreter->interpret(gFunc);

	std::cout << msg;
	



	

	std::cout << '\n';
	//delete myparser;
	//delete myargreader;
	//delete myrecursor;
	return 0;
}
