// DSU Tree

#include <iostream>
#include <vector>
#include <deque>
#include <thread>
#include <chrono>

using namespace std;

class Node{
public:
	int ht,par;
	Node(){
		par=-1; // self rooted 
		ht = 0; // elements in subtree = 0
	}
};

deque<Node> nodeCache;

Node* newNode(){
	nodeCache.push_back(Node());
	Node* node = &nodeCache.back();
	return node;
}

int Find(vector<Node*>&vec,int i){
	while(vec[i]->par!=-1){
		i=vec[i]->par;
	}
	return i;
}

void Union(vector<Node*>&set,int i,int j){
}


void printparNht(vector<Node*> &vec)
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



//ht number of elements in subtree of tree
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	vector<Node*> set(n+1,NULL);

	for(int i=1;i<set.size();++i)
		set[i] = newNode();
	
	int u,v;
	while(true)
	{
		cin>>u;
		if(u==-1) break;

		cin>>v;

		Union(set,u,v);
		printparNht(set);
		cout<<flush;
        this_thread::sleep_for(chrono::seconds(1));
	}


	return 0;
}
