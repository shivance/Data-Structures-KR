#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class strnode
{
public:
    bool EOW;
    string str;
    strnode(string s)
    {
        EOW = false;
        str = s;
    }
};

class trienode
{
public:
    trienode** child;
    strnode** leaf;
    strnode* s;
    bool EOW;
    trienode()
    {
        EOW = true;
        s = NULL;
        child = new trienode*[3];
        leaf = new strnode*[3];
        for (int i =0;i<3;++i) {
            this->child[i]=NULL;
            this->leaf[i]=NULL;
        }
    }
};


void insert(trienode*&T,string str)
{
    // will create a str node if next trienode is null 
    trienode* tmp = T;
    strnode* leaf = new strnode(str);
    int index;
    strnode* s = NULL;
    

    int i =0,j=0;
    while(i<str.length())
    {
        index = str[i]-'A';
        if (tmp->child[index]==NULL && tmp->leaf[index]==NULL){
            tmp->leaf[index] = leaf;
            //tmp->s = s;
            return;
        }

        if (tmp->child[index]==NULL && tmp->leaf[index]!=NULL){
            s = tmp->leaf[index];
            tmp->leaf[index] = NULL;
            string tmpstr=s->str;
            while(tmpstr[i]==str[i] && i<min(tmpstr.length(),str.length()))
            {
                index = str[i]-'A';
                tmp->child[index] = new trienode();
                tmp = tmp->child[index];
                ++i;
            }
            tmp->leaf[tmpstr[i]-'A'] = new strnode(tmpstr);
            tmp->leaf[str[i]-'A'] = new strnode(str);

            return;
        }

        if(!tmp->child[index]){
            tmp = tmp->child[index];++i;
        }

        tmp->s = new strnode(str);
    }
}


void print(trienode*T)
{
    for (int i=0;i<3;++i)
    {
        if (T->leaf[i])
        {
            cout<<T->leaf[i]->str<<" ";
            return;
        }
        if(T->s)
            cout<<T->s->str<<" ";
        print(T->child[i]);
    }
}

int main()
{
    string s;
    trienode* T = new trienode();

    while(true)
    {
        cin>>s;
        if (s=="#") break;
        insert(T,s);
    }
    print(T);

    return 0;
}

