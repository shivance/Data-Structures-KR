#include <iostream>
#include <vector>
using namespace std;

class tnode
{
public:
	int child,data;
	tnode** arr;
	tnode (int s) 
	{
		child = s;
		arr = new tnode* [s];
	}
};


void printstk(vector <tnode*> stk)
{
	for (int i=0;i<stk.size();++i)
	{
		cout<<stk[i]->data<<" ";
	}
	cout<<endl;
}

void inputLL(tnode* tmp)
{
	int a,dir;
	
	if (tmp->child==0)
	{
		return;
	}

	for (int i=0;i<tmp->child;++i)
	{
		cin>>a>>dir;
		tmp->arr[i] = new tnode(dir);
		tmp->arr[i]->data = a;
		inputLL(tmp->arr[i]);
	}
}

void prinTgt(tnode* tmp,vector<tnode*>stk)
{
	stk.push_back(tmp);
	if (tmp->child==0)
	{
		printstk(stk);
		cout<<endl;
		return;
	}

	for (int i=0;i< (tmp->child); ++i)
	{
		prinTgt(tmp->arr[i],stk);
	}
}

int main()
{
	int a,dir;
	cin>>a>>dir;
	tnode* head = new tnode(dir);
	head->data = a;
	vector<tnode*> stk;
	inputLL(head);
	prinTgt(head,stk);

	return 0;
}	