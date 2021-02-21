#include <iostream>
#include <vector>
#include <list>
#include <climits>

using namespace std;

class lnode{
    public:
    int v;
    int wt;
    lnode(int v,int wt){
        this->v = v;
        this->wt = wt;
    }
};


void addEdge(vector<list<lnode*> > &G, int u, int v,int wt)
{
    G[u].push_back(new lnode(v,wt));
    G[v].push_back(new lnode(u,wt));
    cout<<G[u].back()->v<<" "<<G[v].back()->v<<"\n\n";

}

void printGraph(vector<list<lnode*> > &G)
{
    for (int v = 0; v < G.size(); ++v)
    {
        cout << v<<"\n";
        for (list<lnode*>::iterator x = G[v].begin();x != G[v].end();++x)
            cout<<(*x)->v<<" ";
        cout << "\n";
    }
}

int ExploreMst(vector<list<lnode*> >&G,vector<bool>&visited,int v){
    //if (visited[v]) return 0;

    visited[v] = true;
    int k = INT_MAX;

    list<lnode*>::iterator it;
    
    for (it= G[v].begin();it!=G[v].end();++it)
    {
        if (!visited[(*it)->v])
            k = min(k,ExploreMst(G,visited,(*it)->v));
    }

    return k;
}

int mst(vector<list<lnode*> >&G,int v,int V){
    vector<bool> visited(V, false);
    return ExploreMst(G, visited, v);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n;
    vector<list<lnode*> > G(n + 1,list<lnode*> ());
    int u, v , wt;
    // n vertices
    //m number of u and v --> m edge
    while(1)
    {
        cin >> u ;
        if (u==-1) break;
        cin>> v>>wt;
        addEdge(G, u, v, wt);
        printGraph(G);
    }

    cout<<"here\n";
    int k = INT_MAX;
    for (int i=1;i<8;++i){
        k = min(mst(G,i,8),k);
    }
    
    cout<<k<<"\n";

    return 0;
}
/*
6
1 2 2
1 3 4
1 4 1
2 4 3
2 5 10
3 4 2
3 6 5
4 5 7
4 6 8
4 7 4
5 7 6
6 7 1
-1
*/
