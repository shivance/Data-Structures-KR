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
		l = 'o';
		fc=nc=NULL;
	}
};

//ABC..D.E..FG.H..JK.L.MP.Q..N....
void inputGT(GTnode* &T)
{
	GTnode* tmp;char a;
	cin>>a;

	if (a=='.') return;
	tmp = new GTnode();
	tmp->l = a;
	T->fc = tmp;
	inputGT(tmp);

	cin>>a;

	if (a=='.') return;
	tmp = new GTnode();
	tmp->l = a;
	T->nc = tmp;
	inputGT(tmp);
}

void level(GTnode* T,queue<GTnode*>&q)
{
	GTnode* tmp,*tmpn;
	
	q.push(T);
	while(!q.empty())
	{
		tmp = q.front();
		q.pop();
		cout<<tmp->l<<" ";
		tmpn = tmp->fc;
		if(tmpn!=NULL)
		{
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
	GTnode* T = new GTnode();
	char a;
	cin>>a;
	T->l = a;
	inputGT(T->fc);
	cout<<T->fc->fc->l;

	//queue<GTnode*> q;
	//level(T,q);

	return 0;	
}

//ABC..D.E..FG.H..JK.L.MP.Q..N....