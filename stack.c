//
//  stack.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/4.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "stack.h"

STACK* createStack(void)
{
    STACK* st;
    
    st = (STACK *)malloc(sizeof(STACK));
    if (st) {
        st -> count    = 0;
        st -> pHead    = NULL;
        return st;
    }
    return NULL;
}

NODE*  createNode(void * data) {
    NODE * pNode;
    
    pNode = (NODE *) malloc(sizeof(NODE));
    if (pNode) {
        pNode -> data = data;
        pNode -> next = NULL;
        return pNode;
    }
    return NULL;
}

bool pushStack (STACK* stack, void* data)
{
    NODE * pNode;
    
    pNode = createNode(data);
    if (pNode) {
        pNode -> next = stack -> pHead;
        stack -> pHead = pNode;
        (stack -> count) += 1;
        return true;
    }
    return false;
}

void* popStack (STACK* stack)
{
    void* pData;
    NODE* tmp;
    
    if (stack -> count == 0)
        return NULL;
    tmp   = stack -> pHead;
    pData = tmp -> data;
    stack -> pHead = tmp -> next;
    free(tmp);
    (stack -> count) --;
    return pData;
}

void* peek     (STACK * const stack)
{
    if (stack -> count == 0)
        return NULL;
    return (stack -> pHead) -> data;
}

bool emptyStack (STACK * const stack)
{
    return stack -> count == 0;
}

bool fullStack (STACK * const stack)
{
    NODE * pNode;
    
    if ((pNode = (NODE *) malloc(sizeof(NODE)))) {
        free(pNode);
        return false;
    }
    return true;
}

unsigned int stackCount (STACK * stack)
{
    return stack -> count;
}

STACK* destroyStack (STACK * stack)
{
    NODE* pNode;
    NODE* tmp;
    
    if (stack) {
        pNode = stack -> pHead;
        while (pNode) {
            tmp = pNode;
            pNode = pNode -> next;
            free(tmp -> data);
            // 如果这块数据在别处被引用怎么办
            free(tmp);
        }
        free(stack);
    }
    return NULL;
}

ArrayList* convertStack2List(const STACK * stack) {
    ArrayList * ret;
    void** list;
    NODE*  cur;
    
    ret  = (ArrayList*) malloc(sizeof(ArrayList));
    if (!ret)
        return ret;
    
    ret -> size = stack -> count;
    if (ret -> size == 0) {
        ret -> data = NULL;
        return ret;
    }
    list  = (void **)malloc(sizeof(void *)*(ret->size));
    if (!list) {
        free(ret);   // 创建数据失败了 必须返回空 失败， 需要把创建的 ret 释放
        return NULL;
    }
    ret -> data = list;
    cur = stack -> pHead;
    while (cur) {
        *list   = cur -> data;
        list++;
        cur     = cur -> next;
    }
    return ret;
}
