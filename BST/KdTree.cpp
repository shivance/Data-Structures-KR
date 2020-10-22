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
    bstnode(int d)
    {
        arr = new int[d];
        lchild = rchild = NULL;
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
        T = new bstnode(d);
        T->arr = k;
    }
    else
    {
        if (T->arr[lvl%d] == k[lvl%d])
            return;
        else if (k[lvl%d]<T->arr[lvl%d])
        {
            insert(T->lchild,k,lvl+1,d);
        }
        else if (k[lvl%d]> T->arr[lvl%d])
        {
            insert(T->rchild,k,lvl+1,d);
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
    cout<<"\n";
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
        print(v,d);
        insert(T,v,1,d);
    }
    cout<<"print\n";
    inorder(T,d);
    cout<<"\n";
    cout<<T->lchild->arr[0]<<" "<<T->lchild->arr[1];
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
40 30
1
80 25
1
40 10
-1
*/