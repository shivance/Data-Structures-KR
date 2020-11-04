#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void swap(int *a,int *b)
{
	int temp;
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

void siftUp(vector<int>&H,int &i,int &size)
{
	while(i>1 && H[parent(i)] > H[i])
	{
		swap(&H[parent(i)],&H[i]);
		i = parent(i);
	}
}

void siftDown(vector<int>&H,int i, int &s)
{
	int maxind = i;
	int l = left(i);
	if (l<=s && H[l] < H[maxind])
	{
		maxind = l;
	}

	int r = right(i);

	if (r<=s && H[r] < H[maxind])
	{
		maxind = r;
	}

	if (maxind != i)
	{
		swap(&H[i],&H[maxind]);
		siftDown(H,maxind,s);
	}
}

void insert(vector<int> &H,int p,int&s)
{
	if (s==H.size())
		return;
	s++;
	H.push_back(p);
	siftUp(H,s,s);
}

int ExtractMin(vector<int>&H,int&size)
{
	int result = H[1];
	H[1] = H[size];
	size--;
	siftDown(H,1,size);
	return result;
}


void buildHeap(vector<int>&H)
{
	int siz = H.size();
	siz--;
	for (int i=siz/2;i>=1;--i)
	{
		siftDown(H,i,siz);
	}
}

int main()
{
	cout<<"Enter size of array : ";int n; cin>>n;
	vector<int> H(n+1,0);
	cout<<"Enter elements of array : ";
	for (int i=1;i<H.size();++i) cin>>H[i];
	buildHeap(H);
	
	
	int size = H.size()-1;

	vector<int> HeapSort;
	cout<<"Sorted array : "<<endl;
	while(size>0)
	{
		HeapSort.push_back(ExtractMin(H,size));
	}
	
	for (int i=0;i<HeapSort.size();++i)
	{
		cout<<HeapSort[i]<<" ";
	}
	
	return 0;
}