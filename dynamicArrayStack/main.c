#include <stdio.h>
#include "dynamicArrayStack.h"

#define BUFFER_SIZE 5

int main(int argc, char const *argv[])
{
    dynamicArrayStack stack;
    dynamicArrayStackInit(&stack);
    int buffer[BUFFER_SIZE] = {5, 32, 21, 56, 87};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        dynamicArrayStackPush(&stack, &buffer[idx]);
    }

    int size = 0;
    dynamicArrayStackGetSize(&stack, &size);
    printf("size：%d\n", size);

    int *val = NULL;
    while (!dynamicArrayStackIsEmpty(&stack))
    {
        dynamicArrayStackTop(&stack, (void**)&val);
        dynamicArrayStackPop(&stack);
        printf("val:%d\n", (int)*val);
    }
    
    /* 栈的销毁 */
    //dynamicArrayDestroy(&stack);

    return 0;
}
