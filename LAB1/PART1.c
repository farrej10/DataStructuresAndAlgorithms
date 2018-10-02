#include  <stdio.h>


int  main ( int argc , char *argv[] ) {
const int MAXNAME = 24;

char name[MAXNAME];
int age;
printf("Name >> ");
scanf("%s", name);
printf("Age >> ");
scanf("%d", &age);

printf("\n");
printf("Name >> %s\n", name);
printf("Age >> %d\n", age);
printf("Hello %s", name);
printf(" (%d)\n", age);



return  0;
}