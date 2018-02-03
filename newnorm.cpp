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
	vector<string> candset,closur;
	vector<string> FlatVector;
	vector<string> FDset;
	vector<string> lefti;
	vector<string> righti;
	list<string> *Relation;
public:
	normalization();
	void FindKeySet(int count);
	void InputFD();
	void secondNF(int count);
	void thirdNF(int count);
	void Display();
	void closure();
	~normalization();
};

normalization::normalization()
{
	Relation = new list<string>[20];
}

void normalization::FindKeySet(int count)
{
	lefti.clear();
	righti.clear();
	candset.clear();
	list<string>::iterator it;
	for (it = Relation[count].begin(); it != Relation[count].end() ; ++it)
	{
		string temp=*it;
		char * dup = strdup(temp.c_str());
		char * token1 = strtok(dup, "->");
		lefti.push_back(string(token1));
		token1 = strtok(NULL, "->");
		righti.push_back(string(token1));
		free(dup);
	}

	for (int i = 0; i < lefti.size(); ++i)
	{
		char * dup1 = strdup(lefti[i].c_str());
		char * token = strtok(dup1,",");
		while(token!=NULL)
		{
			FlatVector.push_back(string(token));			
			token=strtok(NULL,",");
		}
		/*cout<<"FlatVector - ";
		/*for (int i = 0; i < FlatVector.size(); ++i)
		{
			cout<<FlatVector[i]<<" ";
		}
		cout<<endl;*/
		for (int m = 0; m < FlatVector.size(); ++m)
		{
			int count1=0;
			for (int n = 0; n < righti.size(); ++n)
			{
				if (FlatVector[m].compare(righti[n])==0)
				{
					count1++;
				}
			}
			//cout<<FlatVector[m]<<" count - "<<count1<<endl;
			
			if (count1==0)
			{
				int k;
					for (k = 0; k < candset.size(); ++k)
					{
						if(!candset[k].compare(FlatVector[m]))
							break;
					}
					if (k==candset.size())
					{
						candset.push_back(FlatVector[m]);
					}
					
			}
			
		}
		FlatVector.clear();
	}
	/*
	candidate+=candset[0];
	for (int l = 1; l < candset.size(); ++l)
	{
		candidate=candidate+","+candset[l];
	}
	//cout<<"count - "<<count<<endl;	
	cout<<"Candidate: "<<candidate<<endl;*/
	/*for (int i = 0; i < lefti.size(); ++i)
	{
		//cout<<"left - "<<lefti[i]<<"  right - "<<righti[i]<<endl;
	}*/
	FlatVector.clear();
}


void normalization::InputFD()
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
			Relation[0].push_back(finalFD);
		}
		cout<<endl<<"Do you want to continue (1/0): ";
		cin>>flag;
	}
	lefti.clear();
	righti.clear();
	
	for (int i = 0; i < FDset.size(); ++i)
	{
		char * dup = strdup(FDset[i].c_str());
		char * token = strtok(dup, "->");
		lefti.push_back(string(token));
		token = strtok(NULL, "->");
		righti.push_back(string(token));
		free(dup);
	}

	list<string>::iterator i;
	for (i = Relation[0].begin(); i != Relation[0].end(); ++i)
	{
		cout<<"("<<*i<<") ";
	}
	cout<<endl;
	lefti.clear();
	righti.clear();
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

void normalization::secondNF(int count)
{
	int count1=0,count2=0,flag=0;
	
		FindKeySet(count);
		for (int i = 0; i < lefti.size(); ++i)
			{
				
				count2=0,count1=0;
				char * dup = strdup(lefti[i].c_str());
				char * token = strtok(dup,",");
				while(token!=NULL)
				{
					FlatVector.push_back(string(token));			
					token=strtok(NULL,",");
				}
				for (int m = 0; m < FlatVector.size(); ++m)
				{
					for (int j = 0; j < candset.size(); ++j)
					{

						if (FlatVector[m].compare(candset[j])==0)
						{
							count1++;
							break;
						}
					}
				}
				//cout<<"count1 - "<<count1<<endl;
				if (count1!=candset.size() and Relation[count].size()>1)
				{
					string add=lefti[i]+"->"+righti[i];
					Relation[count].remove(add);
					Relation[count+1].push_back(add);
					lefti.clear();
					righti.clear();
					candset.clear();
					candidate.clear();
					secondNF(count);
				}
				FlatVector.clear();
			}
			
			lefti.clear();
			righti.clear();
			candset.clear();
			candidate.clear();
			FlatVector.clear();
			count++;
	if(Relation[count].size())
	{
		secondNF(count);
	}
}


void normalization::thirdNF(int count)
{
	//FindKeySet(count);
	for (int i = 0; i < lefti.size(); ++i)
	{
		int count1=0;
		char * dup = strdup(lefti[i].c_str());
		char * token = strtok(dup,",");
		while(token!=NULL)
		{
			FlatVector.push_back(string(token));			
			token=strtok(NULL,",");
		}
		for (int j = 0; j < candset.size(); ++j)
		{
			for (int m = 0; m < FlatVector.size(); ++m)
			{
				if (FlatVector[m].compare(candset[j])==0)
				{
					count1++;
				}
			}
		}
		if (!count1 and Relation[count].size()>1)
		{
			string add=lefti[i]+"->"+righti[i];
			Relation[count].remove(add);
			Relation[count+1].push_back(add);
		}
		FlatVector.clear();
	}
	lefti.clear();
	righti.clear();
	candset.clear();
	candidate.clear();
	FlatVector.clear();
	count++;
	if (Relation[count].size())
	{
		thirdNF(count);
	}
}

normalization::~normalization()
{

}

int main(int argc, char const *argv[])
{

	normalization N;
	N.InputFD();
	
	N.Display();
	//N.FindKeySet(0);
	//candInput();
	N.secondNF(0);
	N.thirdNF(0);
	cout<<endl<<endl;
	N.Display();
	return 0;
}
/*
	patientno->patientname,surgeryno
1
staffno,appdate,apptime->patientno,patientname
1
staffno->dentistname
1
0
*/