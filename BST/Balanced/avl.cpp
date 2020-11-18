#include <iostream>
#include <deque>
using namespace std;

class AVLnode
{
public:
    AVLnode* lc;
    int key;
    AVLnode *rc;
    int h;
    AVLnode(int k)
    {
        key = k;
        lc = rc = NULL;
        h = 1;
    }
};

deque<AVLnode> nodeCache;

AVLnode* newAVLnode(int k)
{
    nodeCache.push_back(AVLnode(k));
    AVLnode* node = &nodeCache.back();
    return node;
}

int height(AVLnode* T)
{
    if (T==NULL) return 0;
    return T->h;
}

AVLnode* leftR(AVLnode* T)
{
	AVLnode* x = T->rc;
	AVLnode* T2 = x->lc;

	x->lc = T;
	T->rc = T2;

    T->h = max(height(T->lc),height(T->rc)) + 1;
    x->h = max(height(x->lc),height(x->rc)) + 1;

	return x;
}

AVLnode* rightR(AVLnode* T)
{
	AVLnode* x = T->lc;
	AVLnode* T2 = x->rc;

	x->rc = T;
	T->lc = T2;

    T->h = max(height(T->lc),height(T->rc)) + 1;
    x->h = max(height(x->lc),height(x->rc)) + 1;

	return x;
}

int loadf(AVLnode* T)
{
    if (T==NULL)
        return 0;
    return (height(T->lc) - height(T->rc));
}

void insert(AVLnode* &T,int k)
{
    if (T==NULL)
    {
        T = newAVLnode(k);
        return ;
    }
        

    if (k<T->key)
        insert(T->lc,k);
    
    else if (k>T->key)
        insert(T->rc,k);
    
    else 
        return;


    T->h = 1 + max(height(T->lc),height(T->rc));

    int load = loadf(T);

    // LL -> Right rotation
    if (load > 1 && k < T->lc->key)
        T = rightR(T);

    // RR -> left rotation
    else if (load < -1 && k > T->rc->key)
        T = leftR(T);
    

    // LR -> right left rotation
    else if (load > 1 && k > T->lc->key)
    {
        T->lc = leftR(T->lc);
        T = rightR(T);
    }

    // RR -> left right 
    else if (load < -1 && k < T->rc->key){
        T->rc = rightR(T->rc);
        T = leftR(T);
    }

    return;
}

void inorder(AVLnode*T)
{
    if (T==NULL)
        return;
    
    inorder(T->lc);
    cout<<T->key<<" ";
    inorder(T->rc);
}

int main()
{
    AVLnode* T = NULL;
    int a;

    while(true)
    {
        cin>>a;
        if (a==-1) break;
        insert(T,a);
        inorder(T);
        cout<<"\nroot -> key = "<<T->key<<"\n";
    }

    inorder(T);
    return 0 ;
}


