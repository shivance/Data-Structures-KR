#include <iostream>
#include <climits>
#include <map>
#include <cstdlib>
#include <cstddef>
using namespace std;

class node
{
public:
	int dt;
	node* next;
	bool eol;

	node()
	{		
		next = NULL;
	}
};

void print_list(node* n)
{
	while (!n->eol){
		cout << n->dt <<" ";
		n = n->next;
	}
}

node* inputLL()
{
	node* head = new node();
	node* prev;
	int a; cin>>a;
	if (a==-1) 
	{
		return NULL;
	}
	head->dt = a;node* tmp;
	prev = head;
	while(true)
	{
		cin>>a;
		if (a==-1)
		{
			cout<<"BROKE\n";
			break;
		}
		else
		{
			tmp = new node();
			cin>>a;
			tmp->dt = a;
			prev->next = tmp;
			prev = tmp;
		} 
	}

	return head;

}


int main()
{
	int n;
	cin>>n;
	node*arr[n] ;
	for (int i=0;i<n;++i)
	{
		arr[i] = inputLL();
		print_list(arr[i]);
	}

	//traversing through linkedlists and hashing so as to get the count

	map<int,int> m;

	node* tmp;
	for (int i=0;i<n;++i)
	{
		tmp = arr[i];
		while(tmp->next != NULL)
		{
			m[tmp->dt]++;
			tmp = tmp->next;
		}
	}

	map<int,int>::iterator it,itr;

	int count[4];count[0] = INT_MAX;
	int previdx = 0;
	for (int i=1;i<=3;++i)
	{
		int max = INT_MIN;

		for (it = m.begin();it!=m.end();++it)
		{
			if (it->second>max && it->second<count[previdx])
			{
				max = it->second;
			}
		}

		count[i] = max;
		previdx = i;
	}

	// now our count[1,2,3] contain top 3 values of counts

	for (int i=1;i<=3;++i)
	{
		for (it = m.begin();it!=m.end();++it)
		{
			if(it->second == count[i])
			{
				cout<<it->first<<" "<<it->second<<"\n";
			}
		}
	}


	return 0;
}