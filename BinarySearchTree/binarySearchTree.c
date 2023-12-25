#include "binarySearchTree.h"
#include <stdlib.h>

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree)
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
        cmp = val - travelNode->data;
        /* 插入元素 < 遍历到的结点*/
        if (val < travelNode->data)
        {
            travelNode = travelNode->left;
        }
        else if (val > travelNode->data)    /* 插入元素 < 遍历到的结点*/
        {
            travelNode = travelNode->right;
        }
        else 
        {
            /* 插入元素 = 遍历到的结点*/
            return ret;
        }
    }

    if (cmp < 0)
    {
        parentNode->left = (val的结点);
    }
    else (cmp > 0)
    {
        parentNode->right = (val的结点);
    }
    return ret;
}