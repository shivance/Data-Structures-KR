#include <bits/stdc++.h>

using namespace std;

class ele{
public:
    vector <long> v;
    ele(int n){
        v.resize(n+1,INT_MAX);
    }
};

void printGraph(vector<vector<ele*> >&G,int k){
    for (int i=1;i<G.size();++i){
        for (int j=1;j<G.size();++j){
        	if (G[i][j]->v[k]==INT_MAX) cout<<"x ";
            else cout<<G[i][j]->v[k]<<" ";
        }
        cout<<"\n";
    }
}

void ioGraph(vector<vector<ele*> >&G,int m){
    int u,v;
    long wt;

    for (int i=0;i<m;++i){
        cin>>u>>v>>wt;
        G[u][v]->v[0] = wt;
    }
    
    // zero all diagonal elements => no self edge
    for (int i=1;i<G.size();++i){
    	G[i][i]->v[0] = 0;
    }
}

void floyd(vector<vector<ele*> >&G){
	
	for(int k=1;k<G.size();++k){
		for (int i=1;i<G.size();++i){
			for (int j=1;j<G.size();++j){
				if (i==j) 
					G[i][j]->v[k] = 0;

                // k is terminal vertex here not intermediate 
				else if (i==k || j==k) 
					G[i][j]->v[k]=G[i][j]->v[k-1];

                // if edge src->k or k->dstn does not exist
				else if (G[i][k]->v[k-1]==INT_MAX || G[k][j]->v[k-1]==INT_MAX)
					G[i][j]->v[k]=G[i][j]->v[k-1];
				
                // update if cost of path is less with k as intermediate vertex
				else if (G[i][k]->v[k-1]+G[k][j]->v[k-1] < G[i][j]->v[k-1])
					G[i][j]->v[k] = G[i][k]->v[k-1]+G[k][j]->v[k-1];
				
				else
					G[i][j]->v[k]=G[i][j]->v[k-1];	
				
			}
		}
	}
}


int main(){

    int n,m;//no of vertex
    cin>>n>>m;
    
    vector<vector<ele*> > G(n+1,vector<ele*>(n+1));

    for(int i=1;i<G.size();++i){
    	for(int j=1;j<G.size();++j){
    		G[i][j] = new ele(n);
    	}
    }

    ioGraph(G,m);
    floyd(G);
    
    for(int i=0;i<=n;++i){
    	cout<<"K = "<<i<<"\n";
    	printGraph(G,i);
    	cout<<"\n";
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