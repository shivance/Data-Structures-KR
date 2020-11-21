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
    int key;
    bstnode* rchild;
    bstnode()
    {
        lchild = rchild = NULL;
    }
};


<<<<<<< HEAD
void input(bstnode* &T)
{
    char dir;//L for left  R for right X to terminate
    int key;bstnode* tmp;

    while(true)
    {
        cin>>dir;
        if (dir == 'X')
        {
            break;return;
        }
        cin>>key;
        tmp = new bstnode();

    }
}

void convT(bstnode*&T)
=======
void convT(node*&T)
>>>>>>> fad424c66c86420124e363383720740446ebd1a7
{
    if (T==NULL) return;

    if (T->lchild ==NULL && T->rchild==NULL) return;

    if (T->lchild!=NULL && T->rchild==NULL)
    {
        int a,b;
        a = T->key;b = T->lchild->key;
        T->key = max(a,b);T->lchild->key = min(a,b);
        convT(T->lchild);
    }

    else if (T->lchild==NULL && T->rchild !=NULL)
    {
        int a,b;
        a = T->key;b = T->rchild->key;
        T->key = min(a,b);T->rchild->key = max(a,b);
        convT(T->rchild);
    }

    else{
        vector<int>v(3,0);
        v[0]=T->key;v[1]=T->lchild->key;v[2]=T->rchild->key;
        sort(v.begin(),v.end());
        T->lchild->key = v[0];
        T->key = v[1];
        T->rchild->key = v[2];
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
    cout<<T->key<<" ";
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
    /*T->key = 7; 
    tmp = new bstnode();tmp->key = 9;
    T->lchild = tmp;
    tmp = new bstnode();tmp->key = 6;
    T->rchild = tmp;
    tmp = new bstnode();tmp->key = 2;
    T->lchild->lchild = tmp;
    tmp = new bstnode();tmp->key = 4;
    T->lchild->rchild = tmp;
    tmp = new bstnode();tmp->key = 1;
    T->rchild->lchild = tmp;
    tmp = new bstnode();tmp->key = 3;
    T->rchild->rchild = tmp;
    tmp = new bstnode();tmp->key = 8;
    T->lchild->lchild->lchild = tmp;
    tmp = new bstnode();tmp->key = 11;
    T->lchild->lchild->rchild = tmp;
    */


    //Input 2
    T->key = 5;
    tmp = new bstnode();tmp->key = 8;
    T->lchild =tmp;
    tmp = new bstnode();tmp->key = 11;
    T->rchild = tmp;
    tmp = new bstnode();tmp->key = 2;
    T->rchild->lchild = tmp;
    tmp = new bstnode();tmp->key = 4;
    T->rchild->rchild = tmp;
    tmp = new bstnode();tmp->key = 1;
    T->rchild->lchild->lchild = tmp;
    tmp = new bstnode();tmp->key = 10;
    T->rchild->lchild->rchild = tmp;
    tmp = new bstnode();tmp->key = 6;
    T->rchild->lchild->lchild->lchild =tmp;

    convT(T);
    inorder(T);

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> fad424c66c86420124e363383720740446ebd1a7
