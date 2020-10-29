#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

class bstnode
{
public:
    bstnode* lchild;
    int data;
    bstnode* rchild;
    bstnode()
    {
        lchild = rchild = NULL;
    }
};


void input(bstnode* &T)
{
    char dir;//L for left  R for right X to terminate
    int data;bstnode* tmp;

    while(true)
    {
        cin>>dir;
        if (dir == 'X')
        {
            break;return;
        }
        cin>>data;
        tmp = new bstnode();

    }
}

void convT(bstnode*&T)
{
    if (T==NULL) return;

    if (T->lchild ==NULL && T->rchild==NULL) return;

    if (T->lchild!=NULL && T->rchild==NULL)
    {
        int a,b;
        a = T->data;b = T->lchild->data;
        T->data = max(a,b);T->lchild->data = min(a,b);
        convT(T->lchild);
    }

    else if (T->lchild==NULL && T->rchild !=NULL)
    {
        int a,b;
        a = T->data;b = T->rchild->data;
        T->data = min(a,b);T->rchild->data = max(a,b);
        convT(T->rchild);
    }

    else{
        vector<int>v(3,0);
        v[0]=T->data;v[1]=T->lchild->data;v[2]=T->rchild->data;
        sort(v.begin(),v.end());
        T->lchild->data = v[0];
        T->data = v[1];
        T->rchild->data = v[2];
        convT(T->lchild);
        convT(T->rchild);
    }
}

void inorder(bstnode* T)
{
    if (T==NULL) return;

    if (T->lchild !=NULL )
    {
        inorder(T->lchild);
    }
    cout<<T->data<<" ";
    if (T->rchild != NULL)
    {
        inorder(T->rchild);
    }
}


int main()
{
    int a;
    bstnode* T = new bstnode(),*tmp;
    //Input 1
    /*T->data = 7; 
    tmp = new bstnode();tmp->data = 9;
    T->lchild = tmp;
    tmp = new bstnode();tmp->data = 6;
    T->rchild = tmp;
    tmp = new bstnode();tmp->data = 2;
    T->lchild->lchild = tmp;
    tmp = new bstnode();tmp->data = 4;
    T->lchild->rchild = tmp;
    tmp = new bstnode();tmp->data = 1;
    T->rchild->lchild = tmp;
    tmp = new bstnode();tmp->data = 3;
    T->rchild->rchild = tmp;
    tmp = new bstnode();tmp->data = 8;
    T->lchild->lchild->lchild = tmp;
    tmp = new bstnode();tmp->data = 11;
    T->lchild->lchild->rchild = tmp;
    */


    //Input 2
    T->data = 5;
    tmp = new bstnode();tmp->data = 8;
    T->lchild =tmp;
    tmp = new bstnode();tmp->data = 11;
    T->rchild = tmp;
    tmp = new bstnode();tmp->data = 2;
    T->rchild->lchild = tmp;
    tmp = new bstnode();tmp->data = 4;
    T->rchild->rchild = tmp;
    tmp = new bstnode();tmp->data = 1;
    T->rchild->lchild->lchild = tmp;
    tmp = new bstnode();tmp->data = 10;
    T->rchild->lchild->rchild = tmp;
    tmp = new bstnode();tmp->data = 6;
    T->rchild->lchild->lchild->lchild =tmp;

    convT(T);
    inorder(T);

    return 0;
}
