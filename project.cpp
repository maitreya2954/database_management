#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>


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




int main(int argc, char *argv[])
{
	ifstream infile;
	string data;
	vector<string> line,attribute;
	if (strcmp(argv[2],"all")==0)
	{
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
			for (int i = 0; i < line.size(); ++i)
			{
				cout<< " "<< line[i];
			}
			cout<<endl;
			line.clear();
		}
					
		infile.close();    
	}
	else
	{
		char * dup = strdup(argv[2]);
		char * token = strtok(dup, ",");
		    while(token != NULL){
			    attribute.push_back(string(token));
			    token = strtok(NULL, ",");
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
			for (int i = 0; i < attribute.size(); ++i)
			{
				cout<< setw(20)<< line[index_no(attribute[i].c_str())] << setw(20);
			}
			cout<<endl;
			line.clear();
		}
					
		infile.close();    			
	}
	return 0;
}