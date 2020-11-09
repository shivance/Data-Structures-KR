#include <iostream>
#include <climits>

using namespace std;

// maximum size of heap 
#define MAX 100

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class Minheap
{
    int *harr;
    int capacity, heap_size;

public:
    // constructor
    Minheap()
    {
        heap_size = 0;
        capacity = MAX;
        harr = new int[capacity];
    }

    int getsize()
    {
        return heap_size;
    }

    //To heapify a subtree with root ar given index
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if (l < heap_size && harr[l] < harr[i])
            smallest = l;
        if (r < heap_size && harr[r] < harr[i])
            smallest = r;

        if (smallest != i)
        {
            swap(&harr[i], &harr[smallest]);
            heapify(smallest);
        }
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return (2 * i + 1);
    }

    int right(int i)
    {
        return (2 * i + 2);
    }

    int extractMin()
    {
        if (heap_size <= 0)
            return 0;
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        int root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        heapify(0);

        return root;
    }

    int getMin()
    {
        if (heap_size==0) return 0;
        return harr[0];
    }

    void printheap()
    {
        //cout << "Heap \n";
        for (int j = 0; j < heap_size; ++j)
        {
            cout << harr[j] << " ";
        }
        cout << "\n";
    }

    void insertKey(int k)
    {
        if (heap_size == capacity)
        {
            cout << "Heap overflow\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        while (i != 0 && harr[parent(i)] > harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
};

class Maxheap
{
    int *harr;
    int capacity, heap_size;
    
public:
    // constructor
    Maxheap()
    {
        heap_size = 0;
        capacity = MAX;
        harr = new int[MAX];
    }

    int getsize()
    {
        return heap_size;
    }

    //To heapify a subtree with root ar given index
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap_size && harr[l] > harr[i])
            largest = l;
        if (r < heap_size && harr[r] > harr[i])
            largest = r;

        if (largest != i)
        {
            swap(&harr[i], &harr[largest]);
            heapify(largest);
        }
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return (2 * i + 1);
    }

    int right(int i)
    {
        return (2 * i + 2);
    }

    int extractMax()
    {
        if (heap_size <= 0)
            return 0;
        if (heap_size == 1)
        {
            heap_size--;
            return harr[0];
        }

        int root = harr[0];
        harr[0] = harr[heap_size - 1];
        heap_size--;
        heapify(0);

        return root;
    }

    int getMax()
    {
        if (heap_size==0) return 0;
        return harr[0];
    }

    void printheap()
    {
        //cout << "Heap \n";
        for (int j = 0; j < heap_size; ++j)
        {
            cout << harr[j] << " ";
        }
        cout << "\n";
    }

    void insertKey(int k)
    {
        if (heap_size == capacity)
        {
            cout << "Heap overflow\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        harr[i] = k;

        while (i != 0 && harr[parent(i)] < harr[i])
        {
            swap(&harr[i], &harr[parent(i)]);
            i = parent(i);
        }
    }
};

int runningMedian(Maxheap &M,Minheap &m)
{
        //if (m.getsize()==0 || M.getsize()>0) return M.getMax();
        //if (m.getsize()>0 || M.getsize()==0) return m.getMin();

        if (m.getsize() == M.getsize())
        {
            //cout<<"Running median : "<<(m.getMin()+M.getMax())/2<<"\n";
            return (m.getMin()+M.getMax())/2;
        }

        else if (m.getsize() - M.getsize() >= 1)
        {
            while(m.getsize() - M.getsize() >1)
            {
                M.insertKey(m.extractMin());
            }

            if (m.getsize() > M.getsize()) return m.getMin();
            else return (m.getMin()+M.getMax())/2;
        }
        else 
        {
            while(M.getsize() - m.getsize() >= 1)
            {
                m.insertKey(M.extractMax());
            }

            if (m.getsize() < M.getsize()) return M.getMax();
            else return (m.getMin()+M.getMax())/2;
        }
}

int main()
{
    int a, rm = 0;
    Minheap m;Maxheap M;
    
    while(true)
    {
        cin>>a;
        if (a==-1) break;
        
        if (a>=rm) m.insertKey(a);
        else M.insertKey(a);

        rm = runningMedian(M,m);
        cout<<"Running median is : "<<rm<<"\n";
        cout<<"Minheap : \n";m.printheap();
        cout<<"Maxheap : \n";M.printheap();
    }

    return 0;
}