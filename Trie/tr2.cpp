#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

class trienode
{
public:
    bool EOW;
    int s;
    trienode **child;
    trienode(int size)
    {
        s = size;
        child = new trienode *[size];
	    EOW = false;
	    for (int i=0;i<size;++i) this->child[i] = NULL;
    }
};

void printvec(vector<char>v)
{
    for (int i=0;i<v.size();++i) cout<<v[i]<<" ";
}

void insert(trienode* &T ,vector<char>keys,string str)
{
    int index;trienode* tmp = T;
    vector<char>::iterator it;
    int i;
    for (i = 0;i<str.length()-1;++i)
    {
        index = find(keys.begin(),keys.end(),str[i]) - keys.begin();
        if (!tmp->child[index])
            tmp->child[index] = new trienode(keys.size());

        tmp = tmp->child[index];
    }
    index = find(keys.begin(),keys.end(),str[i]) - keys.begin();
    //tmp[index] = true;
    tmp->EOW = true;
}

bool search(trienode*T,vector<char>keys,string str)
{
    int index,i=0;
    trienode* tmp = T;

    vector<char>::iterator it;
    for (i=0;i<str.length()-1;++i)
    {
        index = find(keys.begin(),keys.end(),str[i]) - keys.begin();
        if (!tmp->child[index]) 
            return false;

        tmp = tmp->child[index];
    }
    index = find(keys.begin(),keys.end(),str[i]) - keys.begin();

    return (tmp->EOW && tmp!=NULL);
}

void print(trienode*T)

int main()
{
    string s;
    int n;cin>>n;
    vector<string> vec;
    map<char,bool> m;
    for (int i=0;i<n;++i)
    {
        cin>>s;
        vec.push_back(s);
        for (int j=0;j<s.length();++j)
            m[s[j]] = true;
    }

    vector<char> keys;
    map<char,bool>::iterator it;
    for (it = m.begin();it!=m.end();++it)
        keys.push_back(it->first);

    trienode* T = new trienode(keys.size());

    for (int i=0;i<vec.size();++i)
        insert(T,keys,vec[i]);
    

    for (int i=0;i<n;++i){
        cin>>s;
        cout<<search(T,keys,s)<<"\n";
    }

    return 0;
}
