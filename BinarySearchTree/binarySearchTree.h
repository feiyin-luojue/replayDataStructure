#ifndef __BINARY_SEARCH_TREE_
#define __BINARY_SEARCH_TREE_

#define ELEMENTTYPE void*

typedef struct BSTreeNode
{
    ELEMENTTYPE data;
    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
} BSTreeNode;

typedef struct BinarySearchTree
{
    struct BSTreeNode *root;
    int size;
    int hight;

} BinarySearchTree;

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree);

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(BinarySearchTree **pBstree, ELEMENTTYPE val);


#endif