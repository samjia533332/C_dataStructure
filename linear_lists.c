//
//  linear_lists.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/16.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "linear_lists.h"

bool _ensureCapacity    (ArrayList*, unsigned int);

ArrayList* llcreateList   (unsigned int capacity,
                         bool (*equal) (void*, void*)) {
    ArrayList* aList  = (ArrayList *)malloc(sizeof(ArrayList));
    if (!aList)
        return NULL;
    
    aList -> capacity = capacity;
    aList -> size     = 0;
    
    if (capacity == 0) {
        aList -> datas  = NULL;
    } else {
        aList -> datas  = (void **)malloc(capacity * sizeof(void *));
        if (!(aList -> datas))
            return NULL;
    }
    return aList;
}

void lldestroyList        (ArrayList* list) {
    void ** datas  = list -> datas;
    for (int i = 0; i < list -> capacity; i++) {
        free(*(datas+i));
    }
    free(datas);
    free(list);
}

bool llappendList         (ArrayList* list, void* data) {
    unsigned int newSize   = list -> size + 1;
    if (!_ensureCapacity(list, newSize)) {
        return false;
    };
    *(list -> datas + newSize)  = data;
    (list -> size)++;
    return true;
}

bool llremoveList         (ArrayList* list, unsigned int idx) {
    if (idx >= list -> size)
        return false;
    void * deleteElem    = *(list -> datas + idx);
    free(deleteElem);
    for (int i = idx; i < list -> size - 1; i++) {
        *(list -> datas + i) = *(list -> datas + i + 1);
    }
    (list -> size) --;
    return true;
};

void * getList          (ArrayList* list, unsigned int idx) {
    if (idx >= list -> size)
        return NULL;
    return *(list -> datas + idx);
}

int llsearchList          (ArrayList* list, void * data) {
    for (int i = 0; i < list -> size; i++) {
        if (list -> equal( *((list -> datas) + i), data)) {
            return i;
        }
    }
    return -1;
}

int   lllistCount         (ArrayList* list) {
    return list -> size;
}

bool  llemptyList         (ArrayList* list) {
    return list -> size == 0;
}

bool _ensureCapacity    (ArrayList* list, unsigned int need) {
    unsigned int newCap;
    void ** newDatas;
    
    if (list -> capacity >= need)
        return true;
    
    newCap = need * 3 / 2;
    newDatas = (void **)malloc(sizeof(void*) * newCap);
    if (!newDatas) {
        printf("List full inable to expand capacity.");
        return false;
    }
    for (int i = 0; i < list -> size; i++)
        *(newDatas + i) = *((list -> datas) + i);
    free(list -> datas);
    
    list -> datas  = newDatas;
    list -> capacity  = newCap;
    return true;
}


