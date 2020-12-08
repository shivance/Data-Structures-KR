#include <bits/stdc++.h>
using namespace std;

# define fastIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

class sets
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

	sets(int n){
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


int main()
{
	fastIO
	int n;cin>>n;

	sets s(n);
	int u,v;
	while(true)
	{
		cin>>u;
		if(u==-1) break;

		cin>>v;

		s.Union(u,v);
			
	}
	s.printset();
	return 0;

}

/*
Testcase #1
9
3 6
5 8
7 9
8 4
1 2
9 8
-1
*/