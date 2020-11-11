#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

class mstnode
{
public:
    int m;
    int* key;
    int cnt;
    mstnode**way;

    mstnode(int m)
    {
        this->m = m;
        key = new int[m-1];
        cnt = 0;
        way = new mstnode*[m];
        for (int i=0;i<m;++i) way[i]=NULL;
        for (int i=0;i<m-1;++i) key[i]=INT_MIN;
    }
};

void inorder(mstnode*&MT)
{
    if (MT==NULL || MT->cnt==0)
        return;
    
    int i;
    for (i=0;i<MT->cnt;++i)
    {
        inorder(MT->way[i]);
        cout<<MT->key[i]<<" ";
    }
    inorder(MT->way[i]);
}

void printarr(int arr[],int m)
{
    for (int i=0;i<m;++i)
    {
        cout<<arr[i]<<" ";
    }
}

void level(mstnode*&MT)
{
    mstnode* tmp;
    queue<mstnode*> q;

    q.push(MT);
    while(!q.empty())
    {
        tmp = q.front();
        printarr(tmp->key,tmp->cnt);
        q.pop();

        int i;
        for (i=0;i<=tmp->m;++i)
        {
            if (tmp->way[i] == NULL) continue;
            q.push(tmp->way[i]);
        }
        
    }
}


void seq2mst(mstnode*& MT,int arr[],int n,int &i,int z,int &p,int m,int d,int curr_depth)
{
    if (p==0) return;
    if (i>=n) return;
    if (z>n) return;

    if (curr_depth>d) 
    {
        //cout<<"i = "<<i<<" returned at curr_depth "<<curr_depth<<"\n";
        return;
    }

    if (curr_depth>1)
    {
        if (p<=z)
        {
            //cout<<"i = "<<i<<" overload depth "<<d<<"\n";
            return;
        }
    }

    if (MT==NULL)
        MT = new mstnode(m);

    int j,u;

    for (j=0;j<m-1;++j)
    {        
        u = pow(m+1,curr_depth) - 1 - p;
        if (i>n-1) return;
        seq2mst(MT->way[j],arr,n,i,u,p,m,d,curr_depth+1);
        cout<<"i = "<<i<<" filling "<<arr[i]<<" at depth = "<<curr_depth<<"\n";
        MT->key[j] = arr[i];        
        ++i;
        ++(MT->cnt);
        --p;
        
        if (curr_depth<d && curr_depth>1) --z;
    }
    
    seq2mst(MT->way[j],arr,n,i,u,p,m,d,curr_depth+1);
}

int main()
{
    int n,m;cin>>n>>m;//size of input buffer
    int arr[n];
    for (int i=0;i<n;++i)
        cin>>arr[i];

    

    float df = float(log(n+1))/log(m);
    int d = ceil(df);
    cout<<"max depth of tree : "<<d<<endl;
    int i=0;
    int p = n;
    int z = 0;
    mstnode*MT;
    seq2mst(MT,arr,n,i,z,p,m,d,1);
    cout<<"inorder : ";
    inorder(MT);
    cout<<"\nlevel : ";
    level(MT);
    cout<<"\n";
    //printarr(MT->way[0]->key,MT->way[0]->cnt);


    return 0;
}
/*
26 6
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26
*/