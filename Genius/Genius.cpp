#include <stdio.h>
#include <iostream>
#include <fstream>
#include "scanner.h"
#include "character.h"
#define BUFSIZE 100000

int main(int argc, char const *argv[])
{
	std::ifstream ifs(argv[1]);
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );

	/*
    FILE *fp = fopen(argv[1], "r"); 

    char buff[BUFSIZE]; 
    while(fgets(buff, BUFSIZE - 1, fp) != NULL) 
    {
       

        printf ("%s\n", buff); 

    }

fclose(fp);
	*/
	Character z;

	std::cout << "\nHere are the characters returned by the scanner:\n" << "  line col  character\n";
	initialize(content);

	z = get();
	while(true){
		std::cout << str(z) << '\n';
		//std::cout << z.lineIndex << "\t" << z.colIndex << "\t" << z.cargo << '\n';
		if(z.cargo == "\0"){
			break;
		}

		z = get();
	}

	std::cout << '\n';
	return 0;
}