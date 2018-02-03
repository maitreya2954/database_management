#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>


void main() {
   int flag=1;
   int opt=3;
char flno[10],price[10],distance[10],source[20],destination[20],departs[20],arrives[20]; 
char aid[10],aname[20], cruisingrange[10];
char eid[10];
char ename[30], salary[10];
   while(flag)
   {
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
               printf("%s\n", Query1);
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
             printf("%s\n", Query2);
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
             printf("%s\n", Query4);
            break;
         default:
            flag=0;
            break;
      }
      printf("Enter next set of values (or) to exit enter 5\n");
      int x;
      scanf("%d",&x);
      if (x==5)
      {
         flag=0;
      }
   }
}