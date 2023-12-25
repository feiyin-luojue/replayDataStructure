#include "binarySearchTree.h"
#include <stdlib.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode *parentNode);
/* 根据指定的值获取二叉 */
static BSTreeNode * baseAppointValGetBstreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val);

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2))
{
    int ret = 0;
    BinarySearchTree * bstree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree) * 1);
    if (bstree == NULL)
    {
        return NULL_PTR;
    }
    memset(bstree, 0, sizeof(BinarySearchTree) * 1);
    /* 初始化树 */
    bstree->root = NULL;
    bstree->size = 0;

    bstree->root = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (bstree->root == NULL)
    {
        return NULL_PTR;
    }
    memset(bstree->root, 0, sizeof(BSTreeNode) * 1);

    bstree->root->data = 0;
    bstree->root->parent = NULL;
    bstree->root->left = NULL;
    bstree->root->right = NULL;

    *pBstree = bstree;
    return ret;
}

/* 静态函数前置声明 */
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
#if 0
{
    #if 0
    if (val1 < val2)
    {
        return -1;
    }
    else if (val1 > val2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    #endif
    return val1 - val2;
}
#endif

/* 创建结点 */
static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode *parentNode)
{
    /* 分配根节点 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return (BSTreeNode *)MALLOC_ERROR;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode) * 1);

    newBstNode->data = 0;
    newBstNode->parent = NULL;
    newBstNode->left = NULL;
    newBstNode->right = NULL;
    /* 新结点赋值 */
    newBstNode->data = val;
    newBstNode->parent = parentNode;
    return newBstNode;
}


/* 二叉搜索树的插入 */
int binarySearchTreeInsert(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;

    /* 空树 */
    if (pBstree->size == 0)
    {
        /* 更新树结点 */
        (pBstree->size)++;

        pBstree->root->data = val;
        return ret;
    }

    /* travelNode 指向根结点 */
    BSTreeNode * travelNode = pBstree->root;

    BSTreeNode * parentNode = pBstree->root;

    /* 确定符号：到底放在左边还是右边 */
    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 标记父结点*/
        parentNode = travelNode;
        cmp = compareFunc(val, travelNode->data);
        /* 插入元素 < 遍历到的结点*/
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)    /* 插入元素 < 遍历到的结点*/
        {
            travelNode = travelNode->right;
        }
        else 
        {
            /* 插入元素 = 遍历到的结点*/
            return ret;
        }
    }
    #if 0
    /* 分配根节点 */
    BSTreeNode * newBstNode = (BSTreeNode *)malloc(sizeof(BSTreeNode) * 1);
    if (newBstNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newBstNode, 0, sizeof(BSTreeNode) * 1);

    newBstNode->data = 0;
    newBstNode->parent = NULL;
    newBstNode->left = NULL;
    newBstNode->right = NULL;
    /* 新结点赋值 */
    newBstNode->data = val;
    #else
    BSTreeNode * newBstNode = createBSTreeNewNode(val, parentNode);
    #endif

    /* 挂在左子树 */
    if (cmp < 0)
    {
        parentNode->left = newBstNode;
    }
    else
    {
            /* 挂在右子树 */
        parentNode->right = newBstNode;
    }

    newBstNode->parent = parentNode;

    (pBstree->size)++;
    return ret;
}

/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;

    return ret;
}

/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;

    return ret;
}

/* 二叉搜索树的后序遍历 */
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;

    return ret;
}

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLevelOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;

    return ret;
}

/* 根据指定的值获取二叉 */
static BSTreeNode * baseAppointValGetBstreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    BSTreeNode * travelNode = pBstree->root;
    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = pBstree->compareFunc(val, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            return travelNode;
        }
        return NULL;
    }
}
/* 二叉搜索树是否包含指定的元素 */
int binarySearchTreeIsContainAppointVal(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;

    return ret;
}
