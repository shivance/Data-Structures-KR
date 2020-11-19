#include <iostream>
#include <climits>
#include <cstdlib>
using namespace std;

class node
{
public:
	int dt;
	int idx;
	node* next;
	
	/*node(int x)
	{
		dt = x;
		next = NULL;
		eol = false;
	}*/
};

void print_list(node* n)
{
	while (n!=NULL){
		cout << n->dt <<" ";
		n = n->next;
	}
}

void deleteNode(node **head_ref, int key) 
{ 
 
    node* temp = *head_ref, *prev; 
  
 
    if (temp != NULL && temp->idx == key) 
    { 
        *head_ref = temp->next;   
        free(temp);               
        return; 
    } 
  
  
    while (temp != NULL && temp->idx != key) 
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
  
    if (temp == NULL) return; 
  
  
    prev->next = temp->next; 
  
    free(temp);  
} 

int main()
{
	node* head , end;
	head = NULL;
	int a;
	cin>>a;
	head = new node();
	head->dt = a;
	head->idx = 1;
	int cnt = 1;

	node* prev = head;
	node* tmp;
	while(true)
	{
		cin>>a;
		
		if (a==-1)
		{
			break;
		}

		else
		{
			cnt++;
			tmp = new node();
			tmp->dt = a;
			tmp->idx = cnt;
			prev->next = tmp;
			prev = tmp;
		}	
	}

	node* temp = head;

	while(temp!=NULL)
		{
				
			if (temp->dt == head->idx ){
				head = head->next;
				cout<<"in if deleting "<<temp->dt<<"\n";
				cout<<"head->key = "<<head->dt<<"\n";
				deleteNode(&temp,temp->dt);
				cout<<"current "<<temp->dt<<"\n";
				//temp = temp->next;
			}

			else{
				cout<<"in else deleting "<<temp->dt<<"\n";
				cout<<"head->key = "<<head->dt<<"\n";
				deleteNode(&temp,temp->dt);
				temp = temp->next;
			}
			print_list(head);
			cout<<"\n";
	}	

	print_list(head);

	return 0;
}