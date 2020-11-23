// trie = prefix tree

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class node
{
public:
    bool EOW;
    int s;
    node **child;
    node(int size)
    {
        this->s = size;
        child = new node *[size];
	EOW = false;
	for (int i=0;i<size;++i) this->child[i] = NULL;
    }
};


void insert(node *root, string str, int maxs)
{
    // maxs is the max length of the string encountered in input
    node *tmp = root;
    int index;
    for (int i = 0; i < str.length(); ++i)
    {
        index = (int)(str[i] - 'a');
        cout<<i<<" = i\n";
        if (!tmp->child[index])
            tmp->child[index] = new node(maxs);

	tmp = tmp->child[index];
        
    }

    tmp->EOW = true;
}

bool search(node *root, string key, int size)
{
    node *tmp = new node(size);
    int index;
    for (int i = 0; i < key.length(); ++i)
    {
        index = (int)(key[i] - 'a');
        if (!tmp->child[index])
            return false;
        
        if (i<key.length()-1)
	    tmp = tmp->child[index];        
    }
    
    return (tmp->EOW && tmp != NULL);
}

int main()
{
    string strs[] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    int size = sizeof(strs) / sizeof(strs[0]);
    int maxlen = 0, tmp;
    for (int i = 0; i < size; ++i)
    {
        tmp = strs[i].length();
        if (tmp > maxlen)
            maxlen = tmp;
    }
     
    node *root = new node(size);

    for (int i = 0; i < size; ++i)
    {
        insert(root, strs[i], maxlen);
    }

    //testing

    /*while (true)
    {
        string inp;
        cin >> inp;
        search(root, inp, maxlen) ? cout << "Yes\n" : cout << "No\n";
    }*/

    return 0;
}
