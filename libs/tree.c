#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

tree createNullTree()
{
  return (tree)NULL;
}

tree createTree(mapping x, tree l, tree r)
{
  tree t = (tree)malloc(sizeof(struct TreeNode));
  t->data = x;
  t->left = l;
  t->right = r;
  return t;
}

tree createLeaf(mapping x)
{
  return createTree(x, createNullTree(), createNullTree());
}

int isNullTree(tree t)
{
  return (t == NULL);
}

int isLeaf(tree t)
{
  return ((t != NULL) &&
          (t->left == NULL) &&
          (t->right == NULL));
}

int sizeOfTree(tree t)
{
  if (isNullTree(t))
    return 0;
  else
    return (1 + sizeOfTree(t->left) + sizeOfTree(t->right));
}

char *treeToString(tree t)
{
  char *result;
  char *left;
  char *right;

  if (isNullTree(t))
  {
    result = (char *)malloc(4);
    strcpy(result, "Nil");
    return result;
  }
  else
  {
    left = treeToString(t->left);
    right = treeToString(t->right);

    result = (char *)malloc(40 + strlen(left) + strlen(right));
    sprintf(result, "node(%d,%s,%s)", t->data, left, right);
    free(left);
    free(right);
    return result;
  }
}

tree left(tree t)
{
  if (isNullTree(t))
    return NULL;
  else
    return t->left;
}

tree right(tree t)
{
  if (isNullTree(t))
    return NULL;
  else
    return t->right;
}

char *value(tree t)
{
  if (isNullTree(t))
    return NULL;
  else
    return t->data.key;
}

struct TreeNode *leftMost(tree t)
{
  struct TreeNode *n = t;

  if (isNullTree(t))
    return NULL;
  while (!isNullTree(left(n)))
    n = left(n);
  return n;
}

struct TreeNode *rightMost(tree t)
{
  struct TreeNode *n = t;

  if (isNullTree(t))
    return NULL;
  while (!isNullTree(right(n)))
    n = right(n);
  return n;
}

tree addToLeftMost(tree t, mapping x)
{
  tree n = leftMost(t);

  if (isNullTree(t))
    return createLeaf(x);
  else
  {
    n->left = createLeaf(x);
    return t;
  }
}

tree addToRightMost(tree t, mapping x)
{
  tree n = rightMost(t);

  if (isNullTree(t))
    return createLeaf(x);
  else
  {
    n->right = createLeaf(x);
    return t;
  }
}

int height(tree t)
{
  if (t == NULL)
    return 0;
  else
  {
    int l = height(t->left);
    int r = height(t->right);
    if (l > r)
      return (l + 1);
    else
      return (r + 1);
  }
}

int leavesCount(tree t)
{
  if (t == NULL)
    return 0;
  if (t->left == NULL && t->right == NULL)
    return 1;
  else
    return leavesCount(t->left) + leavesCount(t->right);
}

int innerNodeCount(tree t)
{
  return sizeOfTree(t) - leavesCount(t);
}

mapping rightChildCount(tree t)
{
  // TODO
}

struct TreeNode *searchBST(tree t, char *x)
{
  if (isNullTree(t))
    return NULL;

  if (strcmp(value(t), x) == 0)
    return t;
  else if (strcmp(value(t), x) < 0)
    return searchBST(right(t), x);
  else
    return searchBST(left(t), x);
}

tree insertBST(tree t, mapping x)
{
  if (isNullTree(t))
    return createLeaf(x);

  if (strcmp(value(t), x.key) == 0)
  { 
    return t;
  }
  else if (strcmp(value(t), x.key) > 0)
  {
    t->left = insertBST(t->left, x);
    return t;
  }
  else
  {
    t->right = insertBST(t->right, x);
    return t;
  }
}
// xoa nut goc va tra ve cay BST sau khi da xoa
tree removeRootBST(tree t)
{
  tree p, tmp;

  if (isNullTree(t))
    return NULL;
  // Xoa nut la
  if (isLeaf(t))
  {
    free(t);
    return NULL;
  }
  // Xoa nut co 1 con phai
  if (left(t) == NULL)
  {
    tmp = right(t);
    free(t);
    return tmp;
  }
  // Xoa nut co 1 con trai
  if (right(t) == NULL)
  {
    tmp = left(t);
    free(t);
    return tmp;
  }
  // Xoa nut co hai con
  p = t;
  tmp = right(t);
  while (left(tmp) != NULL)
  {
    p = tmp;
    tmp = left(tmp);
  }

  t->data = tmp->data;
  tmp = removeRootBST(tmp);
  if (p == t)
    p->right = tmp;
  else
    p->left = tmp;
  return t;
}

tree removeBST(tree t, char *x)
{
  tree p, tmp;

  if (isNullTree(t))
    return NULL;

  if (strcmp(t->data.key, x) == 0)
    return removeRootBST(t);

  p = NULL;
  tmp = t;

  while ((tmp != NULL) && strcmp(tmp->data.key, x) != 0)
    if (strcmp(tmp->data.key, x) > 0)
    {
      p = tmp;
      tmp = tmp->left;
    }
    else
    {
      p = tmp;
      tmp = tmp->right;
    }

  if (tmp != NULL)
  {
    if (p->left == tmp)
    {
      p->left = removeRootBST(tmp);
    }

    else
    {
      p->right = removeRootBST(tmp);
    }
  }
  return t;
}

// void inorderprint(tree tree)
// {
//   if (tree != NULL)
//   {
//     inorderprint(tree->left);
//     printf("%s %s %d %d %f\n", tree->data.key, tree->data.name,tree->data.elec,tree->data.fashion,tree->data.payment);
//     inorderprint(tree->right);
//   }
// }

// void inordersave(tree root,FILE *ptr)
// {
//   if(root!=NULL)
//   {
//     inordersave(root->left,ptr);
//     fprintf(ptr,"%s %s %d %d %f\n",root->data.key,root->data.name,root->data.elec,root->data.fashion,root->data.payment);
//     inordersave(root->right,ptr);
//   }
// }
//key ~ id