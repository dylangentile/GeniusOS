#include <stdio.h>
#include <iostream>
#include <fstream>
#include "lexer.h"
#define BUFSIZE 100000

int main(int argc, char const *argv[])
{

	std::string thefile = argv[1];
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



	std::cout << '\n';
	delete mylexer;
	return 0;
}
