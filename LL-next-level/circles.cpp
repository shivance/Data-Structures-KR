#include <iostream>
#include <map>

using namespace std;

class node
{
public:
	int data;
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
	cout<<tmp->data<<" ";

	while (tmpn->sig==false)
	{
		if (tmp->data == tmpn->data)
		{
			cout<<tmpn->data;	
			cout<<endl;
			cout<<tmpn->data<<" ";
			tmpn = tmpn->next;
		}

		else
		{
			cout<<tmpn->data<<" ";
			tmpn = tmpn->next;
		}
	}

	tmp->sig = false;
	cout<<tmp->data<<"\n";	
}

int main()
{
	node* head = new node();
	int a;

	map<int,int> m;
	map<int,bool> vt;

	cin>>a;
	head->data = a;
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
		tmp->data = a;
		prev->next = tmp;
		prev = tmp;
	}

	tmp = head;
	map<int,int>::iterator it;

	node* tmpn = tmp;

	while(!tmp->visited)
	{
		tmp->visited = true;
		
		if (vt[tmp->data]==true)
		{
			tmp=tmp->next;
			continue;
		}
		vt[tmp->data] = true;

		if (m[tmp->data]>1) 
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