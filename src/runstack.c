#include <errno.h>
#include <stdlib.h>
#include "coroutine_int.h"

void stk_init(struct stk *stk)
{
    stk->in = 0;
    stk->mask = RINGBUFFER_SIZE - 1;
}

static inline unsigned int __ringbuffer_unused(struct stk *stk)
{
    return stk->mask + 1 - (stk->in);
}

int stk_push(struct stk *stk, struct task_struct *task)
{
    if (!__ringbuffer_unused(stk))
        return -EAGAIN;
    stk->s[stk->in & stk->mask] = task;
    stk->in++;

    return 0;
}

struct task_struct *stk_pop(struct stk *stk)
{
    struct task_struct *rev;
    if (stk->in < 0)
        return NULL;
    rev = stk->s[--stk->in & stk->mask];
    return rev;
}