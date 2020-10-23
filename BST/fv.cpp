#include <iostream>
#include <climits>

using namespace std;

class node
{
public:    
    node* lc,*rc;
    int arr[3];
    node()
    {
        lc=rc=NULL;
        arr[0]=arr[1]=arr[2]=INT_MIN;
    }
};

void print(int arr[])
{
    for (int i=2;i>=0;--i)
    {
        if (arr[i]!=INT_MIN)
        {
            cout<<arr[i]<<" ";
            break;
        }
    }
}

void inputT(node* &tmp,int loc)
{
    int a;cin>>a;
    if (a==-1) return;

    if (a==1)
    {
        cin>>a;node* tmpn;
        if (tmp->lc==NULL){
            tmpn = new node();
            tmpn->arr[loc] = a;
            tmp->lc = tmpn;
        }
        else 
        {
            tmpn = tmp->lc;
            tmpn->arr[loc] = a;
        }
        inputT(tmpn,loc);

        cin>>a;
        if (a==-1) return;
        node* tmpx;
        if (tmp->rc == NULL){
            tmpx = new node();
            tmpx->arr[loc] = a;
            tmp->rc = tmpx;
        }
        else
        {
            tmpx = tmp->rc;
            tmpx->arr[loc] = a;
        }
        inputT(tmpx,loc);
    }

    else if (a==0)
    {
        cin>>a;
        if (a==-1) return;
        node* tmpn;
        if (tmp->rc==NULL)
        {
            tmpn = new node();
            tmpn->arr[loc] = a;
            tmp->rc = tmpn;
        }
        else
        {
            tmpn = tmp->rc;
            tmpn->arr[loc] = a;
        }
        inputT(tmpn,loc);
    }
}

void inorder(node* &T,int loc)
{
    if (T==NULL) return;

    if (T->lc !=NULL )
    {
        inorder(T->lc,loc);
    }
    print(T->arr);
    //cout<<T->arr[loc]<<" ";
    if (T->rc != NULL)
    {
        inorder(T->rc,loc);
    }
}

void frontV(node* &T)
{
    if (T==NULL) return;

    if (T->lc !=NULL )
    {
        frontV(T->lc);
    }
    print(T->arr);
    if (T->rc != NULL)
    {
        frontV(T->rc);
    }
}

int main()
{
    int a,tinp;
    node* T = new node();
    
    
    for (int i=0;i<3;++i)
    {
        cin>>a;
        T->arr[i] = a;
        inputT(T,i); 
    }

    frontV(T);

    return 0;   
}

/*
8 1 4 1 2 0 -1 6 0 -1 10 0 12 0 -1
5 1 21 0 -1 11 1 9 1 7 0 -1 -1 15 0 -1
16 1 3 0 14 0 -1 20 1 17 0 19 1 18 0 -1 -1 -1
*/

