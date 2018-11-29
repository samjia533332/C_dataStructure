//
//  general_list.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/24.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "general_list.h"

static bool _insert        (GENERAL_LIST* pList, NODE* pPre, void* dataInPtr);

static void _delete       (GENERAL_LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr);

static bool _search       (GENERAL_LIST* pList, NODE** pPre, NODE** pLoc, void*  pArgu);


GENERAL_LIST* createList  (int (*compare) (void* argu1, void* argu2)) {
    GENERAL_LIST* pRet;
    
    pRet  = (GENERAL_LIST*) malloc(sizeof(GENERAL_LIST));
    if (pRet) {
        pRet->compare = compare;
        pRet->count   = 0;
        pRet->head    = NULL;
        pRet->pos     = NULL;
        pRet->rear    = NULL;
        return pRet;
    }
    return NULL;
}

GENERAL_LIST* destroyList (GENERAL_LIST* list) {
    NODE* pNode;
    NODE* tmp;
    
    if (list) {
        pNode = list -> head;
        while (pNode) {
            tmp = pNode;
            pNode = pNode -> next;
            free(tmp -> data);
            free(tmp);
        }
        free(list);
    }
    return NULL;
}

/*================== addNode =================
 Inserts data into list.
    Pre     pList is pointer to valid list
    dataInPtr pointer to insertion data
    Post    data inserted or error
    Return  -1 if overflow
    0 if successful
    1 if dupe key
*/
int   addNode             (GENERAL_LIST* pList, void* dataInPtr) {
    bool found, success;
    NODE *pPre, *pLoc;
    
    found  = _search(pList, &pPre, &pLoc, dataInPtr);
    if (found)
        return 1;
    success   = _insert(pList, pPre, dataInPtr);
    if (!success)
        return -1;
    return 0;
}

bool  removeNode          (GENERAL_LIST* pList, void* keyPtr, void** dataOutPtr) {
    bool found;
    NODE *pPre, *pLoc;
    
    found  = _search(pList, &pPre, &pLoc, keyPtr);
    if (found) _delete(pList, pPre, pLoc, dataOutPtr);
    return found;
}

bool  searchList          (GENERAL_LIST* pList, void*  pArgu, void** pDataOut) {
    bool found;
    NODE *pPre, *pLoc;
    
    found   = _search(pList, &pPre, &pLoc, pArgu);
    if (found) {
        *pDataOut  = pLoc->data;
    } else {
        *pDataOut  = NULL;
    }
    return found;
}

int   listCount           (GENERAL_LIST* pList) {
    return pList->count;
}

bool  emptyList           (GENERAL_LIST* pList) {
    return (pList->count == 0);
}

bool  fullList            (GENERAL_LIST* pList) {
    NODE *pNew;
    
    pNew = (NODE*) malloc(sizeof(NODE));
    if (pNew == NULL) return true;
    free(pNew);
    return false;
}

bool  retrieveNode        (GENERAL_LIST* pList, void* pArgu, void** dataOutPtr) {
    bool found;
    NODE *pPre, *pLoc;
    
    found     = _search(pList, &pPre, &pLoc, pArgu);
    if (!found) {
        *dataOutPtr  = NULL;
        return false;
    }
    *dataOutPtr  = pLoc->data;
    return true;
}

bool traverse             (GENERAL_LIST* pList, int fromWhere, void** dataOutPtr) {
    /* 遍利就是通过 用一个指针一直记录当前这个数据 */
    if (pList->count == 0)
        return false;
    if (fromWhere == 0) {
        pList->pos     = pList->head;
        *dataOutPtr    = pList->pos->data;
        return true;
    } else {
        if (pList->pos->next == NULL)
            return false;
        pList->pos     = pList->pos->next;
        *dataOutPtr    = pList->pos->data;
        return true;
    }
}

/*================== STATIC ==================*/
static bool _insert       (GENERAL_LIST* pList, NODE* pPre, void* dataInPtr) {
    NODE* pNew;
    
    pNew  = (NODE*) malloc(sizeof(NODE));
    if (pNew == NULL)
        return false;
    pNew->data = dataInPtr;
    if (pPre == NULL) {
        pNew->next   = pList->head;
        pList->head  = pNew;
        if (pList->count == 0)
            pList->rear  = pNew;
    } else {
        pNew->next   = pPre->next;
        pPre->next   = pNew;
        if (pList->rear == pPre)
            pList->rear = pNew;
    }
    (pList->count)++;
    return true;
}

static void _delete       (GENERAL_LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr)
{
    if (pPre == NULL)
        pList->head   = pLoc->next;
    else
        pPre->next    = pLoc->next;
    if (pLoc == pList->rear)
        pList->rear   = pPre;
    (pList->count)--;
//    free(pLoc->data);  这里不要释放数据因为数据会被 给 dataOutPtr
    *dataOutPtr = pLoc->data;
    free(pLoc);
    return;
}

static bool _search       (GENERAL_LIST* pList, NODE** pPre, NODE** pLoc, void*  pArgu) {
#define COMPARE ( ((* pList->compare) (pArgu, (*pLoc)->data)) )
#define COMPARE_LAST ((* pList->compare) (pArgu, pList->rear->data))
    //Local Definitions
    int result;
    //Statements
    *pPre  = NULL;
    *pLoc  = pList->head;
    if (pList->count == 0)
        return false;
    if ( COMPARE_LAST > 0)
    {
        *pPre = pList->rear;
        *pLoc = NULL;
        return false;
    } // if
    while ( (result = COMPARE) > 0 )
    {
        // Have not found search argument location
        *pPre = *pLoc;
        *pLoc = (*pLoc)->next;
    } // while
    if (result == 0)
        // argument found--success
        return true;
    else
        return false;
}
