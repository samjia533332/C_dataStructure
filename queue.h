//
//  queue.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/10.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include "stack.h"
#include <stdbool.h>

#endif /* queue_h */


typedef struct queue
{
    unsigned int count;
    NODE* pfront;
    NODE* prear;
} QUEUE;

QUEUE * createQueue(void);

void destryQueue(QUEUE *);

bool enqueueQueue(QUEUE *, void *);

// 终于明白了 这里要修改 void 指针的地址， 因此要传指针的指针，
// 如果只传了 指针是call by value 了 指针的地址不能修改
bool dequeueQueue(QUEUE *, void **);

bool queueFront(QUEUE *, void **);

bool queueRear(QUEUE *, void **);

bool emptyQueue(QUEUE *);

bool fullQueue(QUEUE *);

unsigned int queueCount(QUEUE *);


