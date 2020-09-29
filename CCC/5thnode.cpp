#include <iostream>
#include <climits>
using namespace std;

class node
{
public:
	int dt;
	node* next;
	bool eol;

	/*node(int x)
	{
		dt = x;
		next = NULL;
		eol = false;
	}*/
};

void print_list(node* n)
{
	while (!n->eol){
		cout << n->dt <<" ";
		n = n->next;
	}
}



int main()
{
	node* head , end;
	head = NULL;
	int a;
	cin>>a;
	head = new node();
	head->dt = a;
	
	int cnt = 1;
	node* fifth = NULL;
	node* prev = head;
	node* tmp;
	while(true)
	{
		cin>>a;
		
		if (a==-1)
		{
			tmp->eol = true;
			if (cnt <5)
			{
				cout<<0<<"\n";
			}
			else{
				tmp->next = fifth;
			}
			break;
		}

		else
		{
			cnt++;
			tmp = new node();
			tmp->dt = a;
			prev->next = tmp;
			prev = tmp;
		}

		if (cnt==5)
		{
			fifth = tmp;
		}

	}

	//print_list(head);
	//cout<<"\n\n";
	

	if (tmp->eol)
	{	
		cout<<1<<"\n"<<fifth->dt<<"\n";
	}
	else
	{
		cout<<0<<"\n";
	}

	return 0;
}