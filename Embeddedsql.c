#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>


MYSQL *conn;
   MYSQL_RES *res;
   MYSQL_ROW row;
   unsigned long *lengths;
   unsigned int num_fields;


   char *server = "localhost"; // localhost for accessing local mysql
   char *user = "root";// root for students
   char *password = "mysql"; /* set me first - pwd : iiitdm123 */ 
   char *database = "FLIGHTEMBEDDED"; // Here you need to enter the database name if you have already other wise leave it free.

int showTables(int option)
{
	char Query[500];
	switch(option)
	{
		case 1:
			strcpy(Query,"show columns from Flights");
			break;
		case 2:
			strcpy(Query,"show columns from Aircrafts");
			break;
		case 3:
			strcpy(Query,"show columns from Certified");
			break;
		case 4:
			strcpy(Query,"show columns from Employees");
			break;
	}
	if (mysql_query(conn,Query));
         {
            fprintf(stderr, "%s\n\n", mysql_error(conn));
            //return(1);
         }
        res=mysql_use_result(conn);
        int i=0;
     	while ((row = mysql_fetch_row(res)) != NULL)
      	{
         	num_fields = mysql_num_fields(res);
         	lengths = mysql_fetch_lengths(res);
            printf("|%-15.*s |", (int) lengths[i],row[i] ? row[i] : "NULL");
     	}
   mysql_free_result(res);

}


int showAttributes(int option)
{
	char Query[500];
	switch(option)
	{
		case 1:
			strcpy(Query,"show columns from Flights");
			break;
		case 2:
			strcpy(Query,"show columns from Aircrafts");
			break;
		case 3:
			strcpy(Query,"show columns from Certified");
			break;
		case 4:
			strcpy(Query,"show columns from Employees");
			break;
	}
	if (mysql_query(conn,Query));
         {
            fprintf(stderr, "%s\n\n", mysql_error(conn));
            //return(1);
         }
        res=mysql_use_result(conn);
        int i=0;
     	while ((row = mysql_fetch_row(res)) != NULL)
      	{
         	num_fields = mysql_num_fields(res);
         	lengths = mysql_fetch_lengths(res);
            printf("|%-15.*s |\n", (int) lengths[i],row[i] ? row[i] : "NULL");
     	}
   mysql_free_result(res);

}
int EnterQuery(char Query[])
{
	printf("\n");
	if (mysql_query(conn,Query));
         {
            fprintf(stderr, "%s\n\n", mysql_error(conn));
            //return(1);
         }
        res=mysql_use_result(conn);
        int i=0;
     	while ((row = mysql_fetch_row(res)) != NULL)
      	{
         num_fields = mysql_num_fields(res);
         lengths = mysql_fetch_lengths(res);
         for(i = 0; i < num_fields; i++)
         {
            printf("|%-15.*s |", (int) lengths[i],row[i] ? row[i] : "NULL");

         }
         printf("\n");
     }
   mysql_free_result(res);
   return(0);
}
void DispTables()
{
	char Query7[100]="show tables";
	EnterQuery(Query7);
}





void Create_table()
{
	char Query[500];
	int opt;
	printf("Select the  table you want to create:\n");
	printf("1.Flights\n2.Aircrafts\n3.Certified\n4.Employees\n");
	   scanf("%d",&opt);
	   switch(opt)
	   {
	   		case 1:
	   			strcpy(Query,"create table Flights (flno int, source varchar(20), destination varchar(20), distance int, departs time, arrives time, price int)");
	   			break;
	   		case 2:
	   			strcpy(Query,"create table Aircrafts (aid int, aname varchar(20), cruisingrange int)");
	   			break;
	   		case 3:
	   			strcpy(Query,"create table Certified (eid int, aid int)");
	   			break;
	   		case 4:
	   			strcpy(Query,"create table Employees (eid int, ename varchar(20), salary int)");
	   			break;
	   		default:
	   			printf("Enter a valid option\n");
	   			break;

	   }
	   if (mysql_query(conn, Query)) 
	   {
       fprintf(stderr, "%s\n", mysql_error(conn));
       
   }	
}		

void PK_assign(char table_name[],char attribute[])
{
	char Query[100]="alter table ";
	strcat(Query,table_name);
	char Query1[100]=" add primary key (";
	strcat(strcat(Query1,attribute),")");
	//printf("Query - %s\n", Query);
	if (mysql_query(conn, strcat(Query,Query1))) 
	{
    	fprintf(stderr, "%s\n", mysql_error(conn));
     	
	}
}

