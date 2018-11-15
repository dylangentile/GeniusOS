#include <stdio.h>
#include <iostream>
#include <iomanip>
#include "character.h"
#define BUFSIZE 100000

int main(int argc, char const *argv[])
{
    FILE *fp = fopen(argv[1], "r"); 

    char buff[BUFSIZE]; 
    while(fgets(buff, BUFSIZE - 1, fp) != NULL) 
    {
       

        printf ("%s\n", buff); 

    }

fclose(fp);  
std::cout << '\n';
return 0;
}