#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class bstnode
{
    public:
    bstnode* lchild;
    int data;
    bstnode* rchild;
    int t;
    bstnode(int k)
    {
        t = k;
        lchild = rchild = NULL;
    }
};

void printvec(vector<int> &v)
{
    for (int i=0;i<v.size();++i)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

void prntvecnode(vector <bstnode*>&dt)
{
    for (int i=0;i<dt.size();++i)
    {
        cout<<dt[i]->data<<" "<<dt[i]->t<<endl;
    }
    cout<<endl;
}

void prntvecP(vector <pair<int,int>>&dt)
{
    for (int i=0;i<dt.size();++i)
    {
        cout<<dt[i].first<<" "<<dt[i].second<<endl;
    }
    cout<<endl;
}

bool sortf(bstnode* &n1,bstnode* &n2)
{
    return (n1->data< n2->data);
}

void insert(bstnode* &T,int k,int l,int Tn)
{
    if (T==NULL)
    {
        T = new bstnode(Tn);
        T->data = k;
    }
    else
    {
        if (T->data == k)
            return;
        else if (k<T->data)
        {
            insert(T->lchild,k,l+1,Tn);
        }
        else if (k> T->data)
        {
            insert(T->rchild,k,l+1,Tn);
        }
    }
}

void inorderU(bstnode* T,vector<bstnode*>&dt)
{
    if (T==NULL) return;

    if (T->lchild !=NULL )
    {
        inorderU(T->lchild,dt);
    }
    dt.push_back(T);
    if (T->rchild != NULL)
    {
        inorderU(T->rchild,dt);
    }
}


void mergeL(bstnode* T1,bstnode* T2,vector<bstnode*>&dt)
{
    inorderU(T1,dt);
    inorderU(T2,dt);
}

int main()
{
    int a;
    cout<<"First Tree input : ";
    bstnode* T1 = NULL;
    while(true)
    {
        cin>>a;
        if (a==-1) break;
        insert(T1,a,0,1);
    }
    cout<<"Second Tree input : ";
    bstnode* T2 = NULL;
    while(true)
    {
        cin>>a;
        if (a==-1) break;
        insert(T2,a,0,2);
    }

    vector<bstnode*>dt;
    
    mergeL(T1,T2,dt);
    sort(dt.begin(),dt.end(),sortf);
    //prntvecnode(dt);

    map<int,bool> mDT;
    map<int,int>mT;
    for (int i=0;i<dt.size();++i)
    {
        mDT[dt[i]->data] = true;
        mT[dt[i]->data] = dt[i]->t;
    }
    int sum;
    map<int,bool>::iterator it,itr,itx;

    set<vector<int> > ans; // set for storing final answer

    vector <int> tmp(3,0);
    for (it = mDT.begin();it!=mDT.end();++it)
    {
        sum = it->first;
        for (itr = mDT.begin();itr!=it;++itr)
        {
            itx = mDT.find(sum-(itr->first));
            if (itx == mDT.end()) continue;
            else
            {
                if (mT[sum-(itr->first)] != mT[itr->first])
                {
                    tmp[0]= itr->first;
                    tmp[1]= sum - itr->first;
                    tmp[2]= sum;
                    sort(tmp.begin(),tmp.end());
                    ans.insert(tmp);
                    // making vector of triplets because if we don't do this --> permutaion of each triplet
                    // will be involved in final answer
                }
            }
        }
    }

    set<vector<int>>::iterator its;
    for (its = ans.begin();its!=ans.end();++its)
    {
        cout<<(*its)[0]<<" "<<(*its)[1]<<" "<<(*its)[2]<<endl;
    }

    return 0;
}