void FK_assign(char table_name[],char attribute[],char r_table_name[],char r_attribute[])
{
	char Query[100]="alter table ";
   strcat(Query,table_name);
   char Query1[100]=" add constraint foreign key (";
   strcat(strcat(Query1,attribute),") references ");
   strcat(Query1, strcat(strcat(r_table_name,"("),strcat(r_attribute,")")));
   strcat(Query,Query1);
   if (mysql_query(conn,Query)); 
	{
    	fprintf(stderr, "%s\n", mysql_error(conn));
     	
	}
}

void Insert(int opt)
{
	int flag=1;
	char Query7[500];
	char flno[100],price[100],distance[100],source[200],destination[200],departs[200],arrives[200]; 
	char aid[100],aname[200], cruisingrange[100];
	char eid[100];
	char ename[300], salary[100];
	while(flag)
	{
		printf("%d\n", opt);
		switch(opt)
		{
			case 1:
				printf("Enter flno, source, destination, distance, departs, arrives, price: \n");
                scanf("%s%s%s%s%s%s%s",flno, source, destination, distance, departs, arrives, price);
                char Query1[500]="insert into Flights values (";
                strcat(flno,",\"");
                strcat(Query1, flno);
                strcat(source,"\",\"");
                strcat(Query1, source);
                strcat(destination,"\",");
                strcat(Query1, destination);
                strcat(distance,",\"");
                strcat(Query1, distance);
                strcat(departs,"\",\"");
                strcat(Query1, departs);
                strcat(arrives,"\",");
                strcat(Query1, arrives);
                strcat(Query1, price);
                strcat(Query1,")");
    			if (mysql_query(conn, Query1))
    			{
    				fprintf(stderr, "%s\n", mysql_error(conn));
     				
    			}printf("\n\n");
   				strcpy(Query7,"select * from Flights");
    			break;
    		case 2:
    			printf("Enter aid, aname, cruisingrange\n");
	            scanf("%s%s%s",aid,aname,cruisingrange);
	            char Query2[500]="insert into Aircrafts values (";
	            strcat(aid,"\",\"");
                strcat(Query2, aid);
                strcat(aname,"\",");
                strcat(Query2, aname);
                strcat(Query2, cruisingrange);
                strcat(Query2,")");
    			if (mysql_query(conn, Query2))
    			{
    				fprintf(stderr, "%s\n", mysql_error(conn));
     				
    			}
    			printf("\n\n");
    			strcpy(Query7,"select * from Aircrafts");
    			break;
    		case 3:
	    		printf("Enter aid and eid\n");
	            scanf("%s%s", aid, eid);
	            char Query3[500]="insert into Certified values (";
	            strcat(aid,",");
	            strcat(Query3,aid);
	            strcat(Query3,eid);
	            strcat(Query3,")");
	             printf("%s\n", Query3);
    			if (mysql_query(conn, Query3))
    			{
    				fprintf(stderr, "%s\n", mysql_error(conn));
     				
    			}
    			printf("\n\n");
    			strcpy(Query7,"select * from Certified");
    			break;
    		case 4:
    			printf("Enter eid, ename, salary\n");
               scanf("%s%s%s", eid, ename, salary);
               char Query4[500]="insert into Employees values (";
               strcat(eid,",\"");
               strcat(Query4,eid);
               strcat(ename,"\",");
               strcat(Query4,ename);
               strcat(Query4,salary);
               strcat(Query4,")");
    			if (mysql_query(conn, Query4))
    			{
    				fprintf(stderr, "%s\n", mysql_error(conn));
    			}
    			printf("\n\n");
    			strcpy(Query7,"select * from Employees");
    			break;
    		default:
    			printf("\n\n");
    			flag=0;
    			break;
    	}
    	showTables(opt);
    	EnterQuery(Query7);
    	printf("Enter next set of values (or) to exit enter 5\n");
    	int x;
    	scanf("%d",&x);
    	if (x==5)
    	{
    		flag=0;
    	}
	}
}


