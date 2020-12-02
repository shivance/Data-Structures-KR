// UNWEIGHTED DIRECTED GRAPH </> ADJACENCY MATRIX

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

class GraphNode{
    public:
    bool visited;
    int pstn;
    int order;
    GraphNode(int order){
        this->order = order;
        this->visited = false;
        this->pstn = 0;
    }
};


deque<GraphNode> nodeCache;

GraphNode* newGnode(int d)
{
    nodeCache.push_back(GraphNode(d));
    GraphNode* node = &nodeCache.back();
    return node;
}

vector<GraphNode*> vec(int s){
    vector<GraphNode*> node(s+1,NULL);
    return node;
}

void addEdge(vector<vector<int> >&G,int u,int v){
    G[u][v] = 1;
}

void printGraph(vector<vector<int> >G){
    for (int i=1;i<G.size();++i){
        for (int j=1;j<G.size();++j){
            cout<<G[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void makeGraph(vector<vector<int> >&mat,vector<GraphNode*> &node){
    int u,v;
    while(true){
        cin>>u;
        if(u==-1) return;
        cin>>v;
        addEdge(mat,u,v);
    }
}

bool sortfunc(GraphNode* &a,GraphNode* &b){
    return (a->pstn >= b->pstn);
}

void DFSUtil(vector<vector<int> >&G,vector<GraphNode*> node,int v,int &num){
    node[v]->visited = true;
    for (int i=1;i<G.size();++i){
        if(G[v][i] && !node[i]->visited)
            DFSUtil(G,node,i,num);
    }
    node[v]->pstn = num;
    ++num;
}

void DFS(vector<vector<int> >&G,vector<GraphNode*> &node){
    int num = 1;
    
    DFSUtil(G,node,2,num);
    DFSUtil(G,node,8,num);
    DFSUtil(G,node,7,num);
    
    sort(node.begin()+1,node.end(),sortfunc);

    
}

void finalDFSUtil(vector<vector<int> >&RG,vector<GraphNode*> &node,int v){
    node[v]->visited = true;
    cout<<node[v]->order<<" "<<node[v]->pstn<<"\n";
    for (int i=1;i<RG.size();++i){
        if(RG[v][i] && !node[i]->visited)
            finalDFSUtil(RG,node,i);
    }
}

vector<vector<int> > reverseG(vector<vector<int> >G){
    vector<vector<int> >RG(G.size(),vector<int>(G.size(),0));

    for (int i=1;i<G.size();++i){
        for (int j=1;j<G[i].size();++j){
            if (G[i][j]) RG[j][i] = G[i][j];
        }
    }

    return RG;
}


int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    cout.tie(0);

    int n;//no of vertex
    cin>>n;
    
    vector<vector<int> > G(n+1,vector<int>(n+1,0));
    vector<GraphNode*> node(n+1,NULL);

    // vector of nodes (extended visited array)
    for (int i=1;i<node.size();++i){
        node[i] = newGnode(i);
    }
    
    makeGraph(G,node); 
    //printGraph(G);
    DFS(G,node);

    for (int i=1;i<node.size();++i){
        node[i]->visited = false;
    }

    vector<vector<int> > RG = reverseG(G);

    printGraph(RG);

    /*for (int i=1;i<node.size();++i){
        if (!node[i]->visited){
            finalDFSUtil(RG,node,i);
            cout<<"\n\n";
        }
    }*/

    
    
    return 0;
}

/*
10
1 2 
1 4 
2 3 
2 6 
3 1
3 4 
3 5 
4 5 
6 3 
7 6 
7 8 
8 6 
8 10
10 9
9 8 
-1
*/