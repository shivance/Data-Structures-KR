//Kruskal

#include <bits/stdc++.h>

using namespace std;

class Edge{
public:
    int u,v,wt;
    Edge(int u,int v,int wt)
    {
        this->u = u;
        this->v = v;
        this->wt = wt;
    }
};

class Minheap
{
    Edge**harr;
    int capacity, heap_size;

public:
    // constructor
    Minheap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        harr = new Edge*[cap];
    }

    void swap(Edge**x,  Edge**y)
    {
        Edge* temp = *x;
        *x = *y;
        *y = temp;
    }

    //To heapify a subtree with root ar given index
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap_size && harr[l]->wt <= harr[smallest]->wt){
            if(harr[l]->wt==harr[smallest]->wt){
                if(harr[l]->u<harr[smallest]->u)
                    smallest = l;
                else if (harr[l]->u==harr[smallest]->u){
                    if (harr[l]->v<harr[smallest]->v)
                        smallest = l;
                }
                
            }
            else
                smallest = l;
        }
        if (r < heap_size && harr[r]->wt <= harr[smallest]->wt){
            if(harr[r]->wt==harr[smallest]->wt){
                if(harr[r]->u<harr[smallest]->u)
                    smallest = r;
                else if (harr[r]->u==harr[smallest]->u){
                    if (harr[r]->v<harr[smallest]->v)
                        smallest = r;
                }
                
            }
            else
                smallest = r;
        }

        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest]);
            heapify(smallest);
        }
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return (2 * i + 1);
    }

    int right(int i)
    {
        return (2 * i + 2);
    }

    Edge* extractMin()
    {
        if (heap_size <= 0)
            return NULL;
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        Edge* root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        heapify(0);

        return root;
    }

    Edge* getMin(){
        return harr[0];
    }

    int getsize()
    {
        return heap_size;
    }

    void insertKey(Edge* &k)
    {
        if (heap_size == capacity)
        {
            //cout << "Heap overflow\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        while (i != 0 && harr[parent(i)]->wt > harr[i]->wt)
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }

    void printHeap()
    {
        cout << "array\n";
        for (int j = 0; j < heap_size; ++j)
        {
            cout << harr[j]->wt << " ";
        }
        cout << "\n";
    }

};

class dsu
{
	class setNode
		{
		public:
			int ht,par;
			setNode(int i){
				par = i; 
				ht = 0; 
			}
		};

	vector <setNode*> arr;
	deque<setNode> nodeCache;

	
	public:
	setNode* newNode(int d)
	{
	    nodeCache.push_back(setNode(d));
	    setNode* node = &nodeCache.back();
	    return node;
	}

	dsu(int n){
		arr.resize(n+1,NULL);
		for (int i=1;i<arr.size();++i)
			arr[i] = newNode(i);
	}

	int Find(int i){
		while(arr[i]->par!=i){
			i=arr[i]->par;
		}
		return i;
	}
	
	void Union(int i,int j){
		int i_id = Find(i);
		int j_id = Find(j);

		if (i_id == j_id) return;
		if (arr[i_id]->ht>arr[j_id]->ht){
			arr[j_id]->par = i_id;	
		}
		
		else {
			arr[i_id]->par = j_id;
			if(arr[i_id]->ht==arr[j_id]->ht)
				arr[j_id]->ht++;
		}
	}

	void printparNht()
	{
		cout<<"Parent  : ";
		for (int i=1;i<arr.size();++i){
			cout<<arr[i]->par<<" ";
		}
		cout<<"\nHeights : ";
		for (int i=1;i<arr.size();++i){
			cout<<arr[i]->ht<<" ";
		}
		cout<<"\n";
	}

	void printset(){
		vector<vector<int> > v(arr.size(),vector<int>());

		for (int i=1;i<arr.size();++i)
			v[Find(i)].push_back(i);

		for (int i=1;i<v.size();++i){
			if (v[i].size()){
				for (int j=0;j<v[i].size();++j)
					cout<<v[i][j]<<" ";
				cout<<"\n";
			}
		}
		
	}

};


class Gnode{
public:
    int wt;
    bool flg;
    Gnode(int wt){
        this-> wt = wt;
        flg = false;
    }
};


void addEdge(vector<vector<Gnode*> >&G,int u,int v,int wt){
    G[u][v] = new Gnode(wt);
    G[v][u] = new Gnode(wt);
}

void printGraph(vector<vector<Gnode*> >&G){
    for (int i=1;i<G.size();++i){
        for (int j=1;j<G.size();++j){
            if (G[i][j])
                cout<<G[i][j]->flg<<" ";
            else 
                cout<<"x ";
        }
        cout<<"\n";
    }
}


void ioGraph(vector<vector<Gnode*> >&mat,Minheap& H,int m){
    int u,v,wt;
    for (int i=0;i<m;++i){
        cin>>u>>v>>wt;
        addEdge(mat,u,v,wt);
        Edge* edge = new Edge(u,v,wt);
        H.insertKey(edge);
    }
}


void DFS(vector<vector<Gnode*> >G,vector<bool>&visit,int src,int &wt)
{
    visit[src] = true;
    cout<<src<<" ";

    for (int i=1;i<G.size();++i){
        if (G[src][i] && !visit[i] && G[src][i]->flg){
            wt+=G[src][i]->wt;
            DFS(G,visit,i);
        }
    }
}

int main(){

    int n,m;//no of vertex
    cin>>n>>m;
    
    vector<vector<Gnode*> > G(n+1,vector<Gnode*>(n+1,NULL));
    Minheap H(m);
    ioGraph(G,H,m);

    dsu s(n);
    Edge* e;
    int src = H.getMin()->u;

    int k=0;
    while(H.getsize() && k<=n-1){
        e = H.extractMin();
        if (s.Find(e->u)!=s.Find(e->v)){
            s.Union(e->u,e->v);
            G[e->u][e->v]->flg = G[e->v][e->u]->flg = true;
            ++k;
        }
    }

    
    vector<bool>visit(n+1,false);
    int wt;
    DFS(G,visit,src,wt);
    

    return 0;
}

/*
9 14
1 2 4
1 8 8 
2 3 8
2 8 11
3 4 7
3 6 4
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 6
8 9 7
*/