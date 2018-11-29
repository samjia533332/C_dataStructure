//
//  queue.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/10.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "queue.h"

QUEUE * createQueue(void) {
    QUEUE * q;
    
    q = (QUEUE *)malloc(sizeof(QUEUE));
    if (q) {
        q -> count      = 0;
        q -> pfront     = NULL;
        q -> pfront     = NULL;
    }
    return q;
}

void destryQueue(QUEUE * q) {
    void * dataPtr;
    if (q) {
        while (q -> count) {
            dequeueQueue(q, &dataPtr);
            free(dataPtr);
        }
        free(q);
    }
}

bool enqueueQueue(QUEUE * q, void * itemPtr) {
    NODE* pNode;
    
    if (!(pNode = (NODE *)malloc(sizeof(NODE))))
        return false;
    pNode -> data = itemPtr;
    pNode -> next = NULL;
    
    if (!emptyQueue(q))
        (q -> prear) -> next = pNode;
    else
        (q -> pfront)        = pNode;
    (q -> prear)             = pNode;
    (q -> count)++;
    return true;
}

bool dequeueQueue(QUEUE * q, void ** pItemPtr) {
    NODE * pNode;
    
    if (! q -> count)
        return false;
    pNode = q -> pfront;
    *pItemPtr     = pNode -> data;
    if (q -> count == 1) {
        q -> pfront = NULL;
        q -> prear  = NULL;
    } else {
        q -> pfront = (q -> pfront) -> next;
    }
    (q -> count)--;
    free(pNode);
    return true;
}

bool queueFront(QUEUE * q, void ** pItemPtr) {
    if (q -> count == 0)
        return false;
    *pItemPtr = (q -> pfront) -> data;
    return true;
}

bool queueRear(QUEUE * q, void ** pItemPtr) {
    if (q -> count == 0)
        return false;
    *pItemPtr = (q -> prear) -> data;
    return true;
}

bool emptyQueue(QUEUE * q) {
    return q -> count == 0;
}

bool fullQueue(QUEUE * q) {
    NODE* pNode;
    
    pNode = (NODE *)malloc(sizeof(NODE));
    if (pNode) {
        free(pNode);
        return false;
    }
    return true;
}

unsigned int queueCount(QUEUE * q) {
    return q -> count;
}
