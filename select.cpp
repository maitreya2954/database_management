#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;


int index_no(char const argv[])
{
	int index=-1;
	if(strcmp(argv,"fname")==0)
		index=0;
	else if(strcmp(argv,"mname")==0)
		index=1;
	else if(strcmp(argv,"lname")==0)
		index=2;
	else if(strcmp(argv,"ssn")==0)
		index=4;
	else if(strcmp(argv,"dob")==0)
		index=5;
	else if(strcmp(argv,"address")==0)
		index=6;
	else if(strcmp(argv,"salary")==0)
		index=7;
	else if(strcmp(argv,"superssn")==0)
		index=8;
	else if(strcmp(argv,"dno")==0)
		index=9;
	else if(strcmp(argv,"mobileno")==0)
		index=10;
	return(index);
}


class Employee
{
public:
	Employee();
	~Employee();
	int getall(int,char **);
};

Employee::Employee()
{

}
Employee::~Employee()
{

}
int Employee::getall(int argc,char *argv[])
{
	
		string data;
		ifstream infile;
		if(argc<5)
		{

			infile.open(strcat(argv[3],".txt"),ios::in);
			if(!infile)
				return 1;
			while(!infile.eof())
			{
				getline(infile,data);
				cout <<data<<endl;
			}
			
			infile.close();	
		}
		else
		{
				
				vector<string> v,line;
				char * dup = strdup(argv[5]);
			    char * token = strtok(dup, "=");
			    while(token != NULL){
			        v.push_back(string(token));
			        token = strtok(NULL, "=");
			    }
			    free(dup);
				infile.open(strcat(argv[3],".txt"),ios::in);
				if(!infile)
					return 1;
				while(!infile.eof())
				{
					getline(infile,data);
					char * dup = strdup(data.c_str());
				    char * token = strtok(dup, " ");
				    while(token != NULL){
				        line.push_back(string(token));
				        token = strtok(NULL, " ");
				    }
				    free(dup);
				    if(v[1].compare(line[index_no(v[0].c_str())])==0)	
						cout <<data<<endl;
					line.clear();
				}
				
				infile.close();    			

			
		}
		return 0;
}


int main(int argc, char *argv[])
{
			Employee E1;
			E1.getall(argc,argv);
}