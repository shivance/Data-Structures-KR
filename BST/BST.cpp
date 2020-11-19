#include <iostream>
#include <climits>
#include <cstdlib>
#include <queue>
using namespace std;

class BSTnode
{
public:
    int data;
    BSTnode* lc,*rc;
    bool lvlend;
    BSTnode()
    {
        lc = rc = NULL;
        lvlend = false;
        data = INT_MIN;
    }
};

void insert(BSTnode*&BST,int k)
{
    if (BST == NULL)
    {
        BST = new BSTnode();
        BST->data = k;
        return ;
    }

    if (BST->data > k)
        insert(BST->lc,k);

    else if (BST->data < k)
        insert(BST->rc,k);
}

void inorder(BSTnode* BST)
{
    if(BST==NULL) return;

    inorder(BST->lc);
    cout<<BST->data<<" ";
    inorder(BST->rc);
}

BSTnode* min(BSTnode* BST)
{
    while(BST->lc!=NULL)
        BST=BST->lc;

    return BST;
}

BSTnode* max(BSTnode* BST)
{
    while(BST->rc!=NULL)
        BST=BST->rc;

    return BST;
}

BSTnode* find(BSTnode* BST,int key)
{
    if (BST->data == key) return BST;
    if(BST==NULL) return NULL;

    if (BST->data > key) find(BST->lc,key);
    else if (BST->data <key) find(BST->rc,key);
}

BSTnode* parent(BSTnode* BST,int key)
{
    if (key<BST->data)
    {
        if (BST->lc->data == key) return BST;
        else return parent(BST->lc,key);
    }
    else if (key>BST->data)
    {
        if (BST->rc->data == key) return BST;
        else return parent(BST->rc,key);
    }
    else return NULL;
}

void predsucc(BSTnode* root,BSTnode*&pre,BSTnode*&succ,int key)
{
    if (root==NULL) return ;
    if (root->data == key)
    {
        if (root->lc !=NULL)
            pre = max(root->lc);
        if (root->rc!=NULL)
            succ = min(root->rc);
        
        return;
    }

    if (root->data<key)
    {
        pre=root;
        predsucc(root->rc,pre,succ,key);
    }
    else
    {
        succ = root;
        predsucc(root->lc,pre,succ,key);
    }
}

BSTnode* del(BSTnode* T,int key)
{
    if (T==NULL) 
        return T; 

    if (key < T->data)
        T->lc = del(T->lc,key);
    
    else if (key > T->data)
        T->rc = del(T->rc,key);

    else{ //key was found
        // returns leaf as well
        if(T->lc==NULL){
            BSTnode* tmp = T->rc;
            free(T);
            return tmp;
        }
        else if (T->rc==NULL){
            BSTnode* tmp = T->lc;
            free(T);
            return tmp;
        }

        BSTnode* tmp = min(T->rc);
        
        T->data = tmp->data;
        T->rc = del(T->rc,T->data);
    }

    return T;
}

void BFS(BSTnode*& T)
{
    queue<BSTnode*> q;
    T->lvlend = true;
    q.push(T);

    BSTnode* tmp = NULL;
    while(!q.empty())
    {
        tmp = q.front();
        q.pop();

        cout<<tmp->data<<" ";
        if (tmp->lc != NULL)
            q.push(tmp->lc);
        
        if (tmp->rc!=NULL)
            q.push(tmp->rc);
    }
}

int main()
{
    BSTnode* BST = NULL;

    int k;
    while(true)
    {
        cin>>k;
        if (k==-1) break;
        insert(BST,k);
    }
    
    cout<<"INORDER : ";inorder(BST);cout<<"\n";
    BSTnode* prec,*succ;
    prec = succ =NULL;
    cout<<"Pecdecessor and successor : \n";
    while(true)
    {
        cin>>k;
        if (k==-1) break;
        //cout<<parent(BST,k)->data<<"\n";
        predsucc(BST,prec,succ,k);
        if (prec!=NULL)
        {
            cout<<"predecessor : "<<prec->data<<" ";
        }
        else cout<<"No predecessor ";
        if (succ!=NULL)
        {
            cout<<"successor : "<<succ->data<<'\n';
        }
        else cout<<" No successor\n";
        prec = succ =NULL;
    }
    cout<<"Delete : \n";
    while(true)
    {
        cin>>k;
        if (k==-1) break;
        del(BST,k);
        cout<<"current level order : ";
        BFS(BST);
        cout<<"\n";
    }

    return 0;
}

// 7 6 4 2 5 21 9 97 25 98 