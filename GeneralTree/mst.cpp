#include <iostream>
#include <climits>

using namespace std;

class mstnode
{
    int m;
    int* key;
    int cnt;
    mstnode**way;

    mstnode(int m)
    {
        this->m = m;
        key = new int[m-1];
        cnt = 0;
        way = new mstnode*[m];

        for (int i=0;i<m-1;++i) key[i]=INT_MIN;
    }
};

//version 1
void insertv1(mstnode*&MT,int k)
{
    if (k>MT->key[MT->cnt])
    {
        MT->key[MT->cnt] = k;
        MT->cnt++;
        return;
    }

    for (int i=0;i<MT->cnt;++i)
    {
        if (k>MT->key[i]) break;
    }

    MT->way[i] = new mstnode(m);
    insertv1(MT->way[i],k);
}

void insertionS(mstnode* &MT)
{
	int min_index;mstnode* tmp,int tmpd;;
	for (int i=0;i<(MT->m)-1;i++){
		min_index = i;
		for (int j=i+1;j<MT->m;j++){
			if (arr[j] < arr[min_index])
			{
				min_index=j;
			}
		}
		dtmp = MT->key[i];
		MT->key[i]= MT->key[min_index];
		MT->key[min_index]=dtmp;

        tmp = MT->way[i];
        MT->way[i]=MT->way[min_index];
        MT->way[min_index]=tmp;
	}
}


//version 2 --> insert and sort
void insertv2(mstnode*&MT,int k)
{
    if (k>MT->key[MT->cnt])
    {
        MT->key[MT->cnt] = k;
        MT->cnt++;
        insertionS(MT);
        return;
    }

    for (int i=0;i<MT->cnt;++i)
    {
        if (k>MT->key[i]) break;
    }

    MT->way[i] = new mstnode(m);
    insert(MT->way[i],k);
    insertionS(MT);
}


void inorder(mstnode*&MT)
{
    
}

