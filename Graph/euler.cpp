// UNDIRECTED UNWEIGHTED GRAPH
// EULER's Path problem -> a figure that we can draw on paper without lifting 
// our pen


#include <iostream>
#include <vector>

using namespace std;

void addEdge(vector<vector<int> >&G,int u,int v){
    G[u][v] = 1;
    G[v][u] = 1;
}

void printvec(vector<int>&v,int strt){
    for (int i=strt;i<v.size();++i){
        cout<<v[i]<<" ";
    }
    cout<<"\n";
}

void printGraph(vector<vector<int> >G){
    for (int i=1;i<G.size();++i)
        printvec(G[i],1);   
}

void makeGraph(vector<vector<int> >&G){
    int u,v;
    while(true){
        cin>>u;
        if(u==-1) return;
        cin>>v;
        addEdge(G,u,v);
    }
}

void update_degree(vector<vector<int> >&G){
    int cnt = 0;
    for (int i=1;i<G.size();++i){
        cnt = 0;
        for (int j=1;j<G[i].size();++j){
            if (G[i][j]) ++cnt;
        }
        G[i][0] = cnt;
    }
}

void dfs_util(vector<vector<int> >&G,vector<int>&list,vector<bool>&visited,int v,int par){
    if (G[v][0]<=0) return;

    list.push_back(v);
    //erasing edge
    if (G[par][v]){
        G[par][v] = 0;
        G[par][0]--;
    }
    if (G[v][par]){
        G[v][par] = 0;
        G[v][0]--;
    }

    for (int i=1;i<G[v].size();++i){
        if (G[v][i] && G[v][0]){
            return dfs_util(G,list,visited,i,v);
        }
    }
}

void erasive_dfs(vector<vector<int> >&G,vector<int>&list,int strt){
    vector<bool>visited(G.size(),false);
    dfs_util(G,list,visited,strt,strt);
}


int main()
{
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

    int n;//no of vertex
    cin>>n;

    vector<vector<int> > G(n+1,vector<int>(n+1,0));
    makeGraph(G);
    update_degree(G);
    vector<int> list;

    // let's find a vertex with odd degree if exists
    int strt = 1;
    for (int i=1;i<G.size();++i){
        if (G[i][0]&1){   
            strt = i;break;
        }
    }


    //we'll perform erasive dfs starting from 'strt' and update the list
    erasive_dfs(G,list,strt);
    
    
    // now we have initial list
    // in next step we will loop our this list until we find an element that
    // has degree > 0 if found will perform erasive dfs on it 

    
    vector<int>tmp;
    bool o;
    while(true){
        o = false;
        int i;
        //loop over list to find the element that has deg>0
        for (i=0;i<list.size();++i){
            if (G[list[i]][0]){
                strt = list[i];
                o = true;
                break;
            }
        }

        if(!o) break;
        
        
        // vertex with deg>0 found -> call erasive dfs on it
        
        erasive_dfs(G,tmp,list[i]);
        vector<int>::iterator it = list.begin()+i;
        list.erase(it);

        //inserting in list
        for (int j=0;j<tmp.size()-1;++j,++i){
            list.insert(list.begin()+i,tmp[j]);
        }
            
        // clear tmp
        tmp.clear();
    }
    cout<<"Euler path : ";
    printvec(list,0);        
    

    return 0;
}

/*
12
1 3
1 4
2 3
2 8
3 4
3 6
3 7
3 9
4 5
4 7
4 10
4 11
5 10
6 9
7 9
7 10
8 9
9 10
9 12
10 11
10 12
-1
*/