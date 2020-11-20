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

BTnode newBTnode(int d)
{
    nodeCache.push_back(BTnode(d));
    return nodeCache.back();
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
        //if(BT->way[i]!=NULL)
        inorder(BT->way[i]);
        if(BT->key[i]!=INT_MAX) 
            cout<<BT->key[i]<<" ";
        //else break;
    }
    //if(BT->way[i]!=NULL)
    inorder(BT->way[i]);
}

void nodeSplit(BSTnode*&leaf,BSTnode*&newnode,int k,int& median,int &o)
{
    o = false;
    vector<int>temp;
    for (int i=0;i<cnt_l;++i) 
        temp.push_back(leaf->key[i]);
    temp.push_back(k);

    sort(temp.begin(),temp.end());


    int mid = temp[temp.size()/2];
    median = mid;

    if (mid==k) o = true;

    if (d&1) start = d/2+1;
    else start = d/2;

    //shift pointers easily
    int i,j=0;   
    for (int i=start;i<d-1;++i,++j){
        newchild->way[j] = leaf->way[i];
        leaf->way[i]=NULL;
    }

    for (int i=0;i<leaf->cnt;++i) leaf->key[i]=INT_MAX;

    i=0;j=0;
    for (i,j;i<temp.size();++i)
    {
        if (i<=temp.size()/2)
            leaf->key[i] = temp[i];
        else{
            newchild->key[j] = temp[i];++j;
        }
    }
}

BTnode* search(BTnode*BT,int k)
{
    //exist = false;
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        if(BT->key[i]==k)
        {
            //exist = true;
            return BT;
        }
        else if (BT->key[i]>k)
            break;
    }


    if (BT->way[i]==NULL)
        return BT;
    else 
        return search(BT->way[i],k);

    return NULL;
}


BTnode* parentU(BTnode* BT,BTnode* node)
{
    // if (BT==node) 
    int i;
    for (i=0;i<BT->cnt;++i)
    {
        if (BT->key[i]>=node->key[0]) break;
    }
    if (BT->way[i] == node) return BT;
    else return parent(BT->way[i],node);
}

BTnode* parent(BTnode* BT,BTnode* node)
{
    if (BT == node) return NULL;
    return parentU(BT,node);
}


void Add(BTnode* & BT,BTnode* &leaf,BTnode*&ri8,int d,int k,bool &o)
{
    cout<<"Inserting to  : ";printarr(leaf->key,leaf->cnt);cout<<"\n";
    //no overflow
    if (leaf->cnt < d-1)
    {
        leaf->key[leaf->cnt] = k;
        ++(leaf->cnt);
        //sort(leaf->key,leaf->key+leaf->cnt);
        sortL(leaf);        

        cout<<"leaf now is : ";
        printarr(leaf->key,leaf->cnt);
        
        int idx = -1;

        getidx(leaf->key,leaf->cnt,idx,k);
        cout<<"idx = "<<idx<<"\n";
        ri8 = leaf->way[idx+1];
        //printarr(ri8->key,ri8->cnt);
        if (ri8) cout<<"Not null\n";
        else cout<<"null\n";
        cout<<"added no overflow k = "<<k<<" to ";printarr(leaf->key,leaf->cnt);cout<<"\n";
        return;
    }

    else //overflow
    {
        int cnt_l = leaf->cnt;
        BTnode* newchild = new BTnode(d);
        
        bool o; int median;
        nodeSplit(leaf,newchild,key,o,median);

        cout<<"added overflow k = "<<k<<"\n";
        cout<<"Node splitted into : ";
        cout<<"Left : ";printarr(leaf->key,leaf->cnt);cout<<" right : ";printarr(newchild->key,newchild->cnt);cout<<"\n";
        // newly splitted right node
        
        
        //middle to parent
        if (BT==leaf)
        {
            BTnode* newpar = new BTnode(d);
            newpar->key[0] = median;
            newpar->cnt++;
            newpar->way[0] = leaf;
            newpar->way[1] = newchild;
            
            BT = newpar; // update root
            
            
            cout<<"parent created ";printarr(newpar->key,newpar->cnt);cout<<"\n";
            cout<<"root updated -- added "<<mid<<" to root\n";
            cout<<"key of root : ";printarr(BT->key,BT->cnt);
            ri8 = newchild;
            cout<<"key of newly splitted node : ";printarr(ri8->key,ri8->cnt);cout<<"\n";
            cout<<"INORDER OF RI8 is : ";printarr(ri8->key,ri8->cnt);
        }
        else
        {
            BTnode* par = parent(BT,leaf);
            
            cout<<"called nested else \n";
            int c = par->cnt;
            //ri8 = newchild;
            //cout<<"key of newly splitted node : ";printarr(ri8->key,ri8->cnt);cout<<"\n";
            //cout<<"INORDER OF RI8 is : ";printarr(ri8->key,ri8->cnt);
            o = false;
            Add(BT,par,ri8,d,mid,o);
            cout<<"o is "<<o<<"\n";
            int idxn;
            if (c<d-1){
                getidx(par->key,par->cnt,idxn,mid);
                cout<<"added mid = "<<mid<<"\n";
                par->way[idxn+1] = newchild;
            }
            else
            {
                cout<<"parent overflow \n";
                if (o) 
                {
                    cout<<"parent INORDER is "; inorder(ri8);cout<<"\n";
                    ri8->way[0] = newchild;
                }
                else{
                    getidx(ri8->key,ri8->cnt,idxn,mid);
                    cout<<"added mid = "<<mid<<"\n";
                    ri8->way[idxn+1] = newchild;
                }
            }
            return;
        }
    }
}


int main()
{
    BTnode* BT = NULL,*ri8 = NULL,*leaf = NULL;
    int k;int d;cin>>d;bool o = false;
    cin>>n;
    cin>>k;
    BT = new BTnode(d);
    BT->key[BT->cnt] = k;
    BT->cnt++;

    for (int i=1;i<n;++i)
    {
        cin>>k;
        if (k==-1) break;

        leaf = search(BT,k);
        ri8 = NULL;
        o = false;
        
        cout<<"INSERTING : "<<k<<"\n";
        Add(BT,leaf,ri8,d,k,o);
        cout<<"Current inorder = ";inorder(BT);
        cout<<"\n";
    }
    
    return 0;
}
