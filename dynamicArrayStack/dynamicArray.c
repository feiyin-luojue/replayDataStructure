#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};


#define DEFAULT_SIZE    10

/* 静态函数前置声明 : 静态函数一定要前置声明 */
static int expandDynamicCapacity(dynamicArray *pArray);
static int shrinkDynamicCapacity(dynamicArray *pArray);

/* 堆空间申请成功判断 */
int DetermineMallocNull(const void *pMallocAddress)
{
    if (pMallocAddress == NULL)
    {
        return MALLOC_ERROR;
    }
    return ON_SUCCESS;
}

/* 动态数组判空 */
int dynamicArrayDetermineNull(const dynamicArray *pArray)
{
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    return ON_SUCCESS;
}

/* 容量参数合法性判断 */
int determineCapacityLegitimacy(int *capacity)
{
    if (capacity < 0)
    {
        *capacity = DEFAULT_SIZE;
    }
    return ON_SUCCESS;
}

/* 位置参数合法性判断 */
int determinePosLegitimacy(const dynamicArray *pArray, const int pos)
{
    if (pos < 0 || pos >= pArray->len)
    {
        return INVALID_ACCESS;
    }
    return ON_SUCCESS;
}

/* 释放指针空间*/
int PutPtrToNull(void *ptr)
{
    if (!ptr)
    {
        free(ptr);
        ptr = NULL;
    }
    return ON_SUCCESS;
}

/* 动态数组的初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);
    
    /* 避免传入非法值 */
    determineCapacityLegitimacy(&capacity);

    /* 分配空间 */
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    
    /* 空间申请成功判断 */
    DetermineMallocNull(pArray->data);

    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);
    /* 初始化动态数组的参数属性 */
    pArray->len = 0;
    pArray->capacity = capacity;

    return ON_SUCCESS;
}

/* 动态数组插入数据(默认插到数组的末尾) */
int dynamicArrayInsertData(dynamicArray *pArray, ELEMENTTYPE val)
{
    return dynamicArrayAppointPosInsertData(pArray, pArray->len, val);
}


/* 动态数组扩容 */
static int expandDynamicCapacity(dynamicArray *pArray)
{
    int ret = 0;
    
    int needExpandCapacity = pArray->capacity + (pArray->capacity >> 1);

    /* 备份指针 */
    ELEMENTTYPE * tmpPtr = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needExpandCapacity);
    
    DetermineMallocNull(pArray->data);

    /* 把之前的数据全部拷贝过来 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }

    /* 释放以前的内存 避免内存泄漏 */
    if (tmpPtr != NULL)
    {
        free(tmpPtr);
        tmpPtr = NULL;
    }

    /* 更新动态数组的容量 */
    pArray->capacity = needExpandCapacity;

    return ret;
}

/* 动态数组插入数据, 在指定位置插入 */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    /* 判断位置的合法性 */
    determinePosLegitimacy(pArray, pos);
    
    #if 1
    /* 数组扩容的临界值是: 数组大小的1.5倍 >= 数组容量 */
    if ((pArray->len + (pArray->len >> 1)) >= pArray->capacity)
    {
        /* 开始扩容 */
        expandDynamicCapacity(pArray);
    }
    #else
    if (pArray->len == pArray->capacity)
    {
        /* 开始扩容 */
        expandDynamicCapacity(pArray);
    }
    #endif
   
#if 1
    /* 数据后移 流出pos位置插入 */
    for (int idx = pArray->len; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }
#else
    for (int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx + 1] = pArray->data[idx];
    }
#endif
    /* 找到对应的值 写入到数组中 */
    pArray->data[pos] = val;
    /* 数组的大小加一 */
    (pArray->len)++;

    return ON_SUCCESS;
}


/* 动态数组修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray *pArray, int pos, ELEMENTTYPE val)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    /* 判断位置的合法性 */
    determinePosLegitimacy(pArray,pos);

    /* 更新位置的数据 */
    pArray->data[pos] = val;

    return ON_SUCCESS;
}

/* 动态数组删除数据(默认情况下删除最后末尾的数据) */
int dynamicArrayDeleteData(dynamicArray *pArray)
{
    dynamicArrayDeleteAppointPosData(pArray, pArray->len - 1);
}

/* 动态数组缩容 */
static int shrinkDynamicCapacity(dynamicArray *pArray)
{
    int needShrinkCapacity = pArray->capacity - (pArray->capacity >> 1);

    ELEMENTTYPE * tmpPtr = pArray->data;
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * needShrinkCapacity);
    DetermineMallocNull(pArray->data);

    /* 拷贝之前的数据到新的空间 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = tmpPtr[idx];
    }
    
    /* 释放内存空间 避免内存泄漏 */
    PutPtrToNull(tmpPtr);

    /* 更新容量 */
    pArray->capacity = needShrinkCapacity;
    return ON_SUCCESS;
}

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    /* 位置合法性判断 */
    determinePosLegitimacy(pArray, pos);

    /* 缩容 */
    if (pArray->len < pArray->capacity >> 1)
    {
        shrinkDynamicCapacity(pArray);
    }   

    /* 数据前移 */
    for (int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }
    /* 更新数组的大小 */
    (pArray->len)--;
    return ON_SUCCESS;
}

/* 动态数组删除指定的元素 */
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ELEMENTTYPE val)
{
    /* todo... */
#if 0
    int idx = 0;
    for (idx; idx < pArray->len; idx++)
    {
        if (val == pArray->data[idx])
        {
            dynamicArrayDeleteAppointPosData(pArray, idx);
            /* 从头开始 */
            idx = 0;
        }
    }
#else   
    for (int idx = pArray->len - 1; idx >= 0; idx--)
    {
        if (val == pArray->data[idx])
        {
            dynamicArrayDeleteAppointPosData(pArray, idx);
        }
    }
#endif
    return ON_SUCCESS;
}

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray *pArray)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    /* 指针置空 */
    PutPtrToNull(pArray->data);

    return ON_SUCCESS;
}

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    /* 解引用 */
    if (pSize != NULL)
    {
        *pSize = pArray->len;
    }
    return ON_SUCCESS;
}

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    if (pCapacity != NULL)
    {
        *pCapacity = pArray->capacity;
    }
    return ON_SUCCESS;
}

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal)
{
    /* 动态数组判空 */
    dynamicArrayDetermineNull(pArray);

    /* 判断位置的合法性 */
    determinePosLegitimacy(pArray, pos);
    
    if (pVal)
    {
        *pVal = pArray->data[pos];
    }

    return ON_SUCCESS;
}
