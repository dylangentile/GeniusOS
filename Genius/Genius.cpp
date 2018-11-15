#include <stdio.h>

#define BUFSIZE 1000

int main(int argc, char const *argv[])
{
	
//hello
    FILE *fp = fopen(argv[1], "r"); 

    char buff[BUFSIZE]; 
    while(fgets(buff, BUFSIZE - 1, fp) != NULL) 
    {
       

        printf ("%s\n", buff); 
    }
    fclose(fp);  

	return 0;
}