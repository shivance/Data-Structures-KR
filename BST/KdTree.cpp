#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class bstnode
{
public:
    bstnode* lchild;
    int *arr;
    bstnode* rchild;
    bstnode(int k[],int d)
    {
        lchild = rchild = NULL;
        arr = new int[d];
        for (int i=0;i<d;++i)
        {
            arr[i] = k[i];
        }
    }
};

void print(int arr[],int d)
{
    for (int i=0;i<d;++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


void insert(bstnode* &T,int k[],int lvl,int d)
{
    if (T==NULL)
    {
        T = new bstnode(k,d);
    }
    else
    {
        if (k[lvl%d]<T->arr[lvl%d])
        {
            insert(T->lchild,k,lvl+1,d);
        }
        else if (k[lvl%d]> T->arr[lvl%d])
        {
            insert(T->rchild,k,lvl+1,d);
        }
    }
}

bool equalarr(int k[],int m[],int d)
{
    bool flg =true;
    for (int i=0;i<d;++i)
    {
        if (k[i]!=m[i]) flg = false;
    }
    return flg;
}

void search(bstnode*T,int k[],int lvl,int d,bool &ans)
{
    if (T==NULL) return;
    else
    {
        if (k[lvl%d]== T->arr[lvl%d])
        {
            if (equalarr(T->arr,k,d)) ans = true;
        }
        else if (k[lvl%d]<T->arr[lvl%d])
        {
            search(T->lchild,k,lvl+1,d,ans);
        }
        else
        {
            search(T->rchild,k,lvl+1,d,ans);
        }
    }
}

void inorder(bstnode* T,int d)
{
    if (T==NULL) return;
    
    if (T->lchild !=NULL )
    {
        inorder(T->lchild,d);
    }
    print(T->arr,d);
    if (T->rchild != NULL)
    {
        inorder(T->rchild,d);
    }
} 

int main()
{
    int a,d;
    // input a = 1 if we want to insert a node
    // else -1 to exit
    cin>>d;
    
    bstnode* T = NULL;

    while(true)
    {
        cin>>a;
        if (a==-1) break;
        int v[d];
        for (int i=0;i<d;++i)
        {
            cin>>v[i];
        }
        
        insert(T,v,0,d);
    }
    
    inorder(T,d);
    bool ans = false;
    cout<<"Enter value to be searched : ";
    int v[d];
    while(true)
    {
        cin>>a;
        if (a==-1)
            break;
        for (int i=0;i<d;++i)
        {
            cin>>v[i];
        }
        ans = false;
        search(T,v,0,d,ans);
        if (ans) cout<<"Exist\n";
        else cout<<"Doesn't exist\n";
    }

    return 0;
}

/*
2
1 
20 5
1
3 18
1 
70 15
1
10 80
1
40 30
1
80 25
1
40 10
-1
*/