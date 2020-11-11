// Iterative Depth Limited Search

#include <iostream>
#include <queue>
using namespace std;

class GTnode
{
public:
	GTnode *fc,*nc;
	char l;
	GTnode()
	{
		l = '0';
		fc=nc=NULL;
	}
};

void printQ(queue<GTnode*>q)
{
	cout<<"\nqueue is : ";
	while (!q.empty())
	{
		cout<<q.front()->l<<" ";
		q.pop();
	}
	cout<<"\n";
}

//ABC..D.E..FG.H..JK.L.MP.Q..N....
void inputGT(GTnode* T)
{
	GTnode* tmpc,*tmpnxt;char a;
	cin>>a;

	if (a=='.') return;

	tmpc = new GTnode();
	tmpc->l = a;
	T->fc = tmpc;
	inputGT(tmpc);

	while(true)
	{
		cin>>a;
		if (a=='.') return;

		tmpnxt = new GTnode();
		tmpnxt->l = a;
		tmpc->nc = tmpnxt;
		tmpc = tmpnxt;
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
		tmpn = tmp->fc;
		q.pop();

		if(tmpn!=NULL)
		{
			q.push(tmpn);
			while(tmpn->nc!=NULL)
			{
				q.push(tmpn->nc);
				tmpn = tmpn->nc;
			}
		}
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


//ABC.D.E..FG.H..JK.L.MP.Q..N...