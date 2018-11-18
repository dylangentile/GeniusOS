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
	Token tok;

	Lexer *mylexer = new Lexer;
	mylexer->lexerInit(thefile);

	while(true){
		tok = mylexer->lexerMain();
		std::cout << mylexer->tokenWrapper(tok, false, true);
		if(tok.type == kToken_EOF){
			break;
		}
	}



	std::cout << '\n';
	return 0;
}