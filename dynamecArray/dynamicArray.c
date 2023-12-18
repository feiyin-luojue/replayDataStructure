#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicArray.h"

#define DEFAULT_SIZE 10

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
};


/* 动态数组的初始化 */
int dynamicArrayInit(dynamicArray *pArray, int capacity)
{
    if (pArray == NULL )
    {
        return NULL_PTR;
    }
    /* 避免传入非法值 */
    if (capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }
    pArray->data = (dynamicArray*)malloc(sizeof(ELEMENTTYPE) * capacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);

    pArray->len = 0;
    pArray->capacity = capacity;

    return ON_SUCCESS;
}

/* 动态数组插入数据(默认插到数组的末尾) */
int dynamicArrayInsertData()
{

}

/* 动态数组插入数据(在指定位置插入) */
int dynamicArrayAppointPosInsertData(dynamicArray *pArray, int pos, ELEMENTTYPE val);

/* 动态数组修改指定位置的数据 */
int dynamicArrayModfyAppointPosData(dynamicArray *pArray, int pos, ELEMENTTYPE set);

/* 动态数组删除数据（默认情况下删除最后末尾的数据） */
int dynamicArrayDeleteData(dynamicArray *pArray);

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointPosData(dynamicArray *pArray, int pos);

/* 动态数组删除指定位置数据 */
int dynamicArrayDeleteAppointData(dynamicArray *pArray, ELEMENTTYPE val);

/* 动态数组销毁 */
int dynamicArrayDestory(dynamicArray *pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity);
