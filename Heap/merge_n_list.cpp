#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Node
{
public:
    int dt;
    Node* next = NULL;
};

void swap(Node**a,Node**b)
{
	Node* temp;
	temp = *a;
	*a = *b;
	*b = temp;
}


int parent(int i)
{
	return (i/2);
}

int left(int i)
{
	return 2*i;
}

int right(int i)
{
	return 2*i+1;
}

void siftUp(vector<Node*>&H,int &i,int &size)
{
	while(i>1 && H[parent(i)]->dt > H[i]->dt)
	{
		swap(&H[parent(i)],&H[i]);
		i = parent(i);
	}
}

void siftDown(vector<Node*>&H,int i, int &s)
{
    if (H[i]==NULL) return;

	int minind = i;
	int l = left(i);
	if (l<=s && H[l]!=NULL && H[l]->dt < H[minind]->dt)
	{
		minind = l;
	}

	int r = right(i);

	if (r<=s && H[r]!=NULL && H[r]->dt < H[minind]->dt)
	{
		minind = r;
	}

	if (minind != i)
	{
		swap(&H[i],&H[minind]);
		siftDown(H,minind,s);
	}
}

void insertList(vector<Node*> &H,Node* list,int&s)
{
	if (s==H.size())
		return;
	s++;
	H.push_back(list);
	siftUp(H,s,s);
}

int ExtractMin(vector<Node*>&H,int& size)
{
    if (H[1]==NULL) return INT_MAX;
    int result = H[1]->dt;

    if (H[1]->next !=NULL)
    {
        H[1] = H[1]->next;
    }
    else{
	    H[1] = H[size];
        size--;
    }

	siftDown(H,1,size);

    return result;
}

void buildHeap(vector<Node*>&H)
{
	int siz = H.size();
	siz--;
	for (int i=siz/2;i>=1;--i)
	{
		siftDown(H,i,siz);
	}
}

void printvec(vector<int> v)
{
    for (int i=0;i<v.size();++i) cout<<v[i]<<" ";
}

void prinList(Node* head)
{
    while(head !=NULL)
    {
        cout<<head->dt<<" ";
        head = head->next;
    }
}

void printHeap(vector<Node*> &v)
{
    for (int i=1;i<v.size();++i)
    {
        prinList(v[i]);
        cout<<endl;
    }
}

int main()
{
    int n; cin>>n;// number of list
    vector<Node*> H(n+1,NULL);
    Node* prev,*head,*tmpn;

    int dt;
    for (int i=1;i<=n;++i)
    {
        cin>>dt;
        if (dt==-1) continue;
        head = new Node(); head->dt = dt; 
        H[i] = head;
        prev = head;
        while(true)
        {
            cin>>dt;
            if (dt==-1) break;

            tmpn = new Node();
            tmpn->dt = dt;
            prev->next = tmpn;
            prev = tmpn;
        }  
    }
    buildHeap(H);
    cout<<"Heap is : \n";   
    printHeap(H);

    vector<int>ans;
    int size = H.size()-1;
    int p;
    while(size>=1)
    {
        p = ExtractMin(H,size);
        cout<<"pushing p = "<<p<<" size = "<<size<<endl;
        ans.push_back(p);
    }
    //cout<<ans.size();
    printvec(ans);
    return 0;
}