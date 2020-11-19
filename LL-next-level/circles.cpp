// problem name - circles circle


#include <iostream>
#include <map>

using namespace std;

class node
{
public:
	int key;
	bool eol,sig;
	node* next;
	bool visited;
	node()
	{
		eol=false; 
		visited = false;
		next = NULL;
		sig = false;
	}
};

void printlist(node* tmp)
{
	tmp->sig = true;
	node *tmpn = tmp->next;
	cout<<tmp->key<<" ";

	while (tmpn->sig==false)
	{
		if (tmp->key == tmpn->key)
		{
			cout<<tmpn->key;	
			cout<<endl;
			cout<<tmpn->key<<" ";
			tmpn = tmpn->next;
		}

		else
		{
			cout<<tmpn->key<<" ";
			tmpn = tmpn->next;
		}
	}

	tmp->sig = false;
	cout<<tmp->key<<"\n";	
}

int main()
{
	node* head = new node();
	int a;

	map<int,int> m;
	map<int,bool> vt;

	cin>>a;
	head->key = a;
	node* tmp,*prev = head;

	while(true)
	{
		cin>>a;
		if (a==-1) 
		{
			tmp->next = head;
			tmp->eol = true;
			break;
		}

		m[a]++;
		vt[a] = false;
		tmp = new node();
		tmp->key = a;
		prev->next = tmp;
		prev = tmp;
	}

	tmp = head;
	map<int,int>::iterator it;

	node* tmpn = tmp;

	while(!tmp->visited)
	{
		tmp->visited = true;
		
		if (vt[tmp->key]==true)
		{
			tmp=tmp->next;
			continue;
		}
		vt[tmp->key] = true;

		if (m[tmp->key]>1) 
		{
			node* tmpq = tmp;
			printlist(tmpq);
		}

		if (tmp->eol==true)
		{
			break;
		}

		tmp = tmp->next;		
	}

	return 0;
}