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
	int minind = i;
	int l = left(i);
	if (l<=s && H[l]->dt < H[minind]->dt)
	{
		minind = l;
	}

	int r = right(i);

	if (r<=s && H[r]->dt < H[minind]->dt)
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

int ExtractMin(vector<Node*>&H,int&size)
{
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

int main()
{
    int n; cin>>n;// number of list
    vector<Node*> H;
    Node* prev,*head,*tmpn;

    int dt;
    for (int i=0;i<n;++i)
    {
        cin>>dt;
        if (dt==-1) continue;
        head = new Node(); head->dt = dt; 
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
    vector<int>ans;
    int size = H.size()-1;
    while(size>0)
    {
        ans.push_back(ExtractMin(H,size));
    }

    printvec(ans);
    return 0;
}