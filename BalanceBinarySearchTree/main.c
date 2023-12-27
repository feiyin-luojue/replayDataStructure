#include <stdio.h>
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
    /* */
    BalanceBinarySearchTree * BST = NULL;
    balanceBinarySearchTreeInit(&BST, compareBasicDataFunc, printBasicData);

    int buffer[BUFFER_SIZE] = {56, 28, 75, 73, 77, 13, 7, 26, 100, 12};

    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        balanceBinarySearchTreeInsert(BST, (void*)&buffer[idx]);
    }
    /* 获取二叉搜索树的结点个数 */
    int size = 0;
    balanceBinarySearchTreeGetNodeSize(BST, &size);
    printf("size:%d\n", size);
    /* 获取二叉搜索树的高度 */
    int heigh = 0;
    balanceBinarySearchTreeGetHeight(BST, &heigh);
    printf("heigh:%d\n", heigh);

    // /* 中序遍历 */
    // binarySearchTreeinOrderTravel(BST);
    // putchar(10);

    // /* 层序遍历 */
    // binarySearchTreeLevelOrderTravel(BST);
    // putchar(10);



    return 0;
}
