//
//  heap.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/26.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef heap_h
#define heap_h

#include <stdlib.h>
#include <math.h>

#endif /* heap_h */


#include <stdbool.h>
typedef struct
{
    void** heapAry;
    int    last;
    int    size;
    int    (*compare) (void* argu1, void* argu2);
    int    maxSize;
} HEAP;

// Prototype Definitions
HEAP* heapCreate (int maxSize, int (*compare) (void* arg1, void* arg2));

bool  heapInsert  (HEAP* heap, void*  dataPtr);

bool  heapDelete (HEAP* heap, void** dataOutPtr);

int   heapCount (HEAP* heap);

bool  heapFull (HEAP* heap);

bool  heapEmpty   (HEAP* heap);

void  heapDestroy (HEAP* heap);

static void _reheapUp (HEAP* heap, int childLoc);

static void _reheapDown (HEAP* heap, int root);

static int  _getLeftChild(int);

static int  _getRightChild(int);

static int  _getParent(int);  // 必须有父节点

static void _swap(void** dataArray, int loc1, int loc2);
