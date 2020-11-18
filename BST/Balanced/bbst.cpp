#include <iostream>
#include <climits>
#include <vector>
#include <queue>
#include <deque>
#include <stack>
using namespace std;

class bstnode
{
public:
    bstnode* lc;
    int data,h;
    bstnode* rc;
    bstnode()
    {
        h = 0;
        lc = rc = NULL;
    }
};

deque<bstnode> nodeCache;

bstnode* newBTnode()
{
    nodeCache.push_back(bstnode());
    bstnode* node = &nodeCache.back();
    return node;
}

trpnode* leftR(bstnode* &BST)
{
	bstnode* newBST = BST->rc;
	bstnode* LOR = newBST->lc;
	
	newBST->lc = BST;
	BST->rc = LOR;

	newBST->lc->h = max(newBST->lc->rc->h,newBST->lc->rc->h);
	newBST->h = max(newBST->lc->h,newBST->rc->h);
	
	return newBST;
}

trpnode* rightR(bstnode* &BST)
{
	bstnode* newBST = BST->lc;
	bstnode* ROL = newBST->rc;

	newBST->rc = BST;
	BST->lc  = ROL;
	
	//newBST->lc->h = max(newBST->rc->lc->h,newBST->rc->lc->h);
	//newBST->h = max(newBST->lc->h,newBST->rc->h);
	
	return newBST;
}


