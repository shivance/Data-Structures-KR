#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class node
{
public:
	vector <int> i,vector<char> c,vector <float> f;
}


class Queue
{

	int size,front,rear;
	unsigned capacity;
	int* arr;
public:
	Queue(unsigned s)
	{
		size = 0;
		arr = new int[s];
		capacity = s;
		front = rear = -1;
	}

	bool isEmpty()
	{
		if (size==0)
			return true;
		else 
			return false;
	}

	bool isFull()
	{
		if (size == capacity)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool enq(int val)
	{
		if (isFull())
		{
			return false;
		}
		else if (isEmpty())
		{
			front = 0;rear = 0;
			arr[rear] = val;
			++size;
			return true;
		}
		else 
		{
			rear=(rear+1)%capacity;
			++size;
			arr[rear]=val;
			return true;
		}
	}

	int deq()
	{
		if (isEmpty())
		{
			return INT_MAX;
		}

		else if (size == 1)
		{
			size--;
			int k = arr[front];
			front = rear = -1;
			return k;
		}

		else
		{
			size--;
			int k = arr[front];
			front = (front+1)%(capacity);

			return k;
		}
	}

	int fron()
	{
		return arr[front];
	}

	int rea()
	{
		return arr[rear];
	}

	void display()
	{
		cout<<"front = "<<front<<" rear = "<<rear<<endl;
		if (front==-1 && rear==-1)
		{
			cout<<"queue is Empty\n";
		}

		else if (front <= rear)
		{
			//cout<<"front <= rear\n";
			
			for (int i=front;i<=rear;++i)
			{
				cout<<arr[i]<<" ";
			}
			cout<<"\n";
		}
		else
		{
			for (int i=front;i<capacity;++i)
			{
				cout<<arr[i]<<" ";
			}
			for (int i=0;i<=rear;++i)
			{
				cout<<arr[i]<<" ";
			}
			cout<<"\n";
		}
	}

};


int main()
{
	queue<node> q;
	// flags are c : char , i : int , f : float , k for terminating input in a line
	int n;cin>>n;//number of elements
	char c1,c2;int i1; float f1;int k1;
	int k1;
	for (int i=0;i<n;++i)
	{
		cin>>c1;
		if (c1=='i')
		{
			cin>>k1;
			if (k1==-1)
			{
				break;
			}
			else
			{
				q->i.push_back(k1);
			}
		}

		else if (c1 == 'f')
		{
			cin>>f1;
			q->f.push_back(f1);
		}
		else if (c1=='c')
		{
			cin>>c2;
			q->c.push_back(c2);
		}
	}

	return 0;
}