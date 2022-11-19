#include <stdio.h>
#include "../src/coroutine_int.h"

int main(void)
{
    struct task_struct task[10];
    struct stk stk;
    struct task_struct *tmp;

    stk_init(&stk);
    for (int i = 0; i < 10; i++)
    {
        task[i].tfd = i;
        printf("push %d, return %d\n", i, stk_push(&stk, &task[i]));
    }

    for (int i = 0; i < 10; i++)
    {
        tmp = stk_pop(&stk);
        if (tmp)
            printf("pop %d\n", tmp->tfd);
        else
            printf("pop failed\n");
    }
}
