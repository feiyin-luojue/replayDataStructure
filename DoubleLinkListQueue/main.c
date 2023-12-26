#include <stdio.h>
#include "doubleLinkListQueue.h"

#define BUFFER_SIZE 6

int main(int argc, char const *argv[])
{
    DoubleLinkListQueue *queue = NULL;
    doubleLinkListQueueInit(&queue);

    int buffer[BUFFER_SIZE] = {111, 222, 333, 444, 555, 666};
    for (int idx = 0; idx < BUFFER_SIZE; idx++)
    {
        doubleLinkListQueuePush(queue, (void *)&buffer[idx]);
    }

    int size = 0; 
    doubleLinkListQueueGetSize(queue, &size);
    printf("size:%d\n", size);

    int *val = NULL;
    while (!doubleLinkListQueueIsEmpty(queue))
    {
        doubleLinkListQueueTop(queue, (void **)&val);
        printf("val:%d\n", (int)*val);
        doubleLinkListQueuePop(queue);
    }

    /* 销毁队列 */
    doubleLinkListQueueDestroy(queue);

    return 0;
}
