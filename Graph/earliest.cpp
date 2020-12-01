#include <iostream>
#include <vector>
#include <list>
#include <climits>
#include <cmath>

using namespace std;

class lnode{
    public:
    int v;
    float wt;
    lnode(int v,float wt){
        this->wt = wt;
        this->v = v;
    }
};

template<typename D>
void printvec(vector<D>v){
    for (int i=0;i<v.size();++i){
        cout<<v[i]<<" ";
    }
    cout<<"\n";
}


void addEdge(vector<list<lnode*> >&G, int u, int v,float wt)
{
    G[u].push_back(new lnode(v,wt));
}


float early(vector<list<lnode*> >&RG,int v){
    if(RG[v].size()==0)
        return 0;

    float k = -10.0;
    list<lnode*>::iterator it;
    for (it = RG[v].begin();it!=RG[v].end();++it){
        k = fmax(k,(*it)->wt+early(RG,(*it)->v));
    }
    //cout<<v<<" max = "<<k<<" returned\n";
    return k;
}




int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<list<lnode*> > RG(n + 1, list<lnode*>());
    int u, v ;
    float wt;

    // n vertices
    //m number of u and v --> m edge

    //vertex weighted graph
    float dstn_wt;
    for (int i = 1; i <= n; ++i)
    {
        cin >> wt;
        if (i==n) dstn_wt = wt;
        // i/o all child 
        while(true){
            cin>>u;
            if (u==-1) break;
            // dag -> u = i, v = u; rdag -> u = u, v = i
            //storing wt of outgoing edge of dag
            addEdge(RG, u, i, wt);
        }
        
    }
    //destination is 7
    
    cout<<early(RG,n)+dstn_wt<<"\n";
    // construct only reverse DAG

    
    return 0;
}

/*
7
3.1 3 5 -1
2.0 5 -1
4.6 4 6 -1
1.8 7 -1
3.0 6 -1
4.0 7 -1
3.7 -1
*/