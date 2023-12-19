#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"
#include <string.h>

#define BUFFER_SIZE 20
#define DEFAULT_NUM 3

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo; 

int main()
{
    dynamicArray array;
    /* 初始化 */
    dynamicArrayInit(&array, BUFFER_SIZE);

#if 0   //使用API插入5,6,7
        /* 插入数据 */
        // dynamicArrayInsertData(&array, 3);
        for (long idx = 5; idx < DEFAULT_NUM + 5; idx++)
        {
            dynamicArrayInsertData(&array, (void*)idx);
        }
#endif

#if 0    //手动插入5,6,7
    dynamicArrayInsertData(&array, (void *)5);
    dynamicArrayInsertData(&array, (void *)6);
    dynamicArrayInsertData(&array, (void *)7);
#endif

#if 0    //测试是否插入成功
    printf("array[0]: %ld\n", (long)array.data[0]);
    printf("array[1]: %ld\n", (long)array.data[1]);
    printf("array[2]: %ld\n", (long)array.data[2]);
    //该测试表明插入 567成功
#endif

#if 0   //两种使用API的方法获取指定位置元素数据
        /* 获取动态数组的大小 */
        int size = 0;
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);
    #if 0   /*方法1.使用malloc在堆区为val开辟长整型二级指针long**类型的内存，
                    使用 val 做为地址，
                    将 val 强转为 void* 类型，接收指定位置元素
                    输出 *val    
                    (不能直接long **val = NULL; 会引起段错误)
            */
        long **val = (long**)malloc(sizeof(long*));
        for (int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, (void*)val);
            printf("val:%ld\t\n", (long)*val);
        }    
    #else   /*方法2.使用 long类型的 val 作为地址
                    使用 &val 做为地址，
                    将 &val 强转为 void** 类型，接收指定位置元素
                    输出 val  
            */
        long val = 0;
        for (int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, (void**)&val);
            printf("val:%ld\t\n", val);
        }    
    #endif
#endif

#if 0   //删除最后位置的元素
    /* 删除最后位置的元素 */
    dynamicArrayDeleteData(&array);

    /* 获取动态数组的大小 */
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    long val = 0;
    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void **)&val);
        printf("val:%ld\t\n", val);
    }    
#endif

#if 0   /* 删除指定位置的元素 */   
        int pos = 1;
        dynamicArrayDeleteAppointPosData(&array, pos);

        /* 获取动态数组的大小 */
        int size = 0;
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);

        long val = 0;
        for (int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, (void**)&val);
            printf("val:%ld\t\n", val);
        }    
#endif

#if 0   //将静态数组buffer[]逐个插入动态数组
    long buffer[DEFAULT_NUM] = {1, 2, 3};
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)buffer[idx]);
    }
    
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    long val = 0;
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void *)&val);
        printf("val:%ld\n", val);
    }
#endif

#if 0   //向动态数组写入1-3，使用API接收并打印出来
    for (long idx = 1; idx < DEFAULT_NUM + 1; idx++)
    {
        dynamicArrayInsertData(&array, (void *)idx);    //  后面的参数 不能取地址
    }

    #if 0   //打印前两个数据，该测试说明写入成功
    printf("array0:%ld\n", (long)array.data[0]);        
    printf("array1:%ld\n", (long)array.data[1]);
    #endif

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    void *val = NULL;
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void*)&val);
        printf("val:%ld\n", (long)val);
        printf("array%d:%ld\n", idx, (long)array.data[idx]);
    }
#endif

#if 1   //向动态数组array写入三个结构体（stu1,2,3）,并读取出来
    stuInfo stu1, stu2, stu3;
    memset(&stu1, 0, sizeof(stu1));
    memset(&stu2, 0, sizeof(stu2));
    memset(&stu3, 0, sizeof(stu3));

    stu1.age = 10;
    stu1.sex = 'm';

    stu2.age = 20;
    stu2.sex = 'f';

    stu3.age = 30;
    stu3.sex = 'm';

    stuInfo buffer[DEFAULT_NUM] = {stu1, stu2, stu3};
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&buffer[idx]);
    }

    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    stuInfo *info = NULL;
    for (int idx = 0; idx < DEFAULT_NUM ; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, (void *)&info);
        printf("stu%d.age:%d\tstu%d.sex:%c\n", idx + 1, info->age, idx, info->sex);
    }
#endif

    return 0;
}
