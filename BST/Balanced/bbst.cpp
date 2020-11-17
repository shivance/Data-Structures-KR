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

void leftR(bstnode* &BST)
{
	bstnode* newBST = BST->rc;
	bstnode* LOR = BST->rc->lc;
	
	newBST->lc = BST;
	newBST->lc->rc = LOR;

	newBST->lc->h = max(newBST->lc->rc->h,newBST->lc->rc->h);
	newBST->h = max(newBST->lc->h,newBST->rc->h);
	BST = newBST;
}

void rightR(bstnode* &BST)
{
	bstnode* newBST = BST->lc;
	bstnode* ROLs = BST->lc->rc;

	newBST->rc = BST;
	newBST->rc->lc  = ROL;
	newBST->lc->h = max(newBST->rc->lc->h,newBST->rc->lc->h);
	newBST->h = max(newBST->lc->h,newBST->rc->h);
	BST = newBST;
}


