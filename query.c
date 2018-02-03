#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define SIZE 10
struct student
{
	char name[30],rno[10],degree[5],branch[10];
}student;
struct course
{
	char cname[30],cno[10],offdept[10];
	int credits;
}course;
struct section
{
	char sid[10],cno[10],faculty[20];
	int sem,year;
}section;
struct prereq
{
	char pno[10],cno[10];
}prereq;
struct grep
{
	char rno[10],sid[10],grade[1];
	float CGPA;
}grep;
void main()
{
	int flag=1;
	int opt,i,j,z;
	FILE *fptr,*fptr1,*fptr2;
	char str[10]="garbage";
	char rollno[10];
			int count=0;
	while(flag)
	{
		printf("To enter details of \n1.student\n2.course\n3.section\n4.prereq\n5.grep\n6.NO ENTRY ------ :");
		scanf("%d",&opt);
		switch(opt){
			case 1:
			fptr=fopen("student.dat","a"); 
			printf("Enter Name,Roll No, Degree and branch of the student\n");
			scanf("%s%s%s%s",student.name,student.rno,student.degree,student.branch);
			fprintf(fptr, "%s %s %s %s\n", student.name,student.rno,student.degree,student.branch);
			fclose(fptr);
			break;
			case 2:
			fptr=fopen("courses.dat","a");
			printf("Enter course name,course number, credits and offering department\n");
			scanf("%s%s%d%s",course.cname,course.cno,&course.credits,course.offdept);
			fprintf(fptr, "%s %s %d %s\n", course.cname,course.cno,course.credits,course.offdept);
			fclose(fptr);
			break;
			case 3:
			fptr=fopen("section.dat","a");
			printf("Enter section ID,Course number,semester,Year and Faculty\n");
			scanf("%s%s%d%d%s",section.sid, section.cno, &section.sem, &section.year, section.faculty);
			fprintf(fptr, "%s %s %d %d %s\n",section.sid, section.cno, section.sem, section.year, section.faculty);
			fclose(fptr);
			break;
			case 4:
			fptr=fopen("prereq.dat","a");
			printf("Enter course number and prerequisites number\n");
			scanf("%s%s",prereq.cno, prereq.pno);
			fprintf(fptr, "%s %s\n",prereq.cno, prereq.pno);
			fclose(fptr);
			break;
			case 5:
			fptr=fopen("grades.dat","a");
			printf("Enter Roll No, section ID and CGPA\n");
			scanf("%s%s%s",grep.rno, grep.sid, grep.grade);
			fprintf(fptr, "%s %s %s\n",grep.rno, grep.sid, grep.grade);
			fclose(fptr);
			break;
			case 6:
			flag=0;
			break;
		}
	}
	flag=1;
	while(flag)
	{
		printf("Querying Options\n1.Find students of COE department.\n2.Display course name and course number offered in 2015.\n3.course names of prerequisites for 'HCI'.\n4.Courses offered by a faculty.\n5.Calculate CGPA of a student\n");
		scanf("%d",&opt);
		switch(opt){
			case 1:
			fptr=fopen("student.dat","r");
			for (i = 0; i < SIZE; ++i)
			{
				fscanf(fptr, "%s %s %s %s", student.name, student.rno, student.degree, student.branch);
				if(strcmp(student.branch,"coe")==0)
					printf("Name: %s *|* Roll No: %s\n", student.name, student.rno);
			}
			printf("\n");
			fclose(fptr);
			break;
			case 2:
			fptr=fopen("section.dat","r");
			for (i = 0; i < SIZE; ++i)
			{
				fscanf(fptr, "%s %s %d %d %s", section.sid, section.cno, &section.sem, &section.year, section.faculty);
				if(section.year==2015)
				{
					fptr1=fopen("courses.dat","r");
					for (j = 0; j < SIZE; ++j)
					{
						fscanf(fptr1, "%s %s %d %s\n", course.cname, course.cno, &course.credits, course.offdept);
						if(strcmp(section.cno,course.cno)==0 && !feof(fptr))
						{
							printf("Course Name: %s *|* Course Number: %s\n", course.cname, course.cno);
							strcpy(course.cno,str);
						}
					}
					fclose(fptr1);
				}
			}
			fclose(fptr);
			break;
			case 3:
			fptr=fopen("courses.dat","r");
			
			
			char pre[10];
			for (i=0; i < SIZE; ++i)
			{
				fscanf(fptr, "%s %s %d %s", course.cname, course.cno, &course.credits, course.offdept);
				if(strcmp(course.cname,"HCI")==0 && !feof(fptr))
				{
					strcpy(pre,course.cno);
				}
			}
			fclose(fptr);
			fptr1=fopen("prereq.dat","r");
			for (j = 0; j < SIZE; ++j)
					{
						fscanf(fptr1, "%s %s\n", prereq.cno, prereq.pno);
						//printf("%s-%s\n", pre,prereq.cno);
						if(strcmp(pre,prereq.cno)==0){
							fptr2=fopen("courses.dat","r");
							//
							printf("%s-%s\n", prereq.cno, prereq.pno);
							for (z = 0; z < SIZE; ++z)
							{
								fscanf(fptr2, "%s %s %d %s\n", course.cname, course.cno, &course.credits, course.offdept);
								//printf("%s\n", course.cname);
								if (strcmp(prereq.pno,course.cno)==0)
								{
									printf("prereq Name: %s *|* prereq course no: %s\n", course.cname, course.cno);
									
								}

							}
							fclose(fptr2);
						}
						
					}
			
			fclose(fptr1);
			
			printf("\n\n");
			break;
			case 4:
			printf("Enter the name of the faculty\n");
			char string[20];
			scanf("%s",string);
			fptr=fopen("section.dat","r");
			for (i = 0; i < SIZE; ++i)
			{
				fscanf(fptr, "%s %s %d %d %s", section.sid, section.cno, &section.sem, &section.year, section.faculty);
				if(strcmp(section.faculty,string)==0)
				{
					fptr1=fopen("courses.dat","r");
					for (j = 0; j < SIZE; ++j)
					{
						fscanf(fptr1, "%s %s %d %s", course.cname, course.cno, &course.credits, course.offdept);
						if(strcmp(section.cno,course.cno)==0 && !feof(fptr))
						{
							printf("Course Name: %s *|* Course Number: %s\n", course.cname, course.cno);
						}
					}
					fclose(fptr1);
				}
			}
			fclose(fptr);
			break;
			case 5:
			printf("Enter the rollno of student to get CGPA\n");
			scanf("%s",rollno);
			grep.CGPA=0.0;
			fptr=fopen("grades.dat","r");
			for (int i = 0; i < SIZE; ++i)
			{
				fscanf(fptr, "%s%s%s", grep.rno, grep.sid, grep.grade);
				if(strcmp(grep.rno,rollno)==0){
					printf("%s%s%s\n", grep.rno, grep.sid, grep.grade);
					count++;
					if(strcmp(grep.grade,"S")==0)
						grep.CGPA=grep.CGPA+10;
					if(strcmp(grep.grade,"A")==0)
						grep.CGPA=grep.CGPA+9;
					if(strcmp(grep.grade,"B")==0)
						grep.CGPA=grep.CGPA+8;
					if(strcmp(grep.grade,"C")==0)
						grep.CGPA=grep.CGPA+7;
					if(strcmp(grep.grade,"D")==0)
						grep.CGPA=grep.CGPA+6;
				}
				strcpy(grep.rno,string);
			}
			printf("CGPA is %f\n",grep.CGPA/count);
			fclose(fptr);
			break;
			case 6:
			flag=0;
			break;
		}
	}
}
