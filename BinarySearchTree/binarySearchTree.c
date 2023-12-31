#include "binarySearchTree.h"
#include <stdlib.h>
#include <string.h>
#include "DoubleLinkListQueue/doubleLinkListQueue.h"

/* 状态码 */
enum STATUS_CODE
{
    NOT_FIND = -1,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

/* 两个值比较大小 */
static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2);
static BSTreeNode *createBSTreeNewNode(ELEMENTTYPE val, BSTreeNode *parentNode);
/* 根据指定的值获取二叉 */
static BSTreeNode * baseAppointValGetBstreeNode(BinarySearchTree *pBstree, ELEMENTTYPE val);
/* 二叉搜索树删除指定的结点 */
static binarySearchTreeDeleNode(BinarySearchTree *pBstree, BSTreeNode *node);
/* 判断二叉搜索树度为2 */
static int binarySearchTreeNodeHasTwochildrens(BSTreeNode *node);
/* 判断二叉搜索树度为1 */
static int binarySearchTreeNodeHasOnechildrens(BSTreeNode *node);
/* 判断二叉搜索树度为0 */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node);
/* 二叉搜索树的前序遍历 */
static int preOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
/* 二叉搜索树的中序遍历 */
static int preInOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);
/* 二叉搜索树的后序遍历 */
static int prePostOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node);

/* 获取当前节点的前驱结点 */
static BSTreeNode * bstreeNodePreDecessor(BSTreeNode *node);
/* 获取当前节点的后继结点 */
static BSTreeNode * bstreeNodeSuccessor(BSTreeNode *node);


/* 二叉搜索树的初始化 */
int binarySearchTreeInit(BinarySearchTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (printFunc)(ELEMENTTYPE val))
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

/* 判断二叉搜索树度为2 */
static int binarySearchTreeNodeHasTwochildrens(BSTreeNode *node)
{
    return (node->left != NULL) && (node->right != NULL);
}
/* 判断二叉搜索树度为1 */
static int binarySearchTreeNodeHasOnechildrens(BSTreeNode *node)
{
    return ((node->left == NULL) && (node->right != NULL)) || ((node->left != NULL) && (node->right == NULL));
}
/* 判断二叉搜索树度为0 */
static int binarySearchTreeNodeIsLeaf(BSTreeNode *node)
{
    return (node->left == NULL) || (node->right != NULL);
}

/* 获取当前节点的前驱结点 */
static BSTreeNode * bstreeNodePreDecessor(BSTreeNode *node)
{
    if (node->left)
    {
        /* 前驱结点是左子树的右子树的右子树 */
        BSTreeNode *travelNode = node->left;
        while (travelNode != NULL)
        {
            travelNode = travelNode->right;
        }
        return travelNode;
    }

    /* 程序到这个地方 说明一定没有左子树。那就需要向父结点找 */
    while (node->parent && node == node->parent->left)
    {
        node = node->parent;
    }
    
    return node->parent;
}

/* 获取当前节点的后继结点 */
static BSTreeNode * bstreeNodeSuccessor(BSTreeNode *node)
{
    /* 后继节点是比它大的所有孩子中最小的，
    或者第一个比它大的parent（它的第一个右parent）*/
    if (node->right)
    {
        /* 后继结点是右子树的左子树的左子树 */
        BSTreeNode *travelNode = node->right;
        while (travelNode != NULL)
        {
            travelNode = travelNode->left;
        }
        return travelNode;
    }

    /* 程序到这个地方 说明一定没有右子树。那就需要向父结点找 */
    while (node->parent && node == node->parent->right)
    {
        node = node->parent;
    }
    
    return node->parent;
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

/* 前序遍历 */
static int preOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    pBstree->printFunc(node->data);
    preInOrderTravel(pBstree, node->left);
    preInOrderTravel(pBstree, node->right);
}
/* 二叉搜索树的前序遍历 */
int binarySearchTreePreOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    preOrderTravel(pBstree, pBstree->root);
    return ret;
}

static int preInOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    preInOrderTravel(pBstree, node->left);
    pBstree->printFunc(node->data);
    preInOrderTravel(pBstree, node->right);
}
/* 二叉搜索树的中序遍历 */
int binarySearchTreeInOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    preInOrderTravel(pBstree, pBstree->root);
    return ret;
}

static int prePostOrderTravel(BinarySearchTree *pBstree, BSTreeNode *node)
{
    int ret = 0;
    if (node == NULL)
    {
        return ret;
    }
    preInOrderTravel(pBstree, node->left);
    preInOrderTravel(pBstree, node->right);
    pBstree->printFunc(node->data);
}
/* 二叉搜索树的后序遍历 */
int binarySearchTreePostOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    prePostOrderTravel(pBstree, pBstree->root);
    return ret;
}

