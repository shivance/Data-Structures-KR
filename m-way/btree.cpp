#include <iostream>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

class BTnode
{
public:
    int cnt;
    int cnt_w;
    int d;
    int* key;
    BTnode**way;

    BTnode(int d)
    {
        this->d = d;
        key = new int[d-1];
        way = new BTnode*[d];
        cnt = 0;
        cnt_w = 0;
        for (int i=0;i<d;++i) way[i]=NULL;
        for (int i=0;i<d-1;++i) key[i]=INT_MIN;
    }
};

void getidx(int arr[],int size,int &idx,int k)
{
    for (int i=0;i<size;++i)
    {
        if (arr[i]==k)
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
            if (BT->way[i]==NULL) 
            {
                return BT;
            }
            else 
            {
                if (BT->cnt<(BT->d - 1)) return BT;
                return search(BT->way[i],k);
            }
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

void printarr(int arr[],int size)
{
    for (int i=0;i<size;++i) cout<<arr[i]<<" ";
 
}

void Add(BTnode* & BT,BTnode* &ri8,int d,int k,bool o)
{
    o =false;
    if (BT==NULL) 
    {
        BT = new BTnode(d);
        BT->key[0] = k;
        BT->cnt++;
        return;
    }

    BTnode* leaf = search(BT,k);

    //no overflow
    if (BT->cnt < d-1)
    {
        leaf->key[leaf->cnt] = k;
        ++(leaf->cnt);
        sort(leaf->key,leaf->key+leaf->cnt);
        int idx = -1;
        getidx(leaf->key,leaf->cnt,idx,k);
        ri8 = leaf->way[idx+1];
        cout<<"added k = "<<k<<"\n";
        //root remains same
        return;
    }

    else //overflow
    {
        int cnt_l = leaf->cnt;
        BTnode* newchild = new BTnode(d);
        deque<int>tmp;
        for (int i=0;i<leaf->cnt;++i) 
        {
            tmp.push_back(leaf->key[i]);
            leaf->key[i]= INT_MIN;
        }
        
        leaf->cnt = 0;
        tmp.push_back(k);
        cout<<"added k = "<<k<<"\n";
        sort(tmp.begin(),tmp.end());
        int mid_idx = tmp.size()/2;
        int mid = tmp[mid_idx];

        deque<BTnode*>dqw;
        //deque<int> dqk;

        for (int i=0;i<tmp.size();++i)
        {
            if (tmp[i]<mid) 
            {
                leaf->key[leaf->cnt] = (tmp.at(i));
                leaf->cnt++;
            }
            else if (tmp[i]>mid) 
            {
                newchild->key[newchild->cnt] = (tmp.at(i));
                newchild->cnt++;
            }
        }
        sort(newchild->key,newchild->key+newchild->cnt);
        sort(leaf->key,leaf->key+leaf->cnt);
        cout<<"Node splitted into : ";
        cout<<"Left : ";printarr(leaf->key,leaf->cnt);cout<<" right : ";printarr(newchild->key,newchild->cnt);
        tmp.clear();
        cout<<"\n";

        //adjusting pointers
        int j = 0;
        for (int i=mid+1;i<=cnt_l;++i,++j)
        {
            newchild->way[j] = leaf->way[i];
            leaf->way[i]=NULL;
        }
        
        // mid ko parent
        if (BT==leaf)
        {
            BTnode* newpar = new BTnode(d);
            newpar->key[0] = mid;
            newpar->cnt++;
            newpar->way[0] = leaf;
            newpar->way[1] = newchild;
            if (mid==k) // no ri8 updation
                o= true;
            else{
                int idx = -1;
                getidx(leaf->key,leaf->cnt,idx,k);
                
                if (idx!=-1)
                     ri8 = leaf->way[idx+1];

                else
                {
                     getidx(newchild->key,newchild->cnt,idx,k);

                     if (idx!=-1)
                          ri8 = newchild->way[idx+1];
                }
            }
            cout<<"parent created ";printarr(newpar->key,newpar->cnt);cout<<"\n";
            BT = newpar; // update root
            cout<<"root updated -- added "<<mid<<" to root\n";
        }
        else
        {
            Add(BT,ri8,d,mid,o);
            cout<<"added mid = "<<mid<<"\n";
            if(!o)
                ri8 = newchild;
                
            return;
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
        //if(BT->way[i]!=NULL)
        inorder(BT->way[i]);
        if(BT->key[i]!=INT_MIN) 
            cout<<BT->key[i]<<" ";
        else break;
    }
    //if(BT->way[i]!=NULL)
    inorder(BT->way[i]);
}

int main()
{
    BTnode* BT = NULL,*ri8 = NULL;
    int k;int d;cin>>d;bool o = false;

    while(true)
    {
        o = false;
        cin>>k;
        if (k==-1) break;
        cout<<"INSERTING : "<<k<<"\n";
        Add(BT,ri8,d,k,o);
        cout<<"\n";
    }

    inorder(BT);
    
    return 0;
}
