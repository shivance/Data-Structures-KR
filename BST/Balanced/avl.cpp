#include <iostream>
#include <deque>
using namespace std;

template <typename D>
class AVLnode
{
public:
    AVLnode* lc;
    D key;
    AVLnode *rc;
    int h;
    AVLnode(D k)
    {
        key = k;
        lc = rc = NULL;
        h = 1;
    }
};

template <typename D>
deque<AVLnode<D> > nodeCache;

template <typename D>
AVLnode<D>* newAVLnode(D k)
{
    nodeCache<D>.push_back(AVLnode<D>(k));
    AVLnode<D>* node = &nodeCache<D>.back();
    return node;
}

template <typename D>
class AVL
{
    AVLnode<D>* T = NULL;
public:
    int height(AVLnode<D>* T)
    {
        if (T==NULL) return 0;
        return T->h;
    }

    AVLnode<D>* leftR(AVLnode<D>* T)
    {
        AVLnode<D>* x = T->rc;
        AVLnode<D>* T2 = x->lc;

        x->lc = T;
        T->rc = T2;

        T->h = max(height(T->lc),height(T->rc)) + 1;
        x->h = max(height(x->lc),height(x->rc)) + 1;

        return x;
    }

    AVLnode<D>* rightR(AVLnode<D>* T)
    {
        AVLnode<D>* x = T->lc;
        AVLnode<D>* T2 = x->rc;

        x->rc = T;
        T->lc = T2;

        T->h = max(height(T->lc),height(T->rc)) + 1;
        x->h = max(height(x->lc),height(x->rc)) + 1;

        return x;
    }

    int loadf(AVLnode<D>* T)
    {
        if (T==NULL)
            return 0;
        return (height(T->lc) - height(T->rc));
    }
    
    void insertU(AVLnode<D>* &T,D k)
    {
        if (T==NULL)
        {
            T = newAVLnode<D>(k);
            return ;
        }
            
        if (k<T->key)
            insertU(T->lc,k);
        
        else if (k>T->key)
            insertU(T->rc,k);
        
        else return;

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

    void insert(D key)
    {
        insertU(T,key);
    }

    void inorderU(AVLnode<D>*T)
    {
        if (T==NULL)
            return;
        
        inorderU(T->lc);
        cout<<T->key<<" ";
        inorderU(T->rc);
    }

    void inorder()
    {
        inorderU(T);
    }
};



int main()
{
    AVL<int> T;
    int a;

    while(true)
    {
        cin>>a;
        if (a==-1) break;
        T.insert(a);

        T.inorder();
        //cout<<"\nroot -> key = "<<T->key<<"\n";
    }

    return 0 ;
}


