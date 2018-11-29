//
//  linear_lists.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/16.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef linear_lists_h
#define linear_lists_h

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#endif /* linear_lists_h */

#define DEFAULT_CAP 10

typedef struct {
    unsigned int   size;
    unsigned int   capacity;
    void ** datas;
    bool (*equal) (void* argu1, void* argu2);
} ArrayList;

// LIST ADT declaration

ArrayList* llcreateList   (unsigned int capacity,
                         bool (*equal) (void* argu1, void* argu2));

void lldestroyList        (ArrayList*);

bool llappendList         (ArrayList*, void*);

bool llremoveList         (ArrayList*, unsigned int);

void * getList          (ArrayList*, unsigned int);

int llsearchList          (ArrayList*, void *);

int   lllistCount         (ArrayList*);

bool  llemptyList         (ArrayList*);
