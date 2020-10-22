#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Hnode
{
public:
    Hnode* l,*r;
    char c;int freq;
    Hnode()
    {
        c = '0';
        l=r=NULL;
    }
};

bool func(Hnode* a,Hnode* b)
{
    return a->freq > b->freq;
}

void printvec(vector<Hnode*>&H)
{
    for (int i=0;i<H.size();++i)
    {
        cout<<H[i]->freq<<" ";
    }
    cout<<endl;
}

void buildT(vector<Hnode*>& H)
{
    Hnode* a,*b,*t,*tmp;
    if (H.size()==1) return;
    while(true)
    {
        a = H[H.size()-1];
        H.pop_back();
        b = H[H.size()-1];
        H.pop_back();
        t = new Hnode();
        t->freq = (a->freq) + (b->freq);
        t->c = '0';
        
        if (a->freq <= b->freq)
        {
            t->l = b;
            t->r = a;
        }
        else
        {
            t->l = a;
            t->r = b;
        }
        
        // now we will push node into vector
        H.push_back(t);
        if (H.size()==1) break;
    }
}

void printHuff(Hnode* T,string s)
{
    if (T->l ==NULL && T->r == NULL)
    {
        cout<<T->c<<" "<<T->freq<<" "<<s<<"\n";
        return;
    }
    string t1 = s+'0';
    printHuff(T->l,t1);
    string t2 = s+'1';
    printHuff(T->r,t2);
}

int main()
{
    vector <Hnode*> H;
    char a;int f;
    // we'll stop taking input if a == '-'
    Hnode* tmp;
    while(true)
    {
        cin>>a;
        if (a=='-') break;
        cin>>f;
        tmp = new Hnode();
        tmp->c = a;tmp->freq = f;
        H.push_back(tmp);
    }

    sort(H.begin(),H.end(),func);
    //building huffman tree
    buildT(H);
    string s = "";
    printHuff(H[0],s);    

    return 0;
}