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
    //int hight;
    /* 钩子 函数比较器 */
    int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 钩子 函数包装器 实现自定义打印函数接口 */
    int (*printFunc)(ELEMENTTYPE val);
} BinarySearchTree;

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (printFunc)(ELEMENTTYPE val));

/* 二叉搜索树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定的元素 */
int binarySearchTreeIsContainAppointVal(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历 */
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLevelOrderTravel(BinarySearchTree *pBstree);

/* 二叉搜索树是否包含指定的元素 */
int binarySearchTreeIsContainAppointVal(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的删除 */
int binarySearchTreeDele(BinarySearchTree *pBstree);

/* 二叉树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pBstree, int *pBstHeigh);

/* 二叉搜索树的销毁 */
int binarySearchTreeDestory(BinarySearchTree *pBstree);

#endif