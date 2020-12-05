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

        if (l < heap_size && harr[l]->wt <= harr[smallest]->wt)
            smallest = l;
        if (r < heap_size && harr[r]->wt <= harr[smallest]->wt)
            smallest = r;

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

class setNode{
public:
    int ht,par;
    setNode(){
        par=-1; // self rooted 
        ht = 0; // elements in subtree = 0
    }
};

int Find(vector<setNode*>&vec,int i){
    while(vec[i]->par!=-1){
        i=vec[i]->par;
    }
    return i;
}

void Union(vector<setNode*>&set,int i,int j){
    // merge set of j into i

    int i_id = Find(set,i);
    int j_id = Find(set,j);

    // if same set
    if (i_id == j_id) return;

    // if height(tree of i) > height(tree of j)
    // hang tree of j in
    if (set[i_id]->ht>set[j_id]->ht){
        set[j_id]->par = i_id;  
    }
    

    else {
        set[i_id]->par = j_id;
        if(set[i_id]->ht==set[j_id]->ht)
            set[j_id]->ht++;
    }
}


void printparNht(vector<setNode*> &vec)
{
    cout<<"Parent  : ";
    for (int i=1;i<vec.size();++i){
        cout<<vec[i]->par<<" ";
    }
    cout<<"\nHeights : ";
    for (int i=1;i<vec.size();++i){
        cout<<vec[i]->ht<<" ";
    }
    cout<<"\n";
}


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


void DFS(vector<vector<Gnode*> >G,vector<bool>&visit,int src)
{
    visit[src] = true;
    cout<<src<<" ";

    for (int i=1;i<G.size();++i){
        if (G[src][i] && !visit[i] && G[src][i]->flg)
            DFS(G,visit,i);
    }
}

int main(){

    int n,m;//no of vertex
    cin>>n>>m;
    
    vector<vector<Gnode*> > G(n+1,vector<Gnode*>(n+1,NULL));
    Minheap H(m);
    ioGraph(G,H,m);

    //DSU
    vector<setNode*> set(n+1,NULL);

    for(int i=1;i<set.size();++i)
        set[i] = new setNode();

    
    Edge* hk = H.getMin();
    int hook = H.getMin()->u;

    Edge* e = H.extractMin();
    G[e->u][e->v]->flg = true;
    G[e->v][e->u]->flg = true;
    
    cout<<"Here\n";

    int cnt = 0;
    while(cnt<m-2 && H.getsize()>0){
        e = H.extractMin();
        int id1 = Find(set,e->v);
        int id2 = Find(set,e->u);
        if (id1!=id2 || id1==id2==-1){
            cout<<"wt = "<<e->wt<<"\n";
            
            cout<<"ID of u "<<e->u<<" is "<<id1;
            cout<<"\nID of v "<<e->v<<" is "<<id2<<"\n\n";
            ++cnt;
            if(G[e->u][e->v]){
                G[e->u][e->v]->flg =true;
                G[e->v][e->u]->flg =true;
            }
            Union(set,)

            //cout<<"x\n";
            //continue;
        }
        //else{
            
        //}
        
    }

    vector<bool>visit(n+1,false);

    DFS(G,visit,hook);
    

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