#include <iostream>
#include <climits>
#include <algorithm>

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
/*
//version 1
void insertv1(mstnode*&MT,int k)
{
    if (k>MT->key[MT->cnt])
    {
        MT->key[MT->cnt] = k;
        MT->cnt++;
        return;
    }

    for (int i=0;i<MT->cnt;++i)
    {
        if (k>MT->key[i]) break;
    }

    MT->way[i] = new mstnode(MT->m);
    insertv1(MT->way[i],k);
}
*/

void printarr(mstnode* arr[],int m)
{
    cout<<"Content : ";
    for (int i=0;i<m;++i) cout<<arr[i]-><<" ";
    cout<<"\n";
}


void printNarr(mstnode* arr[],int m)
{
    cout<<"Content : ";
    for (int i=0;i<m;++i) cout<<arr[i]-><<" ";
    cout<<"\n";
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
        cout<<"k = "<<k<<"\n";
        return;
    }
    int i;
    for (i=0;i<MT->cnt;++i)
    {
        if (k>MT->key[i]) break;
    }
    
    insertv2(MT->way[i],k,m);
    
}


void inorder(mstnode*&MT)
{
    if (MT==NULL || MT->cnt==0)
        return;
    //printarr(MT->key,MT->cnt);
    int i;
    for (i=0;i<MT->cnt;++i)
    {
        inorder(MT->way[i]);
        cout<<MT->key[i]<<" ";
    }
    inorder(MT->way[i]);
}

int main()
{
    int m;cin>>m;
    int a;
    mstnode* MT = NULL;
    while(true)
    {
        cin>>a;
        if (a==0) break;
        insertv2(MT,a,m);
    }

    cout<<"Inorder : \n";
    //inorder(MT);
    //cout<<"\n";
    mstnode* x = MT->way[0];
    printarr(x->way,x->cnt);
    return 0;
}

