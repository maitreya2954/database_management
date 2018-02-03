#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class normalization
{
	vector<string> candidate_key,Attribute,lefti,righti,powerset;
	list<string> *Relation;
	int Relation_count;
public:
	normalization();
	~normalization();
	void Find2NF();
	void Find3NF();
	void isBCNF();	
	void Display();
	void InputFD();
	void enterCandidate();
	void utility(string);
	void utility2(string,int);
	void refillLRVec(int);
	bool isPartialDep(string,string);
	string closure(string);
	void GenSuperKey();
	void SupUtility(string,int);
	bool isSubset1(string);
};

normalization::normalization()
{
	Relation = new  list<string>[10];
	Relation_count=1;
}

normalization::~normalization()
{

}

void normalization::enterCandidate()
{
	cout<<"Enter the Attributes(a,b,c): ";
	string temp;
	cin>>temp;
	char * dup1 = strdup(temp.c_str());
	char * token = strtok(dup1,",");
	while(token!=NULL)
	{
		Attribute.push_back(string(token));
		token = strtok(NULL,",");
	}
	free(dup1);
	temp.clear();
	InputFD();
	Display();
}


void normalization::Display()
{
	cout<<"Attributes: ";
	for (int i = 0; i < Attribute.size(); ++i)
	{
		cout<<Attribute[i]<<" ";
	}
	cout<<endl<<endl;
	cout<<"candidate_key: ";
	for (int i = 0; i < candidate_key.size(); ++i)
	{
		cout<<candidate_key[i]<<" ";
	}
	cout<<endl<<endl;
	/*cout<<"lefti->righti: ";
	for (int i = 0; i < lefti.size(); ++i)
	{
		cout<<lefti[i]<<"->"<<righti[i]<<" ";
	}*/
	cout<<endl<<endl;
	for (int i = 0; i < 10; ++i)
	{
		
		list<string>::iterator j;
		for (j = Relation[i].begin(); j != Relation[i].end(); ++j)
		{
			cout<<"R"<<i<<" - "<<*j<<endl;
		}
	}

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
		Relation[0].push_back(lefti.back()+"->"+righti.back());
		free(dup);
		cout<<endl<<"Do you want to continue (1/0): ";
		cin>>flag;
	}
	lefti.clear();
	righti.clear();
	
	for (list<string>::iterator i = Relation[0].begin(); i != Relation[0].end(); ++i)
	{
		string temp=*i;
		char * dup = strdup(temp.c_str());
		char * token = strtok(dup, "->");
		lefti.push_back(string(token));
		token = strtok(NULL, "->");
		righti.push_back(string(token));
		free(dup);
	}
}

bool normalization::isPartialDep(string NP,string candidate)
{
	int count=0;
	for (int i = 0; i < NP.size(); ++i)
	{
		size_t found = candidate.find(NP[i]);
		if(found!=string::npos)
			count++;
	}
	if (count==candidate.size() or count==0)
		return false;
	else
		return true;
}

void normalization::utility(string in)
{
	for (int i = 0; i < lefti.size(); ++i)
	{
		int count=0;
		string temp=lefti[i];
		for (int j = 0; j < temp.size(); ++j)
		{
			size_t found = in.find(temp[j]);
			if(found!=string::npos)
				count++;
		}
		if(count==temp.size() and Relation[0].size()>1 and temp.size()!=0)
		{
			string add=lefti[i]+"->"+righti[i];
			Relation[0].remove(add);
			string temp=righti[i];
			Relation[Relation_count].push_back(add);
			lefti[i].clear();
			righti[i].clear();
			utility(temp);
			temp.clear();
		}
	}
}

void normalization::Find2NF()
{
	for (int i = 0; i < candidate_key.size(); ++i)
	{
		for (int j = 0; j < lefti.size(); ++j)
		{
			if (isPartialDep(lefti[j],candidate_key[i]) and Relation[0].size()>1)
			{
				string add=lefti[j]+"->"+righti[j];
				Relation[0].remove(add);
				string temp=righti[j];
				Relation[Relation_count].push_back(add);
				lefti[j].clear();
				righti[j].clear();
				utility(temp);
				Relation_count++;	
			}
			
		}
	}
	cout<<"*******************2NF***************"<<endl;
	Display();
}

void normalization::refillLRVec(int counter)
{
	lefti.clear();
	righti.clear();
	for (list<string>::iterator i = Relation[counter].begin(); i != Relation[counter].end(); ++i)
	{
		string temp=*i;
		char * dup = strdup(temp.c_str());
		char * token = strtok(dup, "->"); 
		lefti.push_back(string(token));
		token = strtok(NULL, "->");
		righti.push_back(string(token));
		temp.clear();
		free(dup);
	}
	//Display();
}

