#include <iostream>
#include <deque>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>
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

    //return NULL;
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
        vector<int>tmp;
        for (int i=0;i<leaf->cnt;++i) 
        {   
            tmp.push_back(leaf->key[i]);
            leaf->key[i]= INT_MAX;
        }
        
        leaf->cnt = 0;
        tmp.push_back(k);
        cout<<"added overflow k = "<<k<<"\n";
        sort(tmp.begin(),tmp.end());
        int mid_idx = tmp.size()/2  ;
        int mid = tmp[mid_idx];

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
        sortL(newchild);
        sortL(leaf);
        cout<<"Node splitted into : ";
        cout<<"Left : ";printarr(leaf->key,leaf->cnt);cout<<" right : ";printarr(newchild->key,newchild->cnt);cout<<"\n";
        // newly splitted right node
        
        //adjusting pointers
        int j;
        if (mid == k) 
        {
            cout<<"mid == k \n";
            o = true; // represents mid == key in parent
        }
        else j= 0;

        for (int i=mid_idx+1;i<=cnt_l;++i,++j)
        {
            newchild->way[j] = leaf->way[i];
            if (leaf->way[i]!=NULL){
                cout<<"newchild->way["<<j<<"] ";
                printarr(leaf->way[i]->key,leaf->way[i]->cnt);cout<<"\n";
            }
            leaf->way[i]=NULL;
        }

        
        //middle to parent
        if (BT==leaf)

        {
            BTnode* newpar = new BTnode(d);
            newpar->key[0] = mid;
            newpar->cnt++;
            newpar->way[0] = leaf;
            newpar->way[1] = newchild;
            
            BT = newpar; // update root
            
            
            cout<<"parent created ";printarr(newpar->key,newpar->cnt);cout<<"\n";
            cout<<"root updated -- added "<<mid<<" to root\n";
            cout<<"data of root : ";printarr(BT->key,BT->cnt);
            ri8 = newchild;
            cout<<"data of newly splitted node : ";printarr(ri8->key,ri8->cnt);cout<<"\n";
            cout<<"INORDER OF RI8 is : ";printarr(ri8->key,ri8->cnt);
        }
        else
        {
            BTnode* par = parent(BT,leaf);
            
            cout<<"called nested else \n";
            int c = par->cnt;
            //ri8 = newchild;
            //cout<<"data of newly splitted node : ";printarr(ri8->key,ri8->cnt);cout<<"\n";
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


void AddLeaf(BTnode* & BT,BTnode* &leaf,BTnode*&ri8,int d,int k,bool &o)
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
        vector<int>tmp;
        for (int i=0;i<leaf->cnt;++i) 
        {   
            tmp.push_back(leaf->key[i]);
            leaf->key[i]= INT_MAX;
        }
        
        leaf->cnt = 0;
        tmp.push_back(k);
        cout<<"added overflow k = "<<k<<"\n";
        sort(tmp.begin(),tmp.end());
        int mid_idx = tmp.size()/2  ;
        int mid = tmp[mid_idx];

        for (int i=0;i<tmp.size();++i)
        {
            if (tmp[i]<mid) 
            {
                leaf->key[leaf->cnt] = (tmp.at(i));
                leaf->cnt++;
            }
            else if (tmp[i]>=mid) 
            {
                newchild->key[newchild->cnt] = (tmp.at(i));
                newchild->cnt++;
            }
        }
        sortL(newchild);
        sortL(leaf);
        cout<<"Node splitted into : ";
        cout<<"Left : ";printarr(leaf->key,leaf->cnt);cout<<" right : ";printarr(newchild->key,newchild->cnt);cout<<"\n";
        // newly splitted right node
        
        //adjusting pointers
        int j;
        if (mid == k) 
        {
            j= 1;
            cout<<"mid == k \n";
            o = true; // represents mid == key in parent
        }
        else j= 0;

        for (int i=mid_idx;i<=cnt_l;++i,++j)
        {
            newchild->way[j] = leaf->way[i];
            if (leaf->way[i]!=NULL){
                cout<<"newchild->way["<<j<<"] ";
                printarr(leaf->way[i]->key,leaf->way[i]->cnt);cout<<"\n";
            }
            leaf->way[i]=NULL;
        }

        
        //middle to parent
        if (BT==leaf)
        {
            BTnode* newpar = new BTnode(d);
            newpar->key[0] = mid;
            newpar->cnt++;
            newpar->way[0] = leaf;
            newpar->way[1] = newchild;
            
            BT = newpar; // update root
            
            
            cout<<"parent created ";printarr(newpar->key,newpar->cnt);cout<<"\n";
            cout<<"root updated -- added "<<mid<<" to root\n";
            cout<<"data of root : ";printarr(BT->key,BT->cnt);
            ri8 = newchild;
            cout<<"data of newly splitted node : ";printarr(ri8->key,ri8->cnt);cout<<"\n";
            cout<<"INORDER OF RI8 is : ";printarr(ri8->key,ri8->cnt);
        }
        else
        {
            BTnode* par = parent(BT,leaf);
            
            cout<<"called nested else \n";
            int c = par->cnt;
            //ri8 = newchild;
            //cout<<"data of newly splitted node : ";printarr(ri8->key,ri8->cnt);cout<<"\n";
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
                cout<<"data of ri8 : ";printarr(ri8->key,ri8->cnt);
                if (o) 
                {
                    cout<<"parent INORDER is "; inorder(ri8);cout<<"\n";
                    ri8->way[0] = newchild;
                }
                else{
                    idxn = -1;
                    getidx(leaf->key,leaf->cnt,idxn,mid);
                    cout<<"added mid = "<<mid<<"\n";
                    if (idxn!=-1)
                    leaf->way[idxn+1] = newchild;
                    
                    getidx(ri8->key,ri8->cnt,idxn,mid);
                    cout<<"added mid = "<<mid<<"\n";
                    ri8->way[idxn+1] = newchild;
                }
            }
            return;
        }
    }
}
    
void level(BTnode*&BT)
{
    BTnode* tmp;
    queue<BTnode*> q;

    q.push(BT);
    while(!q.empty())
    {
        tmp = q.front();
        printarr(tmp->key,tmp->cnt);
        q.pop();

        int i;
        for (i=0;i<=tmp->cnt;++i)
        {
            if (tmp->way[i] == NULL) continue;
            q.push(tmp->way[i]);
        }
        
    }
}



int main()
{
    BTnode* BT = NULL,*ri8 = NULL,*leaf = NULL;int n;
    int k;int d;cin>>d;bool o = false;
    cin>>n;
    cin>>k;
    BT = newBTnode(d);
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
        AddLeaf(BT,leaf,ri8,d,k,o);
        cout<<"Current inorder = ";inorder(BT);
        cout<<"\n";
        
    }

    level(BT);
    
    return 0;
}
