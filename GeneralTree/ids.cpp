#include <iostream>
#include <queue>
#include <list>
using namespace std;

#define MAX_DEPTH 25

class GTnode
{
public:
    list<GTnode*> ls;
	char l;
    int d;
	GTnode()
	{
        d = 0;
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


void inputGT(GTnode* &T,int d)
{
	GTnode* tmpc,*tmpnxt;char a;
	cin>>a;
    ++d;
	if (a=='.') return;

	tmpc = new GTnode();
	tmpc->l = a;
    tmpc->d = d;
	T->ls.push_back(tmpc);
	inputGT(tmpc,d);

	while(true)
	{
		cin>>a;
		if (a=='.') return;

		tmpnxt = new GTnode();
        tmpnxt->d = d;
		tmpnxt->l = a;
        T->ls.push_back(tmpnxt);
		inputGT(tmpnxt,d);
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

bool DFS(GTnode*&T,char k,int depth)
{
    if (T->d > depth) return false;
    if (T->l==k) return true;


    list<GTnode*>::iterator it;

    for (it = T->ls.begin();it != T->ls.end();++it)
        if (DFS((*it),k,depth)) return true;

    return false;
}

bool IDLS(GTnode*&T,char k)
{
    for (int d = 0;d<MAX_DEPTH;++d)
    {
        cout<<"Running IDLS for d = "<<d<<"\n";
        if(DFS(T,k,d))
            return true;
    }
    return false;
}

int main()
{
	char a;
	GTnode* T = new GTnode();
	cin>>a;
	T->l = a;
	inputGT(T,0);	
    cout<<"Enter char to be searched : ";cin>>a;
	if(IDLS(T,a)) cout<<"\nFound \n";
    else cout<<"\nNot Found\n";

	return 0;	
}

//ABFI.J..GK..H..C.DLM.N..P.Q..E..
//ABC.D.E..FG.H..JK.L.MP.Q..N...