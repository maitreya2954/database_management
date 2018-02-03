#include <iostream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;
vector<string> FDset;
vector<string> lefti;
vector<string> righti;
vector<string> closure;

void closur(string left)
{
	char * dup1 = strdup(righti.back().c_str());
	char * token = strtok(dup1,",");
	while(token!=NULL)
	{
		closure.push_back(string(token));
		token = strtok(NULL,",");
	}
	int count=1;
	while(count)
	{
		count=0;
		for (int i = 0; i < closure.size(); ++i)
		{
			for (int j = 0; j < left.size(); ++j)
			{
				lefti[i].compare(closure[j]);
			}
		}
		
	}
}

void InputFD()
{

	
	int flag=1;
	while(flag)
	{
		string FD,finalFD,cont;
		cout<<"Enter the FD  (A,X->B,Y): ";
		cin>>FD;
		char * dup = strdup(FD.c_str());
		char * token = strtok(dup, "->");
		lefti.push_back(string(token));
		token = strtok(NULL, "->");
		righti.push_back(string(token));
		free(dup);
		char * dup1 = strdup(righti.back().c_str());
		token = strtok(dup1,",");
		while(token!=NULL)
		{
			finalFD=lefti.back()+"->"+token;
			token = strtok(NULL,",");
			FDset.push_back(finalFD);
		}
		cout<<endl<<"Do you want to continue (1/0): ";
		cin>>flag;
	}
	lefti.clear();
	righti.clear();
	for (int i = 0; i < FDset.size(); ++i)
	{
		cout<<i+1<<" - "<<FDset[i]<<"\n";
	}
	
	for (int i = 0; i < FDset.size(); ++i)
	{
		char * dup = strdup(FDset[i].c_str());
		char * token = strtok(dup, "->");
		lefti.push_back(string(token));
		token = strtok(NULL, "->");
		righti.push_back(string(token));
		free(dup);
	}

}

int main(int argc, char const *argv[])
{
	InputFD();
	return 0;
}