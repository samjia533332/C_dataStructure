//
//  general_list.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/24.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef general_list_h
#define general_list_h

//#include <stdio.h>
#include "stack.h"

#endif /* general_list_h */

typedef struct general_lsit {
    /* 尽管在定义的时候 list 主要就是包含了 node 但是定义个头 可以保存
     很多描述数据的数据 比如长度，比如头地址，尾地址等 称为metadata*/
    unsigned int count;
    NODE* head;  // NODE 里面的dataPtr 指向一个 key/value pair
    NODE* pos;
    NODE* rear;
    int    (*compare) (void* argu1, void* argu2);
} GENERAL_LIST;

GENERAL_LIST* createList  (int (*compare) (void* argu1, void* argu2));

GENERAL_LIST* destroyList (GENERAL_LIST* list);

int   addNode             (GENERAL_LIST* pList, void* dataInPtr);

bool  removeNode          (GENERAL_LIST* pList, void*  keyPtr, void** dataOutPtr);

bool  searchList          (GENERAL_LIST* pList, void*  pArgu, void** pDataOut);

bool  retrieveNode        (GENERAL_LIST* pList, void*  pArgu, void** dataOutPtr);

bool traverse             (GENERAL_LIST* pList, int fromWhere, void** dataOutPtr);

int   listCount           (GENERAL_LIST* pList);

bool  emptyList           (GENERAL_LIST* pList);

bool  fullList            (GENERAL_LIST* pList);









