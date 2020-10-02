#include <iostream>
#include <map>

using namespace std;

class node
{
public:
	int data;
	bool eol;
	node* next;

	node()
	{
		eol=false; 
		next = NULL;
	}
};

void printlist(node* tmp)
{
	node *tmpn = tmp->next;
	cout<<tmp->data<<" ";
	while (tmpn != tmp)
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

	if (tmpn==tmp)
	{
		cout<<tmpn->data<<"\n";
	}
}

int main()
{
	node* head = new node();
	int a;

	map<int,int> m;

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
		tmp = new node();
		tmp->data = a;
		prev->next = tmp;
		prev = tmp;
	}

	tmp = head;

	while(true)
	{
		if (tmp->eol==true)
		{
			break;
		}

		cout<<tmp->data<<"\n";

		if (m[tmp->data]>1) 
		{
			node* tmpq = tmp;
			printlist(tmpq);
			tmp = tmp->next;
		}
	}

	return 0;
}