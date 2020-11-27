// undirected

#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;


void addEdge(vector<list<int> >&G, int u, int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}

void ExploreD(vector<list<int> >&G, vector<bool> &visited, int v)
{
    visited[v] = true;
    cout << v << " ";
    
    list<int>::iterator it;
    for (it=G[v].begin();it!=G[v].end();++it)
    {
        if (!visited[*it])
            ExploreD(G, visited, *it);
    }
}

void DFS(vector<list<int> > &G, int v, int V)
{
    vector<bool> visited(V, false);

    ExploreD(G, visited, v);
}

void ExploreB(vector<list<int> >&G,vector<bool>&visited,int v)
{
    queue<int>q;
    
    list<int>::iterator it;

    int k;
    q.push(v);
    visited[v]=true;

    while(!q.empty())
    {
        k = q.front();
        cout<<k<<" ";
        
        q.pop();

        for (it = G[k].begin();it!=G[k].end();++it){
            if (!visited[*it]){
                visited[*it] = true;
                q.push(*it);
            }
        }
    }
}

void BFS(vector<list<int> >&G, int v, int V)
{
    vector<bool> visited(V, false);

    ExploreB(G, visited, v);
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<list<int> > G(n + 1, list<int>());
    int u, v;
    // n vertices
    //m number of u and v --> m edge
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        addEdge(G, u, v);
    }
    DFS(G,1,n+1);
    cout<<"\n";
    BFS(G,1,n+1);

    return 0;
}