void Delete(char table_name[],int opt)
{
	char Query[500]="delete from ";
	strcat(Query,table_name);
	int and;
	char condition[200];
	if (opt>0)
	{
		strcat(Query," where ");
	}
	while(opt--)
	{
		printf("Enter the condition\n");
		scanf(" %999[^\n]",condition);
		if (opt!=0)
		{
			printf("Enter 1 for AND and 0 for OR\n");
			scanf("%d",&and);
			if(and==1)
				strcat(condition," and ");
			else
				strcat(condition," or ");
		}
		strcat(Query, condition);
	}
	printf("Query -************ %s\n", Query);
	

	if (mysql_query(conn, Query))
    {
    	fprintf(stderr, "%s\n", mysql_error(conn));

    }
    char display[100]="select * from Flights";
    showTables(1);
    EnterQuery(display);
}


void MakeUpdate(char table_name[], char Query[], int opt)
{
	int and;
	char condition[200];
	if (opt>0)
	{
		strcat(Query," where ");
	}
	while(opt--)
	{
		printf("Enter the condition\n");
		scanf(" %999[^\n]",condition);
		if (opt!=0)
		{
			printf("Enter 1 for AND and 0 for OR\n");
			scanf("%d",&and);
			if(and==1)
				strcat(condition," and ");
			else
				strcat(condition," or ");
		}
		strcat(Query, condition);
	}
	//printf("Query -************ %s\n", Query);
	if (mysql_query(conn, Query))
    {
    	fprintf(stderr, "%s\n", mysql_error(conn));

    }
}

void Offers(char source[],char destination[],float df)
{
	char Query[500];
	printf("\n|no              ||source          ||Destination     ||original price  ||discount price  |\n");
	sprintf(Query,"select no,source,destination,price,price-((distance/20)*%f) \"discounted price\" from Flights where source like \"%%",df);
	strcat(source,"%%\" and destination like \"%%");
	strcat(Query,source);
	strcat(destination,"%%\"");
	strcat(Query,destination);
	EnterQuery(Query);
}

void Filters(char filters[])
{
	char Query[500]="select no,source,destination,distance,departs,arrives,price from Flights group by ";
	strcat(Query,filters);
	printf("Query-%s\n", Query);
	EnterQuery(Query);
	
}

void Inter(int i, char source[], char dest[])
{
	int k=2;
	char Part1[600]="select f1.source, f1.destination, ";

	while(k<=i)
	{	
		char f[200]="";
		char destination[100]=".destination";
		sprintf(f,"f%d",k);
		strcat(f,destination);
		if(k!=i)
		{
			strcat(f,", ");
			strcat(Part1,f);
		}
		else
		{
			strcat(f," ");
			strcat(Part1,f);
		}
		k++;
	}
	k=1;
	strcat(Part1,"from ");
	while(k<=i)
	{
		char f[200]="";
		sprintf(f,"Flights f%d",k);
		if(k!=i)
		{
			strcat(f,", ");
			strcat(Part1,f);
		}
		else
		{
			strcat(f," ");
			strcat(Part1,f);
		}
		k++;
	}
	strcat(Part1,"where ");
	char cond1[100];
	sprintf(cond1,"f1.source=\"%s\"",source);
	strcat(Part1,cond1);
	char cond2[100];
	sprintf(cond2,"and f%d.destination=\"%s\" and ",i,dest);
	strcat(Part1,cond2);
	k=1;
	while(k<i)
	{
		char f[200]="";
		sprintf(f,"f%d.destination=f%d.source",k,k+1);
		if(k!=i-1)
		{
			strcat(f," and ");
			strcat(Part1,f);
		}
		else
		{
			strcat(f," ");
			strcat(Part1,f);
		}
		k++;
	}
	printf("%s\n", Part1);
	EnterQuery(Part1);
}


