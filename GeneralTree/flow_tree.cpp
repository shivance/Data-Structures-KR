// Iterative Depth Limited Search

#include <iostream>
#include <queue>
#include <list>
#include <vector>
using namespace std;

class GTnode
{
public:
    list<GTnode*> ls;
	char l;
    int mass;
    bool flg;
    int time;
	GTnode()
	{
		l = '0';
        mass = 0;
        flg = false;
        time = 0;
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

void printvec(vector<GTnode*>vec)
{
    cout<<"vector : ";
    for (int i=0;i<vec.size();++i)
        cout<<vec[i]->l<<" ";
    cout<<endl;
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
	GTnode* tmp;
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

void printMass(GTnode* &T)
{
    GTnode* tmp,*tmpn;
	queue<GTnode*> q;
	
	q.push(T);
	while(!q.empty())
	{
		tmp = q.front();
		cout<<tmp->mass<<" ";
        q.pop();

        list<GTnode*>::iterator it;

        for (it = tmp->ls.begin();it!=tmp->ls.end();++it)
            q.push(*it);
	}
}

void printTime(GTnode* &T)
{
    GTnode* tmp,*tmpn;
	queue<GTnode*> q;
	
	q.push(T);
	while(!q.empty())
	{
		tmp = q.front();
		cout<<tmp->l<<" was updated at t = "<<tmp->time<<"\n";
        q.pop();

        list<GTnode*>::iterator it;

        for (it = tmp->ls.begin();it!=tmp->ls.end();++it)
            q.push(*it);
	}
}



void updateMass(GTnode* &T)
{
    if (T->ls.size()==0) return;

    list<GTnode*>::iterator it;
    for (it=T->ls.begin();it!=T->ls.end();++it)
        updateMass(*it);

    T->mass=(T->ls.size());

    for (it=T->ls.begin();it!=T->ls.end();++it)
        T->mass+= (*it)->mass;
    
}

bool sortfunc(GTnode*& a,GTnode*&b)
{
    return (a->mass > b->mass);
}

void sortTree(GTnode* &T)
{
    GTnode* tmp;
	queue<GTnode*> q;
	
	q.push(T);
	while(!q.empty())
	{
		tmp = q.front();
        tmp->ls.sort(sortfunc);
        q.pop();

        list<GTnode*>::iterator it;

        for (it = tmp->ls.begin();it!=tmp->ls.end();++it)
            q.push(*it);
	}
}

int propagate(GTnode* &T)
{
    int t=0;
    vector<GTnode*> v,tmpvec;
    T->flg = true;
    T->time = t;
    v.push_back(T);
    ++t;

    GTnode* tmp,*tmpn;
    list<GTnode*>::iterator it;
    vector<GTnode*>::iterator vit;

    while(true)
    {
        if (v.size()>=(T->mass+1)) break;

        printvec(v);
        tmpvec = v;
        for (vit=v.begin();vit!=v.end();++vit)
        {
            tmp =*vit;
            if (tmp->ls.size()!=0)
            {
                it = tmp->ls.begin();
                while (it!=tmp->ls.end() && ((*it)->flg)) 
                    ++it;

                if (*it != NULL && it != tmp->ls.end())
                {
                    (*it)->flg = true;
                    (*it)->time = t;
                    tmpvec.push_back(*it);
                }

                else continue;
            }
        }
        v = tmpvec;
        ++t;
    }
    printvec(v);
    --t;

    return t;
}

int main()
{
	char a;
	GTnode* T = new GTnode();
	cin>>a;
	T->l = a;
	inputGT(T);	
    updateMass(T);
    sortTree(T);
    int t = propagate(T);
    cout<<"Maximum time : "<<t<<"\n";
    printTime(T);
    
	return 0;	
}

//ABFI.J..GK..H..C.DLM.N..P.Q..E..