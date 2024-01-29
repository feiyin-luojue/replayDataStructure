#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_

#include "common.h"
// #define ELEMENTTYPE int

typedef struct AVLTreeNode
{
    ELEMENTTYPE data;
    /* 结点维护一个高度属性 */
    int height;
    struct AVLTreeNode *left;        /* 左子树 */
    struct AVLTreeNode *right;       /* 右子树 */
    #if 1
    struct AVLTreeNode *parent;      /* 父结点 */
    #endif
} AVLTreeNode;

typedef struct balanceBinarySearchTree
{   
    /* 根结点 */
    AVLTreeNode * root;
    /* 树的结点个数 */
    int size;

    /* 钩子🪝函数比较器 放到结构体内部. */
    int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 钩子🪝函数 包装器实现自定义打印函数接口. */
    int (*printFunc)(ELEMENTTYPE val);

#if 0
    /* 把队列的属性 放到树里面 */
    DoubleLinkListQueue *pQueue;
#endif

} balanceBinarySearchTree;

/* 二叉搜索树的初始化 */
int balanceBinarySearchTreeInit(balanceBinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val));

/* 二叉搜索树的插入 */
int balanceBinarySearchTreeInsert(balanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树是否包含指定的元素 */
int balanceBinarySearchTreeIsContainAppointVal(balanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的前序遍历 */
int balanceBinarySearchTreePreOrderTravel(balanceBinarySearchTree *pBstree);

/* 二叉搜索树的中序遍历 */
int balanceBinarySearchTreeInOrderTravel(balanceBinarySearchTree *pBstree);

/* 二叉搜索树的后序遍历 */
int balanceBinarySearchTreePostOrderTravel(balanceBinarySearchTree *pBstree);

/* 二叉搜索树的层序遍历 */
int balanceBinarySearchTreeLevelOrderTravel(balanceBinarySearchTree *pBstree);

/* 获取二叉搜索树的结点个数 */
int balanceBinarySearchTreeGetNodeSize(balanceBinarySearchTree *pBstree, int *pSize);

/* 获取二叉搜索树的高度 */
int balanceBinarySearchTreeGetHeight(balanceBinarySearchTree *pBstree, int *pHeight);

/* 二叉搜索树的删除 */
int balanceBinarySearchTreeDelete(balanceBinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的销毁 */
int balanceBinarySearchTreeDestroy(balanceBinarySearchTree *pBstree);

/* 判断二叉搜索树是否是完全二叉树 */
int balanceBinarySearchTreeIsComplete(balanceBinarySearchTree *pBSTree);

#endif  //__BINARY_SEARCH_TREE_H_