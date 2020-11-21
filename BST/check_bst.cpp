#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
using namespace std;

class TreeNode
{
public:
    TreeNode* left;
    int key;
    TreeNode* right;
    TreeNode()
    {
        left = right = NULL;
    }
};

void convT(TreeNode*&T)
{
    if (T==NULL) return;

    if (T->left ==NULL && T->right==NULL) return;

    if (T->left!=NULL && T->right==NULL)
    {
        int a,b;
        a = T->key;b = T->left->key;
        T->key = max(a,b);T->left->key = min(a,b);
        convT(T->left);
    }

    else if (T->left==NULL && T->right !=NULL)
    {
        int a,b;
        a = T->key;b = T->right->key;
        T->key = min(a,b);T->right->key = max(a,b);
        convT(T->right);
    }

    else{
        vector<int>v(3,0);
        v[0]=T->key;v[1]=T->left->key;v[2]=T->right->key;
        sort(v.begin(),v.end());
        T->left->key = v[0];
        T->key = v[1];
        T->right->key = v[2];
        convT(T->left);
        convT(T->right);
    }
}

int minT(TreeNode*T)
{
    if (T==NULL ) return INT_MAX;
    while(T->left!=NULL && T->right==NULL)
        T=T->left;
    
    return T->key;
}

int maxT(TreeNode*T)
{
    if (T==NULL) return INT_MIN;
    while(T->left !=NULL && T->right!=NULL)
        T=T->right;

    return T->key;
}

bool check_bst(TreeNode* &T)
{   
       if (T->left == NULL && T->right == NULL) return true;

        bool o;
        if (T->left !=NULL && T->right ==NULL)
        {
            int a = maxT(T->right);
            //b=T->left->key;
            //if (a==b) return false;
            if (T->key > a)
            {
                o = check_bst(T->left);
                if (!o)
                {
                    cout<<T->key<<"\n";
                    return false;
                }
                return true;
            }
            else 
                {
                    cout<<T->key<<"\n";
                    return false;
                }
        }
        else if (T->left == NULL && T->right !=NULL)
        {
            int b = minT(T->right);
            //if (a==b) return false;
            if (T->key < b)
            {
                o = check_bst(T->right);
                if (!o) 
                {
                    cout<<T->key<<"\n";
                    return false;
                }
                else return true;
            }
            else 
                {
                    cout<<T->key<<"\n";
                    return false;
                }
        }
            
        else
        {
            int a = maxT(T->left);
            int b = minT(T->right);
            if (a<T->key && T->key < b)
            {   
                o = check_bst(T->left);
                if (!o) 
                {
                    cout<<T->key<<"\n";
                    return false;
                }

                o = check_bst(T->right);
                if (!o)
                {
                    cout<<T->key<<"\n";
                    return false;
                }

                return true;
            }
            else 
                {
                    cout<<T->key<<"\n";
                    return false;
                }
        }

}

void inorder(TreeNode* T)
{
    if (T==NULL) return;

    if (T->left !=NULL )
    {
        inorder(T->left);
    }
    cout<<T->key<<" ";
    if (T->right != NULL)
    {
        inorder(T->right);
    }
}



int main()
{
    int a;
    TreeNode* T = new TreeNode(),*tmp;
    //Input 1
    T->key = 7; 
    tmp = new TreeNode();tmp->key = 9;
    T->left = tmp;
    tmp = new TreeNode();tmp->key = 6;
    T->right = tmp;
    tmp = new TreeNode();tmp->key = 2;
    T->left->left = tmp;
    tmp = new TreeNode();tmp->key = 4;
    T->left->right = tmp;
    tmp = new TreeNode();tmp->key = 1;
    T->right->left = tmp;
    tmp = new TreeNode();tmp->key = 3;
    T->right->right = tmp;
    tmp = new TreeNode();tmp->key = 8;
    T->left->left->left = tmp;
    tmp = new TreeNode();tmp->key = 11;
    T->left->left->right = tmp;
    
    
    cout<<minT(T)<<" = min "<<maxT(T)<<" = max";
    //Input 2
    /*T->key = 5;
    tmp = new TreeNode();tmp->key = 8;
    T->left =tmp;
    tmp = new TreeNode();tmp->key = 11;
    T->right = tmp;
    tmp = new TreeNode();tmp->key = 2;
    T->right->left = tmp;
    tmp = new TreeNode();tmp->key = 4;
    T->right->right = tmp;
    tmp = new TreeNode();tmp->key = 1;
    T->right->left->left = tmp;
    tmp = new TreeNode();tmp->key = 10;
    T->right->left->right = tmp;
    tmp = new TreeNode();tmp->key = 6;
    T->right->left->left->left =tmp;*/
    bool o = check_bst(T);
    if (o) cout<<"YES\n";
    else cout<<"NO\n";
    
    convT(T);
    inorder(T);
    o = check_bst(T);
    if (o) cout<<"YES\n";
    else cout<<"NO\n";
    cout<<T->left->key<<endl<<endl;
    return 0;
}

dvb