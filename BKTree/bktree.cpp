#include <iostream>
#include <queue>
#include <vector>
#include <list>

using namespace std;

class bknode
{
    public:
    string str;
    int d;
    vector<bknode*> child;
    bknode(string s)
    {
        d = 0;
        str = s;
    }
};

int editDP(string s1,string s2)
{
    int m = s1.length(),n = s2.length();
    int D[m+1][n+1];

    for (int i=0;i<=m;++i)
        D[i][0] = i;

    for (int j=0;j<=n;++j)
        D[0][j] = j;

    for (int i=1;i<=m;++i)
    {
        for (int j=1;j<=n;++j)
        {
            if (s1[i-1]==s2[j-1])
                D[i][j] = D[i-1][j-1];

            else
                D[i][j] = 1 + min(D[i][j-1],min(D[i-1][j],D[i-1][j-1]));
        }
    }

    return D[m][n];
}

void insert(bknode* &T,string s)
{
    if (T==NULL)
    {
        T = new bknode(s);
        return;
    }

    int d = editDP(s,T->str);
    bool o = false;

    for (int i=0;i<T->child.size();++i)
    {
        if (editDP(T->str,T->child[i]->str)==d){
            o = true;
            insert(T->child[i],s);
        }
    }

    if (!o){
        T->child.push_back(new bknode(s));
        T->child[T->child.size()-1]->d = d;
        return;
    }
}

void bfs(bknode* T)
{
	bknode* tmp;
	queue<bknode*> q;
	
	q.push(T);
	while(!q.empty())
	{
		tmp = q.front();
		cout<<tmp->str<<" "<<tmp->d<<" ";
        q.pop();

        vector<bknode*>::iterator it;

        for (it = tmp->child.begin();it!=tmp->child.end();++it)
            q.push(*it);
	}
}

void recommend(bknode*T,string s,vector<string>&cl,int n)
{
    bknode* tmp;
    queue<bknode*> q;
    q.push(T);
    cl.push_back(T->str);

    int l ,r,d,td;

	while(!q.empty())
	{
		tmp = q.front();
        d = editDP(tmp->str,s);
        l = d-n;r= d+n;
        q.pop();
        vector<bknode*>::iterator it;

        for (it = tmp->child.begin();it!=tmp->child.end();++it){
            td = editDP((*it)->str,s);
            if (td>=l && td<=r){
                q.push(*it);
                cl.push_back((*it)->str);
            }
        }
	}
}

void printvec(vector<string> vec,string s,int n){
    for (int i=0;i<vec.size();++i){
        if (editDP(vec[i],s)<=n)
            cout<<vec[i]<<" "<<editDP(vec[i],s);
    }
    cout<<"\n";
}

int main()
{
    string s;
    bknode* T = NULL;

    while(true)
    {
        cin>>s;
        if (s=="#") break;
        insert(T,s);
    }
    bfs(T);
    cout<<"\n";

    int n;
    vector<string> cl; //candidate list
    while(true)
    {
        cl.clear();
        cin>>s;
        if (s=="#") break;
        cin>>n;
        
        recommend(T,s,cl,n);
        printvec(cl,s,n);
    }  
    
    return 0;
}
