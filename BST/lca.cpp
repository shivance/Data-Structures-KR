#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
using namespace std;

class bstnode
{
public:
    bstnode* lchild;char data;bstnode* rchild;
    bool v;
    bstnode()
    {
        lchild = rchild =  NULL;
        v = false;
    }
};

void markstk(stack<bstnode*>&stk)
{
    while(!stk.empty())
    {
        bstnode* tmp = stk.top();
        tmp->v = true;
        cout<<tmp->data<<" ";
        stk.pop();
    }
}

bool findQ(bstnode* &T,stack<bstnode*>&stk,char dt,char& par)
{
    if (T==NULL) return false;
    
    if (T->v) par = T->data;

    if (T->data == dt)  return true;

    if (T->data>dt)
    {
        findQ(T->lchild,stk,dt,par);
    }
    else
    {
        findQ(T->rchild,stk,dt,par);
    }
}

bool findP(bstnode* &T,stack<bstnode*>&stk,char dt)
{
    if (T==NULL) return false;
    stk.push(T);
    if (T->data == dt)
    {
        markstk(stk);
        return true;
    }

    if (T->data>dt)
    {
        findP(T->lchild,stk,dt);
    }
    else
    {
        findP(T->rchild,stk,dt);
    }
}


void insert(bstnode* &T,int k)
{
    if (T==NULL)
    {
        T = new bstnode();
        T->data = k;
    }
    else
    {
        if (T->data == k)
            return;
        else if (k<T->data)
        {
            insert(T->lchild,k);
        }
        else if (k> T->data)
        {
            insert(T->rchild,k);
        }
    }
}

int main()
{
    char a,x1,x2;
    bstnode* T = NULL;
    while(true)
    {
        cin>>a;
        if (a=='-') break;
        insert(T,a);
    }
    cin>>x1>>x2;
    stack<bstnode*> stk;
    bool o1 = findP(T,stk,x1);
    if (!o1)
    {
        cout<<"node not found";exit(0);
    }
    char par;
    o1 = findQ(T,stk,x2,par);
    if (!o1)
    {
        cout<<"node not found";exit(0);
    }
    cout<<"LCA = "<<par<<endl;

    return 0;
}