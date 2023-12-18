#include <stdio.h>
#include "dynamicArray.c"

#define BUFFER_SIZE 20
#define DEFAULT_NUM 5

typedef struct stuInfo
{
    int age;
    char sex;
} stuInfo;

int main(int argc, char const *argv[])
{
    /*  静态数组
        1.不够灵活
        2.可能会浪费空间
    */

   //初始化
    dynamicArray array;
    dynamicArrayInit(&array, BUFFER_SIZE);
#if 0
    //插入数据
    dynamicArrayInsertData(&array, 3);
    for (int idx = 0; idx < DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, 21);        
    }

    int size = 0;

    /* 获取动态数组的大小 */
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    int val = 0;
    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, &val);
        printf("val:%d\n", val);
    }
    putchar(10);

    /* 删除末尾 */
    dynamicArrayDeleteData(&array);

    /* 获取动态数组的大小 */
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);

    for (int idx = 0; idx < size; idx++)
    {
        dynamicArrayGetAppointPosVal(&array, idx, &val);
        printf("val:%d\n", val);
    }
    putchar(10);
#endif

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

    // dynamicArrayInsertData(%array, stu1);
    // dynamicArrayInsertData(%array, stu1);
    // dynamicArrayInsertData(%array, stu1);

    return 0;
}