/* 二叉搜索树的层序遍历 */
int binarySearchTreeLevelOrderTravel(BinarySearchTree *pBstree)
{
    int ret = 0;
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 1.根节点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);

    /* 2.判断队列是否为空 */
    BSTreeNode *nodeVal = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void**)&nodeVal);
        #if 0
        printf("data:%d\n", nodeVal->data);
        #else
        pBstree->printFunc(nodeVal->data);
        #endif
        doubleLinkListQueuePop(pQueue);

        /* 将左子树入队 */
        if (nodeVal->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->left);
        }

        /* 将右子树入队 */
        if (nodeVal->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, nodeVal->right);
        }
    }
    
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);

    return ret;
}

/* 根据指定的值获取二叉搜索树的结点 */
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
    return baseAppointValGetBstreeNode(pBstree, val) == NULL ? 0 : 1;
}

static binarySearchTreeDeleNode(BinarySearchTree *pBstree, BSTreeNode *node)
{
    if (node)
    {
        return NULL_PTR;
    }
    /* 删除度为2的结点：找到前驱（后继）结点，复制该前驱（后继）结点的值给要删除的结点，再删除该前驱（后继） */
    /* 找到前驱结点 */
    BSTreeNode *preNode = bstreeNodePreDecessor(node);
    node->data = preNode->data;
    node = preNode;

    /* 程序执行到这里，要删除的结点要么度为1 要么度为0 */
    /* 删除度为1的结点：过继本结点的孩子结点给本结点的父结点，让孩子结点成为本结点的父结点的对应孩子 */
    BSTreeNode *child = node->left == !NULL ? node->left : node->right;   
    if (child)   
    {
        child->parent = node->parent;
        if (!node->parent)
        {
            /* 度为1 且 它不是根结点 */
            if (node = node->parent->left)
            {
                node->parent->left = child;
            }
            if (node = node->parent->right)
            {
                node->parent->right = child;
            }
        }
        else
        {
            child->parent = NULL;
            pBstree->root = child;
        }
    } 
    else
    {   /* 删除叶子结点：直接删除，并且将父节点对应的指针置空 */
        if (node->parent)
        {
            /* 不是根节点 */
            if (node = node->parent->left)
            {
                node->parent->left = NULL;
            }
            if (node = node->parent->right)
            {
                node->parent->right = NULL;
            }
        }
    }
    free(node);
    node = NULL;
    return ON_SUCCESS;
}
/* 二叉搜索树删除数据 */
int binarySearchTreeDele(BinarySearchTree *pBstree, ELEMENTTYPE val)
{
    /* */

    return binarySearchTreeDeleNode(pBstree, val);
    /* 删除度为2的结点：找到前驱（后继）结点，复制该前驱（后继）结点的值给要删除的结点，再删除该前驱（后继） */
    /* 删除度为1的结点：过继本结点的孩子结点给本结点的父结点，让孩子结点成为本结点的父结点的对应孩子 */
    /* 删除度为0的结点：直接删除，并且将父节点对应的指针置空 */
}

/* 二叉树的高度 */
int binarySearchTreeGetHeight(BinarySearchTree *pBstree, int *pBstHeigh)
{
    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);

    /* 1.根节点入队 */
    doubleLinkListQueuePush(pQueue, pBstree->root);

    int height = 0;
    /* 每一层的结点数 */
    int levelSize = 1;

    /* 2.判断队列是否为空 */
    BSTreeNode *travelNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void**)&travelNode);
        doubleLinkListQueuePop(pQueue);
        levelSize--;

        /* 左子树不为空 */
        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->left);
        }

        /* 右子树不为空 */
        if (travelNode->left != NULL)
        {
            doubleLinkListQueuePush(pQueue, travelNode->right);
        }

        /* 树的当前层节点遍历结束 */
        if (levelSize == 0)
        {
            height++;
            doubleLinkListQueueGetSize(pQueue, &levelSize);
        }
        *pBstHeigh = height;

        doubleLinkListQueueDestroy(pQueue);


    }
    
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
}

/* 二叉搜索树的销毁 */
int binarySearchTreeDestory(BinarySearchTree *pBstree)
{
    if (!pBstree)
    {
        return NULL_PTR;
    }

    DoubleLinkListQueue *pQueue = NULL;
    doubleLinkListQueueInit(&pQueue);   
    doubleLinkListQueuePush(pQueue, pBstree->root);

    BSTreeNode *travelNode = NULL;
    while (!doubleLinkListQueueIsEmpty(pQueue))
    {
        doubleLinkListQueueTop(pQueue, (void **)&travelNode);
        doubleLinkListQueuePop(pQueue);
    }

    if (travelNode->left)
    {
        doubleLinkListQueuePush(pQueue, travelNode->left);
    }

    if (travelNode->right)
    {
        doubleLinkListQueuePush(pQueue, travelNode->right);
    }
    
    /* 释放队列 */
    doubleLinkListQueueDestroy(pQueue);
    
    if (pBstree)
    {
        free(pBstree);
        pBstree = NULL;
    }

    return ON_SUCCESS;
}