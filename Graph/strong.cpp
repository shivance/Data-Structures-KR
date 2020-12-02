// UNWEIGHTED DIRECTED GRAPH </> ADJACENCY MATRIX
// STRONGLY connected components


#include <iostream>
#include <vector>
#include <deque>
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

void makeGraph(vector<vector<int> >&mat){
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

void PostorderNumb(vector<vector<int> >&G,vector<GraphNode*> &node){
    int num = 1;

    for (int i =1;i<node.size();++i){
        if (!node[i]->visited)
            DFSUtil(G,node,i,num);
    }

    sort(node.begin()+1,node.end(),sortfunc);

    for (int i=1;i<node.size();++i){
        node[i]->visited = false;
    }
}

void finalDFSUtil(vector<vector<int> >&RG,vector<GraphNode*> &node,int v){
    if(node[v]->visited) return;

    node[v]->visited = true;
    cout<<v<<" ";

    for (int i=1;i<node.size();++i){
        if(RG[v][i]==1 && !(node[i]->visited)){            
            finalDFSUtil(RG,node,i);
        }
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

    for (int i=1;i<node.size();++i){
        node[i] = newGnode(i);
    }
    
    makeGraph(G); 
    //printGraph(G);
    PostorderNumb(G,node);

    vector<vector<int> > RG = reverseG(G);
    
    cout<<"Strongly connected components : \n";
    for (int i=1;i<node.size();++i){
        if (!node[node[i]->order]->visited){
            finalDFSUtil(RG,node,node[i]->order);
            cout<<"\n";
        }
    }

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