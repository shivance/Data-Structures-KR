#include <iostream>
#include <deque>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class BTnode
{
public:
    int cnt;
    int cnt_w;
    int d;
    

    BTnode(int d)
    {
        this->d = d;
        deque<int>key;
        deque<BTnode*>way;
        cnt = 0;
        cnt_w = 0;
        way.push_back(NULL);
    }
};

void printdq(deque<int>key)
{
    for (int i=0;i<key.size();++i)
    {
        cout<<key.at(i)<<" ";
    }
}


void level(BTnode*&MT)
{
    BTnode* tmp;
    deque<BTnode*> q;

    q.push_back(MT);
    while(!q.empty())
    {
        tmp = q.front();
        printdq(tmp->key);
        q.pop_front();

        int i;
        for (i=0;i<=tmp->cnt;++i)
        {
            if (tmp->way[i] == NULL) continue;
            q.push_back(tmp->way[i]);
        }
    }
}

void getidx(deque<int>dq,int &idx,int k)
{
    for (int i=0;i<dq.size();++i)
    {
        if (dq.at(i)==k)
        {
            idx = i;break;
        }
    }
}

BTnode* search(BTnode*BT,int k)
{
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        if(BT->key[i]==k)
            return BT;
        else if (BT->key[i]>k)
        {
            if (BT->way[i]==NULL) return BT;
            else return search(BT->way[i],k);
        }
    }

    if (i==BT->cnt)
    {
        if (BT->way[i]==NULL)
            return BT;
        else 
            return search(BT->way[i],k);
    }
}

void Add(BTnode* & BT,BTnode* &left,BTnode* &ri8,int d,int k)
{
    if (BT==NULL) 
    {
        BT = new BTnode(d);
        BT->key.push_back(k);
        BT->cnt++;
        BT->way.push_back(NULL);
        BT->way.push_back(NULL);
        return;
    }

    BTnode* leaf = search(BT,k);

    //no overflow
    if (BT->cnt < d-1)
    {
        leaf->key.push_back(k);
        ++(leaf->cnt);
        sort(leaf->key.begin(),leaf->key.end());
        leaf->way.push_back(NULL);
        int idx = -1;
        getidx(leaf->key,idx,k);
        left = leaf->way[idx];
        ri8 = leaf->way[idx+1];
    }

    else
    {
        BTnode* newchild = new BTnode(d);
        deque<int>tmp;
        for (int i=0;i<leaf->cnt;++i) 
        {
            tmp.push_back(leaf->key.at(i));
            leaf->key.pop_back();
        }
        while(!leaf->key.empty())
        {
            tmp.push_back(leaf->key.back());
            --(leaf->cnt);
            leaf->key.pop_back();
        }

        tmp.push_back(k);
        sort(tmp.begin(),tmp.end());
        int mid_idx = tmp.size()/2;
        int mid = tmp[mid_idx];

        deque<BTnode*>dqw;
        //deque<int> dqk;

        for (int i=0;i<tmp.size();++i)
        {
            if (tmp[i]<mid) 
            {
                leaf->key.push_back(tmp.at(i));
                leaf->cnt++;
            }
            else if (tmp[i]>mid) 
            {
                newchild->key.push_back(tmp.at(i));
                newchild->cnt++;
            }
        }
        tmp.clear();

        //adjusting pointers
        while(leaf->way.size() != leaf->cnt)
        {
            newchild->way.push_front(leaf->way.back());
            leaf->way.pop_back();
        }
        leaf->way.push_back(NULL);
        
        // midd ko parent
        if (BT==leaf)
        {
            BTnode* newpar = new BTnode(d);
            newpar->key.push_back(mid);
            newpar->way.push_back(leaf);
            newpar->way.push_back(newchild);
            int idx = -1;
            getidx(leaf->key,idx,k);
            if (idx!=-1)
            {
                left = leaf->way.at(idx);
                ri8 = leaf->way.at(idx+1);
            }
            getidx(newchild->key,idx,k);
            if (idx=-1)
            {
                left = newchild->way.at(idx);
                ri8 = newchild->way.at(idx+1);
            }
            if (mid==k)
            {
                left = leaf->way.back();
                ri8 = newchild->way.front();
            }
            BT = newpar; // update root
        }
        else
        {
            Add(BT,left,ri8,d,mid);
            left = leaf;
            ri8 = newchild;
        }
    }
}

void inorder(BTnode*BT)
{
    if (BT==NULL || BT->cnt==0)
        return;
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        inorder(BT->way.at(i));
        cout<<BT->key.at(i)<<" ";
    }
    inorder(BT->way.at(i));
}

int main()
{
    BTnode* BT = NULL,*left = NULL,*ri8 = NULL;
    int k;int d;cin>>d;

    while(true)
    {
        cin>>k;
        if (k==-1) break;
        Add(BT,left,ri8,d,k);
    }

    inorder(BT);
    
    return 0;
}