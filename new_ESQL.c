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
   char *database = "flights"; // Here you need to enter the database name if you have already other wise leave it free.
   char brackets[]=")";
void Q1(char salary[])
{
	char y[]="select aname from aircraft where aircraft.aid in (select c.aid from certified c,employees e where c.eid=e.eid and salary>";

	conn = mysql_init(NULL);

   /* Connect to database */
   if (!mysql_real_connect(conn, server,
         user, password, database, 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      exit(1);
    }
    strcat(strcat(y,salary),brackets);
    printf("%s\n",y );
      if (mysql_query(conn,y));
         {
            fprintf(stderr, "%s\n", mysql_error(conn));
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
           if (i==0)
           {
            printf("Empty Set\n");
           }

   mysql_free_result(res);
   mysql_close(conn);

}

void main() {
   
   char x[100];
   printf("Enter the salary : \n");
   scanf ("%[^\n]%*c", x);
   Q1(x);

   printf("Enter the salary : \n");
   scanf ("%[^\n]%*c", x);
   Q1(x);
   

}