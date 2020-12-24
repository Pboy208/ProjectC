#include<stdio.h>
#ifndef _TREE_H_
#define _TREE_H_

typedef struct 
{
    char key[20];
    int value;
}mapping;

struct TreeNode {
  mapping data;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode* tree;

tree createNullTree();
tree createLeaf(mapping x);
tree createTree(mapping x, tree l, tree r);

int  isNullTree(tree t);
int isLeaf(tree t);

tree left(tree t);
tree right(tree t);
char* value(tree t);

int sizeOfTree(tree t);
// mapping sumOfTree(tree t);
char* treeToString(tree t);

struct TreeNode* leftMost(tree t);
struct TreeNode* rightMost(tree t);

tree addToLeftMost(tree t, mapping x);
tree addToRightMost(tree t, mapping x); 

tree insertBST(tree t, mapping x);
// xoa nut goc va tra ve cay BST sau khi da xoa
tree removeRootBST(tree t);
tree removeBST(tree, char* x);
struct TreeNode *searchBST(tree t, char* x);

void inorderprint(tree tree);
void inordersave(tree root,FILE *ptr);


#endif
