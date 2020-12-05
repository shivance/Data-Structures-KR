#include <bits/stdc++.h>

using namespace std;

class lnode{
    public:
    int wt, v;
    lnode(int v,int wt){
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


void addEdge(vector<list<lnode*> >&G, int u, int v,int wt)
{
    G[u].push_back(new lnode(v,wt));
}


void updateGraph(vector<list<lnode*> >G,vector<int>&dist,vector<int>&prev_vertex,vector<bool>&visited,int src){
    //vector<int>bfs = BFS(G, src,dist.size());
    
    queue<int>q;
    
    list<lnode*>::iterator it;

    int k;
    q.push(src);
    visited[src]=true;

    while(!q.empty())
    {
        k = q.front();
        //bfs.push_back(k);
        for (it = G[k].begin();it!=G[k].end();++it)
        {
            if (dist[(*it)->v]>= dist[k]+(*it)->wt){
                dist[(*it)->v] = dist[k]+(*it)->wt;
                prev_vertex[(*it)->v] = k;
            }
        }
        q.pop();

        for (it = G[k].begin();it!=G[k].end();++it){
            if (!visited[(*it)->v]){
                visited[(*it)->v] = true;
                q.push((*it)->v);
            }
        }
    }        
}

void Path(vector<int>dist,vector<int>prev_vertex,int src,int dstn)
{
    cout<<"Total cost in path : "<<dist[dstn]<<endl;
    int tmp = prev_vertex[dstn];

    vector<int>v;

    while(tmp!=src){
        v.push_back(tmp);
        tmp = prev_vertex[tmp];        
    }

    cout<<"Path is : ";
    cout<<src<<"->";
    for (int i=v.size()-1;i>=0;--i) cout<<v[i]<<"->";
    cout<<dstn<<"\n";
    return;
}


int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<list<lnode*> > G(n + 1, list<lnode*>());
    
    int u, v , wt;

    // n vertices
    //m number of u and v --> m edge
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v>> wt;
        addEdge(G, u, v, wt);
    }

    

    int src,dstn;
    while(true)
    {
        cin>>src;
        if (src==-1) break;
        cin>>dstn;

        vector<bool>visited(n+1,false);
        vector<int>dist(n+1,INT_MAX);
        vector<int>prev_vertex(n+1,0);

        prev_vertex[src] = src;
        dist[src] = 0;
        
        updateGraph(G,dist,prev_vertex,visited,src);

    
        if (dist[dstn]==INT_MAX){
           cout<<"No path \n";
        }
        else Path(dist,prev_vertex,src,dstn);
        cout<<flush;
        this_thread::sleep_for(chrono::seconds(1));
    }
    
    
    return 0;
}


/*
7 12
1 2 3
1 4 1
2 4 3
2 5 2
4 3 2
4 5 4
4 6 3
4 7 6
3 1 5
3 6 4
5 7 4
7 6 2
*/