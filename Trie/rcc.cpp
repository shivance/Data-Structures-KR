#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>

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
    for (int i=0;i<v.size();++i) cout<<v[i];
}

void insert(trienode* &T ,vector<char>keys,string str)
{
    int index;trienode* tmp = T;
    vector<char>::iterator it;
    int i;
    for (i = 0;i<str.length();++i)
    {
        index = find(keys.begin(),keys.end(),str[i]) - keys.begin();
        if (!tmp->child[index])
            tmp->child[index] = new trienode(keys.size());

        tmp = tmp->child[index];
    }
    //index = find(keys.begin(),keys.end(),str[i]) - keys.begin();
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

void print(trienode*T,vector<char>keys,vector<char>stk)
{
    if (T==NULL || T->EOW)
    {
        printvec(stk);
        if (T!=NULL)
        {
            for (int i=0;i<T->s;++i) if(T->child[i]) cout<<keys[i];
        } 
        cout<<" ";
        return;
    }
    

    for (int i=0;i<T->s;++i)
    {
        if (T->child[i])
        {
            stk.push_back(keys[i]);
            print(T->child[i],keys,stk);
            stk.pop_back();
        }
    }
}

int main()
{
    string s;
    
    vector<string> vec;
    map<char,bool> m;
    bool o = false;
    while(true)
    {
        cin>>s;
        if (s[s.length()-1]=='#') 
        { 
            o = true;
            s.erase(s.length()-1);
        }
        vec.push_back(s);
        for (int j=0;j<s.length();++j)
            m[s[j]] = true;

        if (o) break;
    }

    vector<char> keys;
    map<char,bool>::iterator it;
    for (it = m.begin();it!=m.end();++it)
        keys.push_back(it->first);

    trienode* T = new trienode(keys.size());

    for (int i=0;i<vec.size();++i)
        insert(T,keys,vec[i]);
    
    vector<char>stk;
    print(T,keys,stk);

    return 0;
}
