#include  <stdio.h>
#include <stdlib.h>

int hash(char* s){
    int hash = 0;
    while (*s)
    {
        hash = hash + *s;
        s++;
    }
    return hash;

}




int  main(int argc, char *argv[]) {



	return  0;

}

