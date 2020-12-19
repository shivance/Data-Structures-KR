#include <iostream>
#include <climits>
using namespace std;

class mlnode
{
public:
	int key;
	mlnode* next;mlnode* dlink;
	mlnode()
	{
		key = INT_MIN;
		next = NULL;
		dlink = NULL;
	}

};

int main()
{
	int a,drctn,k;

	mlnode* head = new mlnode();
	mlnode* tmp;
	mlnode* tmp_up;
	mlnode *prev;
	mlnode *tmp_cur_d;
	cin>>a;
	head->key = a;
	tmp = head;

	cin>>drctn; 

	
	if (drctn == 1)
	{
		tmp_up = tmp;
		while(true)
		{
			cin>>k;
			if (k==-1) break;
			tmp_cur_d = new mlnode();
			tmp_cur_d->key = k;
			tmp_up->dlink = tmp_cur_d;
			tmp_up = tmp_cur_d;
		}
	}

	prev = head;
	tmp = head;

	int lmp;

	while(true)
	{
		cin>>a;
		if (a == -2 ) break;
		cin>>drctn;
		tmp = new mlnode();
		tmp->key = a;
	
		prev->next = tmp;

		
		if (drctn == 1)
		{
			tmp_up = tmp;
			while(true)
			{
				cin>>k;

				if (k==-1) 
				{		
					break;
				}

				tmp_cur_d = new mlnode();
				tmp_cur_d->key = k;
				tmp_up->dlink = tmp_cur_d;
				tmp_up = tmp_cur_d;
			}
		}
		else if (drctn==0) 
		{
			prev = tmp;
			continue;
		}

		prev = tmp;
	}

	//cout<<"INPUT COMPLETE\n";

	tmp = head;

	while(tmp!=NULL)
	{
		if (tmp->next != NULL || tmp->dlink!=NULL){
			if (tmp->dlink!=NULL)
			{
				tmp_cur_d = tmp;
				while(tmp_cur_d->dlink!=NULL)
				{
					//cout<<tmp_cur_d->key<<"\n";
					tmp_cur_d = tmp_cur_d->dlink;
				}
				tmp_cur_d->next = tmp->next;
				tmp->next = NULL;
				tmp = tmp_cur_d->next;
			}
			else
			{
				//cout<<tmp->key<<" ";
				tmp=tmp->next;
			}
		}
		else
			break;
	}

	//cout<<"Step 2 COMPLETE\n";
	//Now our converted linked list has either dlink or next != NULL; if both NULL it means we 
	//have reached tail of linked list
	tmp = head;
	while(tmp!=NULL)
	{
		if (tmp->next!=NULL)
		{
			cout<<tmp->key<<" ";
			tmp=tmp->next;
		}

		else if (tmp->dlink!=NULL)
		{
			cout<<tmp->key<<" ";
			tmp=tmp->dlink;
		}
		else if (tmp->next == NULL && tmp->dlink == NULL)
		{
			if (tmp->key>INT_MIN)
			{
				cout<<tmp->key<<"\n";
			}
			break;
		}
	}

	return 0;
}



