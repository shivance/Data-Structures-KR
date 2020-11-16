#include <iostream>
#include <climits>
#include <algorithm>
#include <queue>

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

void printarr(int arr[],int m)
{
    for (int i=0;i<m;++i)
    {
        cout<<arr[i]<<" ";
    }
}

//version 1
void insertv1(mstnode*&MT,int k,int m)
{
    if (MT==NULL)
    {
        MT=new mstnode(m);
    }
    if (k>MT->key[MT->cnt-1] && MT->cnt<m-1)
    {
        MT->key[MT->cnt] = k;
        MT->cnt = MT->cnt+1;
        return;
    }
    int i;
    for (i=0;i<MT->cnt;++i)
    {
        if (k<MT->key[i]) break;
    }

    insertv1(MT->way[i],k,m);
}



//version 2 --> insert and sort
void insertv2(mstnode*&MT,int k,int m)
{
    if (MT==NULL)
    {
        MT=new mstnode(m);
    }
    if (k>MT->key[MT->cnt] && MT->cnt<m-1)
    {
        MT->key[MT->cnt] = k;
        MT->cnt=MT->cnt + 1;
        sort(MT->key,MT->key+(MT->cnt));
        return;
    }
    int i;
    for (i=0;i<MT->cnt;++i)
    {
        if (k<MT->key[i]) break;
    }
    
    insertv2(MT->way[i],k,m);
    
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

BTnode* search(BTnode*BT,int k)
{
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        if(BT->key[i]==k)
            return BT;
        else if (BT->key[i]>k)
            break;
    }

    if (i==BT->cnt)
    {
        if (BT->way[i]==NULL)
            return BT;
        else 
            return search(BT->way[i],k);
    }
}

BTnode* parent(BTnode* BT,BTnode* node)
{
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        if (BT->key[i]>node->key[0]) break;
    }
    if (BT->way[i] == node) return BT;
    else return parent(BT->way[i],node);
}


int main()
{
    int m;cin>>m;
    int a;
    mstnode* MT = NULL;
    mstnode* MT1 = NULL;
    while(true)
    {
        cin>>a;
        if (a==0) break;
        insertv1(MT1,a,m);
        insertv2(MT,a,m);
    }

    inorder(MT);  
    cout<<"\n";  
    
    while(true)
    {
        cin>>a;
        BTnode* leaf = search(BT,k);
        cout<<"leaf : "
        printarr(leaf->key,leaf->cnt);
        cout<<"\n";
        BTnode* par = parent(BT,leaf);
        cout<<"parent : ";
        printarr(par->key);
    }
    
    return 0;
}

