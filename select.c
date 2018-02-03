#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
	char name[30],rno[10],degree[5],branch[10];
}student;
int main(int argc, char *argv[])
{
	
	FILE *fptr;
	/*if(strcmp(argv[1],"all")==0)
	{
		//printf("1\n");
		fptr=fopen(strcat(argv[3],".dat"),"r");
		for (int i = 0; i < 10; ++i)
			{
				fscanf(fptr, "%s %s %s %s", student.name, student.rno, student.degree, student.branch);
				printf("%-30s %10s %5s %10s\n", student.name, student.rno, student.degree, student.branch);
			}
	}*/
	char s[1000];
	fptr=fopen("flightqueries.txt","r");
	while(!feof(fptr))
	{
		fgets(s,1000,fptr);
		printf("%s\n", s);
	}
	return(0);
}