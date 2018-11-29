//
//  stack.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/4.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#endif /* stack_h */

typedef struct {
    unsigned int size;
    void** data;
} ArrayList;

typedef struct node
{
    void * data;
    struct node * next;
} NODE;

NODE*  createNode(void *);

typedef struct stack
{
    unsigned int count;
    NODE* pHead;
} STACK;

STACK* createStack(void);

/* ================= pushStack ================ This function pushes an item onto the stack.
Pre     stack is a pointer to the stack
dataPtr pointer to data to be inserted
Post    Data inserted into stack
Return  true  if successful
false if underflow
 */
bool pushStack (STACK *, void *);

void* popStack (STACK *);

void* peek     (STACK * const);

bool emptyStack (STACK *);

bool fullStack (STACK *);

unsigned int stackCount (STACK *);

STACK* destroyStack (STACK *);

ArrayList* convertStack2List(const STACK *);

