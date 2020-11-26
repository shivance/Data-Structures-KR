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
    string tmpstr;

    int i =0;
    while(i<str.length())
    {
        index = str[i]-'A';
        if (tmp->child[index]==NULL && tmp->leaf[index]==NULL){
            tmp->leaf[index] = new strnode(str);
            //tmp->s = s;
            return;
        }

        if (tmp->leaf[index]!=NULL){
            s = tmp->leaf[index];
            tmp->leaf[index] = NULL;
            tmpstr=s->str;
            cout<<tmpstr<<" "<<str<<" i = "<<i<<"\n";
            cout<<"HERE\n";
            while(tmpstr[i]==str[i] && i <min(str.length(),tmpstr.length()))
            {
                
                index = str[i]-'A';
                tmp->child[index] = new trienode();
                tmp = tmp->child[index];
                ++i;
            }
            tmp->leaf[tmpstr[i]-'A'] = new strnode(tmpstr);
            tmp->leaf[str[i]-'A'] = new strnode(str);
            //tmp->s = new strnode(str);
            return;
        }
        

        /*else if(tmp->child[index]!=NULL){
            tmp = tmp->child[index];++i;
            index = str[i]-'A';
        } */      
    }
    
    int idx = str[str.length()-1]-'A';
    tmp = tmp->child[idx];
    tmp->s = new strnode(str);
    
}


void print(trienode*T)
{
    for (int i=0;i<3;++i)
    {
        if (T->leaf[i])
        {
            cout<<"T->leaf : ";
            cout<<T->leaf[i]->str<<"\n";
        }
        if (T->child[i])
            print(T->child[i]);

        if(T->s){
            cout<<"T->s :";
            cout<<T->s->str<<"\n";
            return;
        }
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
        print(T);
        cout<<"\n";
    }
    //print(T);

    return 0;
}

// AAB CABB BAA ABBBC BCCCAA BC A ABB #