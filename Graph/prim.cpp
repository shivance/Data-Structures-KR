// take arbitarary root
// add root to list mark true
// now loop through list find element with least edge weight ..mark this vertex as true and add to list...until list size is not equal to number of vertex

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
        for (int j = 0; j < heap_size; ++j)
        {
            cout << harr[j]->wt << " ";
        }
        cout << "\n";
    }

};


void ioGraph(vector<vector<int> >&G,int m){
    int u,v,wt;
    for (int i=0;i<m;++i){
        cin>>u>>v>>wt;
	    G[u][v] = wt;
	    G[v][u] = wt;
	    
    }
    
}

int prim(vector<vector<int> >&G){
	vector<bool>visited(G.size(),false);
	int n = G.size()-1;
	Minheap H(n*(n-1)/2);

	int u =1;
	Edge* e = NULL;
	int wt = 0;
	int cnt = 0;
	
	while(1){
		visited[u]=true;
		if (e!=NULL) wt+=e->wt;
		
		++cnt;
        if (cnt==G.size()-1) break;

		for (int i=1;i<G.size();++i){
			if (!visited[i] && G[u][i]!=INT_MAX && G[u][i]!=0){
				Edge* ed = new Edge(u,i,G[u][i]);
				H.insertKey(ed);
			}
		}

        while(1){
		  e = H.extractMin();
          if (!visited[e->v]){ 
            u = e->v;
            break;
          }  
        }
		
	}

	return wt;
}


int main(){
	int n,m;
	cin>>n>>m;
	vector<vector<int> >G(n+1,vector<int> (n+1,INT_MAX));

	for (int i=1;i<G.size();++i)
		G[i][i] = 0;
	

	ioGraph(G,m);
	cout<<prim(G)<<"\n";

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