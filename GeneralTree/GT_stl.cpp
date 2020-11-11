// Iterative Depth Limited Search

#include <iostream>
#include <queue>
#include <list>
using namespace std;

class GTnode
{
public:
    list<GTnode*> ls;
	char l;
	GTnode()
	{
		l = '0';
	}
};

void printList(list<GTnode*>ls)
{
    while(!ls.empty())
    {
        cout<<ls.front()->l<<" ";
        ls.pop_front();
    }
    cout<<"\n";
}


void inputGT(GTnode* &T)
{
	GTnode* tmpc,*tmpnxt;char a;
	cin>>a;

	if (a=='.') return;

	tmpc = new GTnode();
	tmpc->l = a;
	T->ls.push_back(tmpc);
	inputGT(tmpc);

	while(true)
	{
		cin>>a;
		if (a=='.') return;

		tmpnxt = new GTnode();
		tmpnxt->l = a;
        T->ls.push_back(tmpnxt);
		inputGT(tmpnxt);
	}
}

void level(GTnode* T)
{
	GTnode* tmp,*tmpn;
	queue<GTnode*> q;
	
	q.push(T);
	while(!q.empty())
	{
		tmp = q.front();
		cout<<tmp->l<<" ";
        q.pop();

        list<GTnode*>::iterator it;

        for (it = tmp->ls.begin();it!=tmp->ls.end();++it)
            q.push(*it);
	}
}

int main()
{
	char a;
	GTnode* T = new GTnode();
	cin>>a;
	T->l = a;
	inputGT(T);	
	level(T);

	return 0;	
}

