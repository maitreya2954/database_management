#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <list>


using namespace std;


class normalization
{
private: 
	string candidate;
	vector<string> candset;
	vector<string> FlatVector;
	vector<string> FDset;
	vector<string> lefti;
	vector<string> righti;
	list<string> *Relation;
	int count;
public:
	normalization(string a, string b);
	~normalization();
	void TakeCandset(string);
	void CreateFlatRel(string);
	void secondNF();	
	void thirdNF();
	void InputFD();
	void Display();
	void FindKeySet();
};

normalization::normalization(string a, string b)
{
	
	//TakeCandset(a);
	//candidate.assign(a);
	//CreateFlatRel(b);
	Relation = new list<string>[10];
	count=0;
}

void normalization::TakeCandset(string candsetin)
{
	char * dup1 = strdup(candsetin.c_str());
	char * token = strtok(dup1,",");
	while(token!=NULL)
	{
		candset.push_back(string(token));
		token = strtok(NULL,",");
	}
}

void normalization::CreateFlatRel(string Flatfile)
{
	char * dup1 = strdup(Flatfile.c_str());
	char * token = strtok(dup1,",");
	while(token!=NULL)
	{
		FlatVector.push_back(string(token));
		token = strtok(NULL,",");
	}
}

void normalization::secondNF()
{

}
void normalization::thirdNF()
{

}

void normalization::Display()
{
	for (int i = 0; i < 10; ++i)
	{
		list<string>::iterator j;
		for (j = Relation[i].begin(); j != Relation[i].end(); ++j)
		{
			cout<<"R"<<i<<" - "<<*j<<endl;
		}
	}

}

void normalization::FindKeySet()
{
	for (int i = 0; i < lefti.size(); ++i)
	{
		int count=0;
		for (int j = 0; j < righti.size(); ++j)
		{
			if(!lefti[i].compare(righti[i]))
			{
				count++;
			}
		}
		if (count>0)
		{
			if (!find(candset.begin(), candset.end(), left[i]) != candset.end() )
   				candset.push_back(lefti);
		}
	}
	for (int i = 0; i < candset.size(); ++i)
	{
		candset=candset+","
	}
	cout<<"Candidate: "<<candidate<<endl;
}

void normalization::InputFD()
{
	cout<<"Enter given functional dependencies in form A->B;AB->C;B,C->A";
	string FDstring;
	cin>>FDstring;
	char * dup1 = strdup(FDstring.c_str());
	char * token = strtok(dup1,";");
	while(token!=NULL)
	{
		FDset.push_back(string(token));
		token = strtok(NULL,";");
	}
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


normalization::~normalization()
{

}

int main(int argc, char const *argv[])
{
	string candsetin;
	cout<<"Enter the candidate set as 'A,B': ";
	cin>>candsetin;
	string Flatfile;
	cout<<"Enter all the attributes: ";
	cin>>Flatfile;
	normalization N(candsetin,Flatfile);
	N.InputFD();
	N.FindKeySet();
	//N.secondNF();
	return 0;
}