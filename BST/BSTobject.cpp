#include <iostream>
#include <climits>
#include <cstdlib>
#include <queue>
using namespace std;

template <typename D>
class BSTnode
{
public:
    D key;
    BSTnode* lc,*rc;
    bool lvlend;
    BSTnode()
    {
        lc = rc = NULL;
        lvlend = false;
    }
};

template <typename D>
deque<BSTnode<D> > nodeCache;

template <typename D>
BSTnode<D>* newBSTnode()
{
    nodeCache<D>.push_back(BSTnode<D>());
    BSTnode<D>* node = &nodeCache<D>.back();
    return node;
}

template <typename D>
class BinST{
    private:
        BSTnode<D>* BST; 

    public:
        BinST()
        {
            BST = NULL;
        }

        void insertU(BSTnode<D>*&BST,D k)
        {
            if (BST == NULL)
            {
                BST = newBSTnode<D>();
                BST->key = k;
                return ;
            }

            if (BST->key > k)
                insertU(BST->lc,k);

            else if (BST->key < k)
                insertU(BST->rc,k);
        }

        void insert(D key){
            return insertU(BST,key);
        }

        void inorderU(BSTnode<D>* BST)
        {
            if(BST==NULL) return;

            inorderU(BST->lc);
            cout<<BST->key<<" ";
            inorderU(BST->rc);
        }

        void inorder(){
            inorderU(BST);
        }

        BSTnode<D>* minU(BSTnode<D>* BST)
        {
            while(BST->lc!=NULL)
                BST=BST->lc;

            return BST;
        }
        
        BSTnode<D>* min(){
            return minU(BST);
        }

        BSTnode<D>* maxU(BSTnode<D>* BST)
        {
            while(BST->rc!=NULL)
                BST=BST->rc;

            return BST;
        }

        BSTnode<D>* max(){
            return maxU(BST);
        }

        BSTnode<D>* findU(BSTnode<D>* BST,D key)
        {
            if (BST->key == key) return BST;
            if(BST==NULL) return NULL;

            if (BST->key > key) findU(BST->lc,key);
            else if (BST->key <key) findU(BST->rc,key);
        }

        BSTnode<D>* find(D key){
            return findU(BST,key);
        }

        BSTnode<D>* parent(BSTnode<D>* BST,D key)
        {
            if (key<BST->key)
            {
                if (BST->lc->key == key) return BST;
                else return parent(BST->lc,key);
            }
            else if (key>BST->key)
            {
                if (BST->rc->key == key) return BST;
                else return parent(BST->rc,key);
            }
            else return NULL;
        }

        void predsuccU(BSTnode<D>* root,BSTnode<D>*&pre,BSTnode<D>*&succ,D key)
        {
            if (root==NULL) return ;
            if (root->key == key)
            {
                if (root->lc !=NULL)
                    pre = maxU(root->lc);
                if (root->rc!=NULL)
                    succ = minU(root->rc);
                
                return;
            }

            if (root->key<key)
            {
                pre=root;
                predsuccU(root->rc,pre,succ,key);
            }
            else
            {
                succ = root;
                predsuccU(root->lc,pre,succ,key);
            }
        }

        void predsucc(BSTnode<D>* &pre,BSTnode<D>* &succ,D key)
        {
            predsuccU(BST,pre,succ,key);
        }

        BSTnode<D>* delU(BSTnode<D>* T,D key)
        {
            if (T==NULL) 
                return T; 

            if (key < T->key)
                T->lc = delU(T->lc,key);
            
            else if (key > T->key)
                T->rc = delU(T->rc,key);

            else{ //key was found
                // returns leaf as well
                if(T->lc==NULL){
                    BSTnode<D>* tmp = T->rc;
                    free(T);
                    return tmp;
                }
                else if (T->rc==NULL){
                    BSTnode<D>* tmp = T->lc;
                    free(T);
                    return tmp;
                }

                BSTnode<D>* tmp = minU(T->rc);
                
                T->key = tmp->key;
                T->rc = delU(T->rc,T->key);
            }

            return T;
        }

        BSTnode<D>* del(D key)
        {
            return delU(BST,key);
        }

        void bfsU(BSTnode<D> *& T)
        {
            queue<BSTnode<D>*> q;
            T->lvlend = true;
            q.push(T);

            BSTnode<D>* tmp = NULL;
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
            bfsU(BST);
        }


};


int main()
{
    BinST<int> T;
    BSTnode<int>* pre=NULL,*succ=NULL;

    int k;
    while(true)
    {
        cin>>k;
        if (k==-1) break;
        T.insert(k);
    }
    
    cout<<"INORDER : ";T.inorder();cout<<"\n";

    cout<<"Pecdecessor and successor : \n";
    while(true)
    {
        cin>>k;
        if (k==-1) break;
        //cout<<parent(BST,k)->key<<"\n";
        T.predsucc(pre,succ,k);
        if (pre!=NULL)
        {
            cout<<"predecessor : "<<pre->key<<" ";
        }
        else cout<<"No predecessor ";
        if (succ!=NULL)
        {
            cout<<"successor : "<<succ->key<<'\n';
        }
        else cout<<" No successor\n";
        pre = succ =NULL;
    }
    cout<<"Delete : \n";
    BSTnode<int>* delnode;
    while(true)
    {
        cin>>k;
        if (k==-1) break;
        delnode = T.del(k);
        cout<<delnode->key<<" deleted from tree\n";
        cout<<"current level order : ";
        T.bfs();
        cout<<"\n";
    }

    return 0;
}

// 7 6 4 2 5 21 9 97 25 98