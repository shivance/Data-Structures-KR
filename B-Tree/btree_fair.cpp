#include <iostream>
#include <deque>
#include <climits>
#include <algorithm>
#include <vector>
using namespace std;


class BTnode
{
public:
    int cnt;
    int d;
    int* key;
    BTnode**way;

    BTnode(int d)
    {
        this->d = d;
        key = new int[d-1];
        way = new BTnode*[d];
        cnt = 0;
        for (int i=0;i<d;++i) way[i]=NULL;
        for (int i=0;i<d-1;++i) key[i]=INT_MAX;
    }
};

deque<BTnode> nodeCache;

BTnode* newBTnode(int d)
{
    nodeCache.push_back(BTnode(d));
    BTnode* node = &nodeCache.back();
    return node;
}

void swap(int &a,int&b)
{
    int t = a;
    a = b;
    b = t;
}

void swapptr(BTnode*&a,BTnode*&b)
{
    BTnode* t = a;
    a = b;
    b = t;
}

void printarr(int arr[],int size)
{
    for (int i=0;i<size;++i) cout<<arr[i]<<" ";
    cout<<"\n";
}   

void getidx(int arr[],int size,int &idx,int k)
{
    for (int i=0;i<size;++i){
        if (arr[i]==k){
            idx = i;
            break;
        }
    }
}

void inorder(BTnode*BT)
{
    if (BT==NULL)
        return;
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        inorder(BT->way[i]);
        if(BT->key[i]!=INT_MAX) 
            cout<<BT->key[i]<<" ";
    }
    inorder(BT->way[i]);
}

void sortL(BTnode*&leaf)
{
    int p = leaf->cnt-1;
    while(leaf->key[p]<leaf->key[p-1] && p>=1)
    {
        swap(leaf->key[p],leaf->key[p-1]);
        swapptr(leaf->way[p+1],leaf->way[p]);
        --p;
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
            break;
    }


    if (BT->way[i]==NULL)
        return BT;
    else 
        return search(BT->way[i],k);
}


BTnode* parent(BTnode* BT,BTnode* node)
{
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        if (BT->key[i]>=node->key[0]) break;
    }
    if (BT->way[i] == node) return BT;
    else return parent(BT->way[i],node);
}


void Add(BTnode* & BT,BTnode* &leaf,BTnode*&ri8,int d,int k,bool &o)
{
    
    //no overflow
    if (leaf->cnt < d-1)
    {
        leaf->key[leaf->cnt] = k;
        ++(leaf->cnt);
        sortL(leaf);                
        int idx;    
        getidx(leaf->key,leaf->cnt,idx,k);
        ri8 = leaf->way[idx+1];
    }

    else 
    {
        int cnt_l = leaf->cnt;
        BTnode* newchild = new BTnode(d);
        vector<int>tmp;
        for (int i=0;i<leaf->cnt;++i) 
        {
            tmp.push_back(leaf->key[i]);
            leaf->key[i]= INT_MAX;
        }
        
        leaf->cnt = 0;
        tmp.push_back(k);
        
        sort(tmp.begin(),tmp.end());
        int mid_idx = tmp.size()/2;
        int mid = tmp[mid_idx];

        for (int i=0;i<tmp.size();++i)
        {
            if (tmp[i]<mid) 
            {
                leaf->key[leaf->cnt] = tmp[i];
                leaf->cnt++;
            }
            else if (tmp[i]>mid) 
            {
                newchild->key[newchild->cnt] = tmp[i];
                newchild->cnt++;
            }
        }
        sortL(newchild);
        sortL(leaf);
        
        //adjusting pointers
        int j;
        if (mid == k) 
        {
            j= 1;
            o = true; // represents mid == key in parent
        }
        else j= 0;

        for (int i=mid_idx+1;i<=cnt_l;++i,++j)
        {
            newchild->way[j] = leaf->way[i];
            leaf->way[i]=NULL;
        }

        
        //middle to parent
        if (BT==leaf)
        {
            BTnode* newpar = newBTnode(d); 
            newpar->key[0] = mid;
            newpar->cnt++;
            newpar->way[0] = leaf;
            newpar->way[1] = newchild;
            BT = newpar; // update root when overflow in root
            ri8 = newchild;
        }
        else
        {
            BTnode* par = parent(BT,leaf);int idxn;
            
            int c = par->cnt;

            o = false;
            Add(BT,par,ri8,d,mid,o);
            
            if (c<d-1){
                getidx(par->key,par->cnt,idxn,mid);
                par->way[idxn+1] = newchild;
            }
            else
            {
                if (o) 
                    ri8->way[0] = newchild;

                else{
                    getidx(ri8->key,ri8->cnt,idxn,mid);
                    ri8->way[idxn+1] = newchild;
                }
            }
            return;
        }
    }
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    BTnode* BT = NULL,*ri8 = NULL,*leaf = NULL;
    int k,d,n;bool o;
    cin>>d;
    cin>>n;
    cin>>k;
    BT = newBTnode(d);
    // using a deque cache for performance improvement
    // didn't use 'new BTnode(d)'
    BT->key[BT->cnt] = k;
    BT->cnt++;

    for (int i=1;i<n;++i)
    {
        cin>>k;
        leaf = search(BT,k);
        ri8 = NULL;
        o = false;
        Add(BT,leaf,ri8,d,k,o);
    }
    inorder(BT);
    
    return 0;
}
