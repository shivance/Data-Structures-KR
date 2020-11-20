// compile with following command : g++ -std=gnu++14 avl.cpp

#include <iostream>
#include <deque>
#include <queue>
#include <cstdlib>
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

        AVLnode<D>* delU(AVLnode<D>* T,D key)
        {
            //cout<<"T->key : "<<T->key<<'\n';
            if (T==NULL){ 
                //cout<<"T==NULL\n";
                return T;
            } 

            if (key < T->key){
                T->lc = delU(T->lc,key);
                //cout<<"Now at T->key = "<<T->key<<"\n";
            }
            
            else if (key > T->key){
                T->rc = delU(T->rc,key);
                //cout<<"Now at T->key = "<<T->key<<"\n";
            }

            else{ //key was found
                // returns leaf as well
                if(T->lc==NULL)
                {
                    //cout<<"Check T->lc == NULL\n";
                    //cout<<"T->lc==NULL returned\n";
                    return T->rc;
                }
                else if (T->rc==NULL)
                {
                    //cout<<"Check T->rc == NULL\n";
                    //cout<<"T->rc==NULL returned\n";
                    return T->lc;
                }

                // none of child is  null
                AVLnode<D>* tmp = minU(T->rc);
                T->key = tmp->key;
                T->rc = delU(T->rc,T->key);
            }

            if (T==NULL) 
            {
                //cout<<"T=NULL 2 returned\n";
                return T;
            }

            T->h = 1 + max(height(T->lc),height(T->rc));

            int load = loadf(T);

            // LL -> Right rotation
            if (load > 1 && loadf(T->lc)>=0)
            {
                //cout<<"Right rotation \n";
                T = rightR(T);
            }

            // RR -> left rotation
            else if (load < -1 && loadf(T->rc)<=0){
                //cout<<"Left Rotation \n";
                T = leftR(T);
                
            }

            // LR -> right left rotation
            else if (load > 1 && loadf(T->lc) <0)
            {
                //cout<<"Right left \n";
                T->lc = leftR(T->lc);
                T =  rightR(T);
            }

            // RR -> left right 
            else if (load < -1 && loadf(T->rc)>0){
                //cout<<"left right\n";
                T->rc = rightR(T->rc);
                T = leftR(T);
            }

            return T;
        }

        AVLnode<D>* minU(AVLnode<D>* T)
        {
            while(T->lc!=NULL)
                T=T->lc;

            return T;
        }
        
        AVLnode<D>* min(){
            return minU(T);
        }

        AVLnode<D>* maxU(AVLnode<D>* T)
        {
            while(T->rc!=NULL)
                T=T->rc;

            return T;
        }

        AVLnode<D>* maxT(){
            return maxU(T);
        }

        void del(D key)
        {
            T = delU(T,key);
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

        void bfsU(AVLnode<D> *& T)
        {
            if(T==NULL) return;
            queue<AVLnode<D>*> q;
            q.push(T);

            AVLnode<D>* tmp = NULL;
            while(!q.empty())
            {
                tmp = q.front();
                q.pop();

                cout<<tmp->key<<" ";
                if (tmp->lc != NULL)
                    q.push(tmp->lc);
                
                if (tmp->rc!=NULL)
                    q.push(tmp->rc);
            }
        }

        void bfs(){
            bfsU(T);
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
        cout<<"\n";
    }
    T.bfs();

    AVLnode<int>* delnode;
    while(true)
    {
        cin>>a;
        if (a==-1) break;
        T.del(a);
        
        cout<<"current level order : ";
        T.bfs();
        cout<<"\n";
    }


    return 0 ;
}


