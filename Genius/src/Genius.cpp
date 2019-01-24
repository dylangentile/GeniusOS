#include <stdio.h>
#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"
#include "arginterpreter.h"
#include "usefulFunctions.h"
#define BUFSIZE 100000
//sytax == input outputdir --verbose/-v ||/&& --quick/-q
int main(int argc, char const *argv[])
{
	std::string temp;
	std::string thefile = argv[1];
	if (argc > 1 ){
		if(temp[0] != "-"){
		std::string theoutput = argv[2];
		}
	}
	else{
	std::string theoutput = "a.txt";
	}
	//Scanner *myscanner = new Scanner;

	/*
    FILE *fp = fopen(argv[1], "r"); 

    char buff[BUFSIZE]; 
    while(fgets(buff, BUFSIZE - 1, fp) != NULL) 
    {
       

        printf ("%s\n", buff); 

    }

fclose(fp);
	*/
/*
	Character z;

	std::cout << "\nHere are the characters returned by the scanner:\n" << "  line col  character\n";
	myscanner->initialize(thefile);

	z = myscanner->getChar();
	while(true){
		std::cout << str(z) << '\n';
		//std::cout << z.lineIndex << "\t" << z.colIndex << "\t" << z.cargo << '\n';
		if(z.cargo == "\0"){
			break;
		}

		z = myscanner->getChar();
	}
*/
/*
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


*/
	ArgReader *myargreader = new ArgReader;
	myargreader->readArgs(arg, argv);
	

	Parser myparser = new Parser;
	std::string ast;
	UsefulFunc *myrecursor = new UsefulFunc;
	ast = myparser->parse(thefile, myargreader->verbosity);
	std::cout << myrecursor->recursiveOut(80, "~") << "Here is the abstract syntax tree:" << myrecursor->recursiveOut(80, "~");
	bool test = recursiveOut->writeOut(ast, theoutput);
	if(!test){
		std::cout << "\n\nSomething prevented my from outputting your ast. I did all that work, parsing, tokenizing, scanning, etc. And this is the thanks your system gives me! Damn you!\n\n";
	} else{
		std::cout << ast;
	}



	std::cout << '\n';
	delete myparser;
	delete myargreader;
	delete myrecursor;
	return 0;
}
