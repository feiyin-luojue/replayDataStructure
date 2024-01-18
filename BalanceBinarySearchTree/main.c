#include <stdio.h>
#include <stdlib.h>
#include "balanceBinarySearchTree.h"

#define BUFFER_SIZE 10

/* 测试二叉搜索树 */

int compareBasicDataFunc(void * arg1, void *arg2)
{
    int val1 = *(int *)arg1;
    int val2 = *(int *)arg2;

    return val1 - val2;

}

int printBasicData(void *arg)
{
    int ret = 0;
    int val = *(int *)arg;
    printf("val:%d\t", val);

    return ret;
}

int main(int argc, char const *argv[])
{
    balanceBinarySearchTree * BST = NULL;
    balanceBinarySearchTreeInit(&BST, compareBasicDataFunc, printBasicData);

    int buffer[BUFFER_SIZE] = {13, 14, 15, 12, 11, 17, 16, 8, 9, 1};

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        balanceBinarySearchTreeInsert(BST, (void*)&buffer[idx]);
    }
    /* 获取二叉搜索树的结点个数 */
    int size = 0;
    balanceBinarySearchTreeGetNodeSize(BST, &size);
    printf("结点个数size:%d\n", size);
    /* 获取二叉搜索树的高度 */
    int heigh = 0;
    balanceBinarySearchTreeGetHeight(BST, &heigh);
    printf("树高heigh:%d\n", heigh);

    /* 中序遍历 */
    printf("中序遍历： ");
    balanceBinarySearchTreeInOrderTravel(BST);
    putchar(10);

    /* 层序遍历 */
    printf("层序遍历： ");
    balanceBinarySearchTreeLevelOrderTravel(BST);
    putchar(10);

    /* 后序遍历 */
    printf("后序遍历： ");
    balanceBinarySearchTreePostOrderTravel(BST);
    putchar(10);

    /* 销毁树 */
    balanceBinarySearchTreeDestroy(BST);




    return 0;
}
