/*
Binary Search Tree – Levels  
Create a binary tree with given input key.

Print all the following level orders.

Input key: 5 8 3 4 1 9 6 7 2 -1

Output level orders :

1. Level order :   5 3 8 1 4 6 9 2 7

2. Reverse reversed level order: 

7 2 9 6 4 1 8 3 5

3. Reverse level order : 

2 7 1 4 6 9 3 8 5

4. Squirrel level order (clock-wise start): 

5 8 3 1 4 6 9 7 2

5. Squirrel level order (anti-clock-wise start):

5 3 8 9 6 4 1 2 7

6. Alternate odd-level reversal level order :

5 8 3 1 4 6 9 7 2

7. Alternate even-level reversal level order:

5 3 8 9 6 4 1 2 7

Test case:

input ( cin >> ) : 5 8 3 4 1 9 6 7 2 -1

output ( cout >>) :

5 3 8 1 4 6 9 2 7

7 2 9 6 4 1 8 3 5

2 7 1 4 6 9 3 8 5

5 8 3 1 4 6 9 7 2

5 3 8 9 6 4 1 2 7

5 8 3 1 4 6 9 7 2

5 3 8 9 6 4 1 2 7 
*/

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
    int key,lvl;
    bstnode* rchild;
    bstnode()
    {
        lvl = 0;
        lchild = rchild = NULL;
    }
};

void printstk(stack<bstnode*> &stk)
{
    while(!stk.empty())
    {
        cout<<stk.top()->key<<" ";
        stk.pop();
    }
}

void printq(queue<bstnode*> &q)
{
    while(!q.empty())
    {
        cout<<q.front()->key<<" ";
        q.pop();
    }
}

void insert(bstnode* &T,int k,int l)
{
    if (T==NULL)
    {
        T = new bstnode();
        T->key = k;
        T->lvl = l;
    }
    else
    {
        if (T->key == k)
            return;
        else if (k<T->key)
        {
            insert(T->lchild,k,l+1);
        }
        else if (k> T->key)
        {
            insert(T->rchild,k,l+1);
        }
    }
}

void inorder(bstnode* T)
{
    if (T==NULL) return;

    if (T->lchild !=NULL )
    {
        inorder(T->lchild);
    }
    cout<<T->key<<" ";
    if (T->rchild != NULL)
    {
        inorder(T->rchild);
    }
} 

void post(bstnode* T)
{
    if (T==NULL) return;
    
    post(T->lchild);
    post(T->rchild);
    cout<<T->key<<" ";

    return;
}

void level(bstnode* T)
{
    bstnode* tmp,*tmpn;
    queue<bstnode*> q;
    //tmp = T;
    q.push(T);
    while(!q.empty())
    {
        tmp = q.front();
        cout<<tmp->key<<" ";
        if (tmp->lchild!=NULL) q.push(tmp->lchild);
        if (tmp->rchild!=NULL) q.push(tmp->rchild);
        q.pop();
    }
    
}

void revrevL(bstnode* T)
{
    bstnode* tmp;
    stack<bstnode*> stk;
    queue<bstnode*> q;
    //tmp = T;
    q.push(T);
    while(!q.empty())
    {
        tmp = q.front();
        stk.push(tmp);
        if (tmp->lchild!=NULL) q.push(tmp->lchild);
        if (tmp->rchild!=NULL) q.push(tmp->rchild);
        q.pop();
    }
    printstk(stk);
}

void squiLClk(bstnode* T)
{
    bstnode* tmp,*tmpn;
    queue<bstnode*> q,qtk;
    stack <bstnode*> stk;
    //int c = 1;
    q.push(T);
    cout<<T->key<<" ";
    int x = T->lvl;
    while(!q.empty())
    {
        tmp = q.front();
        if (tmp->lvl != x)
        {
            if (x&1) printq(qtk);
            else printstk(stk);
            x = tmp->lvl;
        }
        if (tmp->lchild!=NULL) 
        {
            q.push(tmp->lchild);
            if (x&1) qtk.push(tmp->lchild);
            else stk.push(tmp->lchild);
    
        }
        if (tmp->rchild!=NULL)
        {
            q.push(tmp->rchild);
            if (x&1) qtk.push(tmp->rchild);
            else stk.push(tmp->rchild);
        }
        q.pop();
    }
}

void squiLAntiClk(bstnode* T)
{
    bstnode* tmp,*tmpn;
    queue<bstnode*> q,qtk;
    stack <bstnode*> stk;
    //int c = 1;
    q.push(T);
    cout<<T->key<<" ";
    int x = T->lvl;
    while(!q.empty())
    {
        tmp = q.front();
        if (tmp->lvl != x)
        {
            if (x&1) printstk(stk);
            else printq(q);
            x = tmp->lvl;
        }
        if (tmp->lchild!=NULL) 
        {
            q.push(tmp->lchild);
            if (x&1) stk.push(tmp->lchild);
            else qtk.push(tmp->lchild);
    
        }
        if (tmp->rchild!=NULL)
        {
            q.push(tmp->rchild);
            if (x&1) stk.push(tmp->rchild);
            else qtk.push(tmp->rchild);
        }
        q.pop();
    }
}


void revL(bstnode* T)
{
    bstnode* tmp,*tmpn;
    queue<bstnode*> q;
    stack <bstnode*> stk;
    q.push(T);
    cout<<T->key<<" ";
    int x = T->lvl;
    while(!q.empty())
    {
        tmp = q.front();
        if (tmp->lvl != x)
        {
            if (x&1) printq(q);
            else printstk(stk);
            x = tmp->lvl;
        }
        if (tmp->lchild!=NULL) 
        {
            q.push(tmp->lchild);
            stk.push(tmp->lchild);
        }
        if (tmp->rchild!=NULL)
        {
            q.push(tmp->rchild);
            stk.push(tmp->rchild);
        }
        q.pop();
    }
}

int main()
{
    int a;
    bstnode* T = NULL;
    while(true)
    {
        cin>>a;
        if (a==-1) break;
        insert(T,a,0);
    }
    cout<<"Squirrel clockwise : ";
    squiLClk(T);cout<<endl;
    cout<<"Squirrel Anticlock : ";
    squiLAntiClk(T);cout<<endl;
    cout<<"Reverse level order : ";
    revL(T);cout<<endl;
    cout<<"Reverse reversed level order : ";
    revrevL(T);cout<<endl;
    cout<<"level : ";
    level(T);cout<<endl;
    cout<<"odd level reversal level order :";
    squiLClk(T);cout<<endl;
    cout<<"alternate even level reversal level order : "
    squiLAntiClk(T);cout<<endl;

    return 0;
}