void normalization::utility2(string in,int flag)
{
	for (int i = 0; i < lefti.size(); ++i)
	{
		int count=0;
		string temp=lefti[i];
		if (!temp.size() or Relation[flag].size()==1)
		{
			continue;
		}
		for (int j = 0; j < temp.size(); ++j)
		{
			size_t found = in.find(temp[j]);
			if(found!=string::npos)
				count++;
		}
		if(count==temp.size() and Relation[flag].size()>1 and temp.size()!=0);
		{
			string add=lefti[i]+"->"+righti[i];
			Relation[flag].remove(add);
			string temp=righti[i];
			Relation[Relation_count].push_back(add);
			lefti[i].clear();
			righti[i].clear();
   			Relation_count++;
			utility2(temp,flag);
			temp.clear();
		}
	}
}

void normalization::Find3NF()
{
	for (int counter = 0; counter < 10; ++counter)
	{
		//cout<<"Relation["<<counter<<"] - "<<Relation[counter].size()<<endl;
		if(Relation[counter].size()>1)
		{
			refillLRVec(counter);
			for (int i = 0; i < righti.size(); ++i)
			{
				if(righti[i].size()>0)
					utility2(righti[i],counter);
			}
			
		}
	}
	cout<<"*******************3NF***************"<<endl;
	Display();
	//cout<<"Relation_count: "<<Relation_count<<endl;
}

bool isSubset(string a,string b)
{
	int count=0;
	for (int i = 0; i < a.size(); ++i)
	{
		size_t found = b.find(a[i]);
		if(found!=string::npos)
			count++;
	}
	if (count==a.size())
	{
		return true;
	}
	else
		false;
}

void normalization::isBCNF()
{
	for (int counter = 0; counter < 10; ++counter)
	{
		//cout<<"Relation["<<counter<<"] - "<<Relation[counter].size()<<endl;
		if(Relation[counter].size()>1)
		{
			refillLRVec(counter);
			for (int i = 0; i < candidate_key.size(); ++i)
			{
				for (int j = 0; j < lefti.size(); ++j)
				{
					if(lefti[i].size()==0)
						continue;
					if(!isSubset(lefti[j],candidate_key[i]))
					{
						string add=lefti[i]+"->"+righti[i];
						Relation[counter].remove(add);
						string temp=righti[i];
						Relation[Relation_count].push_back(add);
						lefti[i].clear();
						righti[i].clear();
						temp.clear();
					}
				}
			}
			
		}
	}
	cout<<"*******************BCNF***************"<<endl;
	Display();
}

string normalization::closure(string in)
{
	if(in.size()==Attribute.size())
		return in;
	else
	{
		for (int i = 0; i < lefti.size(); ++i)
		{
			if (lefti[i].size()>0 and isSubset(lefti[i],in))
			{
				string temp=righti[i];
				lefti[i].clear();
				righti[i].clear();
				in+=temp;
				in+=closure(in);
			}
		}
		sort(in.begin(),in.end());
		for (int i = 0; i < in.size()-1; ++i)
		{
			while(in[i]==in[i+1])
			{
				in.erase(in.begin()+i+1);
			}

		}

		return in;
	}
}


void normalization::SupUtility(string in, int count)
{
	if (in.size()>=Attribute.size())
	{
	}
	else
	{
		for (int i = count; i < Attribute.size(); ++i)
		{
			string temp=in+Attribute[i];
			sort(temp.begin(),temp.end());
			for (int j = 0; j < temp.size()-1; ++j)
			{
				while(temp[j]==temp[j+1])
				{
					temp.erase(in.begin()+j+1);
				}

			}
			powerset.push_back(temp);
			//cout<<temp<<" ";
			SupUtility(temp,i+1);
		}
	}
}


bool strcompare(string i, string j)
{
	return (i.size()<j.size());
}


bool normalization::isSubset1(string a)
{
	for (int i = 0; i < candidate_key.size(); ++i)
	{
		if(isSubset(candidate_key[i],a))
			return false;
	}
	return true;
}

void normalization::GenSuperKey()
{
	string a;
	cout<<endl<<"Power Set: ";
	SupUtility(a,0);
	
	sort(powerset.begin(),powerset.end(),strcompare);
	for (int i = 0; i < powerset.size(); ++i)
	{
		refillLRVec(0);
		string temp=closure(powerset[i]);
		cout<<"{"<<powerset[i]<<"}+   ---->   "<<temp<<endl;
		if(temp.size()==Attribute.size())
		{
			if (candidate_key.size()==0)
			{
				candidate_key.push_back(powerset[i]);
			}
			else
			{
				if(isSubset1(powerset[i]))
				{
					candidate_key.push_back(powerset[i]);
				}
			}
		}
	}
	//cout<<endl<<"candidate_union: "<<candidate_union<<endl;
	Display();
}


int main(int argc, char const *argv[])
{
	normalization N;
	N.enterCandidate();
	N.GenSuperKey();
	N.Find2NF();
	N.Find3NF();
	N.isBCNF();
	return 0;
}