void main(int argc, char const *argv[])
{
	printf("****************************************\nCREATE A DATABASE NAMED 'FLIGHTEMBEDDED'\n****************************************\n");
	conn = mysql_init(NULL);
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
   }

    char  attribute[20], r_table_name[20], r_attribute[20];
    char s[20];
	char d[20];
    char table_name[20];
	int option,noofattr;
	int opt;
	char Query[1000];
    while(1)
    {
	   printf("1.Create a table\n2.Add a primary key\n3.Add foreign key\n4.Insert/Delete\n5.Update table\n6.Offers\n7.Flights with Intermediate stops\n8.Apply Filters\n9.Exit");
	   scanf("%d",&opt);
	   
	   switch(opt)
	   {
	   		case 1:
	   			Create_table();
	   			printf("\n\n");
	   			break;
	   		case 2:
	   			DispTables();
	   			printf("Enter the name of the table: ");
	   			scanf(" %s",table_name);
	   			printf("Enter the name of the primary attribute: ");
	   			scanf(" %s",attribute);
	   			//printf("table name - %s\nattribute - %s\n", table_name, attribute);
	   			PK_assign(table_name,attribute);
	   			printf("\n\n");
	   			break;
	   		case 3:
	   			DispTables();
	   			printf("Enter the name of the table and foreign key attribute: ");
	   			scanf(" %s",table_name);
	   			scanf(" %s",attribute);
	   			printf("Enter the name of reference table name and attribute name: ");
	   			scanf(" %s",r_table_name);
	   			scanf(" %s",r_attribute);
	   			FK_assign(table_name,attribute,r_table_name,r_attribute);
	   			printf("\n\n");
	   			break;
	   		case 4:
	   			printf("1)Insert\n2)Delete\n");
	   			scanf("%d",&noofattr);
	   			if (noofattr==1)
	   			{
	   				printf("Enter the table into which values have to be entered\n1.Flights\n2.Aircrafts\n3.Certified\n4.Employees");
		   			scanf("%d",&option); 
		   			Insert(option);
	   			}
	   			else
	   			{
	   				DispTables();
	   				printf("Enter the table from which values have to be deleted:");
	   				scanf(" %s", table_name);
	   				printf("Enter no of conditions:");
	   				scanf("%d",&option); 
		   			Delete(table_name,option);
	   			}
	   			printf("\n\n");
	   			break;
	   		case 5:
	   			DispTables();
	   			printf("Enter the name of the table: ");
	   			scanf(" %s",table_name);
	   			printf("Enter the number of attributes to be updated: ");
	   			scanf("%d",&noofattr);
	   			char Query7[500]="update ";
				
				strcat(table_name," set ");
				strcat(Query7,table_name);
	   			while(noofattr--)
	   			{
	   				printf("Enter the name of the attribute: ");
	   				scanf(" %s",attribute);
	   				printf("Enter new value for %s (with double quotes if required): ", attribute);
	   				scanf(" %s",r_attribute);
	   				strcat(attribute,"=");
					strcat(attribute,r_attribute);
					strcat(Query7,attribute);
					if (noofattr>0)
					{
						strcat(Query7,",");
					}
	   			}
	   			printf("Enter no of conditions : ");
	   			scanf("%d",&option);
	   			MakeUpdate(table_name, Query7, option);
	   			//printf("%s\n",Query7 );
	   			printf("\n\n");
	   			break;
	   		/*case 6:
	   			printf("Enter the Query\nmysql> ");
	   			scanf(" %999[^\n]",Query);
	   			EnterQuery(Query);
	   			printf("\n\n");
	   			break;*/
	   		case 6:
	   			printf("Enter the source:");
	   			scanf(" %s",attribute);
	   			printf("Enter the destination:");
	   			scanf(" %s", r_attribute);
	   			float no=14.5;
	   			Offers(attribute,r_attribute,no);
	   			break;
	   		case 7:
		   		printf("Enter source: ");
		   		scanf(" %19[^\n]",s);
		   		printf("Enter the destination: ");
		   		scanf(" %19[^\n]",d);

		   		printf("Enter the number of Intermediate stops: ");
		   		scanf("%d", &option);
		   		while(option--)
		   		{
	   				Inter(option+2,s,d);
	   			}
	   			break;
	   		case 8:
	   			printf("Enter the number of Filters: ");
	   			scanf("%d",&noofattr);
	   			char filters[100]="";
	   			char fil[100];
	   			while(noofattr--)
	   			{
	   				printf("Enter the filter:");
	   				scanf(" %s",fil);
	   				if (noofattr>0)
	   				{
	   					strcat(fil,",");
	   				}
	   				strcat(filters,fil);
	   			}
	   			Filters(filters);
	   			break;
	   		case 9:
	   			exit(1);
	   			break;
	   		default:
	   			printf("Enter a valid option:\n");
	   			printf("\n\n");
	   }		
	}

   mysql_close(conn);
}