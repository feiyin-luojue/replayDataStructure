#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 16
#define DEFAULT_SIZE 2


/* 结构体 */
/* 1.什么叫结构体：将不同类型的属性封装成一个类型 */
/* 2.怎么定义结构体？ */
typedef struct stuInfo
{
    int age;
    int hight;
    int weight;
    char sex;
    char name[BUFFER_SIZE];
    char *address;
#if 0
    char clothing;
    cahr shoes;
    char phones;
#endif
} stuInfo;

typedef struct stuInfo stuInfo;

/* 结构体会默认进行结构对齐：读取速度快，但浪费空间 */   //什么叫变长结构体

/* 函数：结构体做函数参数 */
/* 值传递 */
#if 0
int printStruct(stuInfo stu)
{
    /* 栈空间很小，不允许超过8M */
    stu.age = 100;
    printf("stu.age:%d\t, stu.weight:%d\t, stu.sex:%c\t, stu.hight:%d\t, stu.name:%s\n",
                stu.age, stu.weight, stu.sex, stu.hight, stu.name);
    return 0;
}
#else
/* 传入参数： 不要改变值 */
int printStruct(const stuInfo *stu)
{
    /* 结构体必须用指针*/
    int ret = 0;
    int len = sizeof(stu);
    printf("len:%d\n", len);

    // printf("stu.age:%d\t, stu.weight:%d\t, stu.sex:%c\t, stu.hight:%d\t, stu.name:%s\n",
    //             stu.age, stu.weight, stu.sex, stu.hight, stu.name);
    return 0;
}
#endif

/* 结构体数组做函数参数 */
int printfStructBuffer(stuInfo *stu, int stuSize)
{
    for (int idx = 0; idx < stuSize; idx++)
    {
        printf("stu.age:%d\t, stu.weight:%d\t, stu.sex:%c\t, stu.hight:%d\t, stu.name:%s\n",
                stu[idx].age, stu[idx].weight, stu[idx].sex, stu[idx].hight, stu[idx].name);
    }
}


int main(int argc, char const *argv[])
{

    /* 3.怎么使用结构体 */
    struct stuInfo stu;
    memset(&stu, 0, sizeof(stu));
#if 0
    stu.age = 10;
    stu.weight = 50;
    stu.sex = 'm';
    stu.hight = 170;
    strcpy(stu.name, "zhangsan");
    printf("stu.age:%d\t, stu.weight:%d\t, stu.sex:%c\t, stu.hight:%d\t, stu.name:%s\n",
                stu.age, stu.weight, stu.sex, stu.hight, stu.name);

/* 4.结构体大小 */
    int len = sizeof(stu);
    printf("len:%d\n", len);

/* 5.结构体数组 */
/* 数组：1.一块连续的地址
        2.存放的是同一种数据类型
*/
    stuInfo buffer[DEFAULT_SIZE];
    buffer[0].age = 10;
    buffer[0].weight = 30;
    buffer[0].sex = 'm';
    buffer[0].hight = 130;
    strncpy(buffer[0].name, "zhangsan", sizeof(buffer[0].name) - 1);

    buffer[1].age = 20;
    buffer[1].weight = 50;
    buffer[1].sex = 'f';
    buffer[1].hight = 160;
    strncpy(buffer[1].name, "wangwu", sizeof(buffer[1].name) - 1);
   
    printfStructBuffer(buffer, sizeof(buffer[0]));

#if 0
    printf("buffer[0].age:%d\t, buffer[0].weight:%d\t, buffer[0].sex:%c\t, buffer[0].hight:%d\t, buffer[0].name:%s\n",
            buffer[0].age, buffer[0].weight, buffer[0].sex, buffer[0].hight, buffer[0].name);
    printf("buffer[1].age:%d\t, buffer[1].weight:%d\t, buffer[1].sex:%c\t, buffer[1].hight:%d\t, buffer[1].name:%s\n",
            buffer[1].age, buffer[1].weight, buffer[1].sex, buffer[1].hight, buffer[1].name);
#endif

#endif

#if 0
    /* 结构体指针 */
    stu.age = 10;
    stu.weight = 30;
    stu.sex = 'm';
    stu.hight = 130;
    strcpy(stu.name, "zhangsan");

    /* 回顾指针 */
    int a = 5;
    int *p = &a;

    /* 结构体指针 */
    stuInfo * info = &stu;
    /* 结构体指针 读数据 或者写数据 都是用-> */
    info->age = 30;

    //printf("info->age:%d\n", info->age);



#endif

#if 1
    stu.age = 10;
    stu.weight = 30;
    stu.sex = 'm';
    stu.hight = 130;
    strcpy(stu.name, "zhangsan");

    /* 结构体里有指针必须分配空间 */
    stu.address = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    if (stu.address == NULL)
    {
        return -1;
    }
    strcpy(stu.address, "china");

#endif
    printf("size:%ld\n", sizeof(stuInfo));


    return 0;
}
