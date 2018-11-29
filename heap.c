//
//  heap.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/26.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "heap.h"

HEAP* heapCreate    (int maxSize, int (*compare) (void* arg1, void* arg2)) {
    HEAP* pHeap;
    pHeap   = (HEAP*) malloc(sizeof(HEAP));
    if (!pHeap || maxSize <= 0)
        return NULL;
    
    pHeap->maxSize          = (int) pow (2, ceil(log2(maxSize))) - 1;
    pHeap->heapAry   = (void**) malloc(sizeof(void*) * pHeap->maxSize);
    
    if (pHeap->heapAry == NULL) {
        free(pHeap);
        return NULL;
    }
    pHeap->compare   = compare;
    pHeap->last      = -1;
    pHeap->size      = 0;
    return pHeap;
}

void  heapDestroy   (HEAP* heap) {
    if (heap) {
        free(heap->heapAry);
        free(heap);
    }
    return;
}

bool  heapInsert    (HEAP* heap, void*  dataPtr) {
    if (heap->size == heap->maxSize)
        return false;
    
    (heap->last)++;
    (heap->size)++;
    *(heap->heapAry + heap->last) = dataPtr;
    
    if (heap->last !=0)
        _reheapUp(heap, heap->last);
    return true;
}

bool  heapDelete    (HEAP* heap, void** dataOutPtr) {
    if (heap->size == 0) {
        *dataOutPtr = NULL;
        return false;
    }
    // swap
    *dataOutPtr       = *(heap->heapAry);
    *(heap->heapAry)  = *(heap->heapAry + heap->last);
    (heap->size)--;
    (heap->last)--;
    _reheapDown(heap, 0);
    return true;
}

int   heapCount     (HEAP* heap) {
    return heap->size;
}

bool  heapFull      (HEAP* heap) {
    return heap->size  == heap->maxSize;
}

bool  heapEmpty     (HEAP* heap) {
    return heap->size == 0;
}

static void _reheapUp      (HEAP* heap, int childLoc) {
    int parent;
    int compare_ret;
    
    if (childLoc == 0)
        return;
    parent     = _getParent(childLoc);
    compare_ret    = (* heap->compare) (*(heap->heapAry+parent), *(heap->heapAry+childLoc));
    if (compare_ret <= 0)
        return;
    _swap(heap->heapAry, childLoc, parent);
    _reheapUp(heap, parent);
}

static void _reheapDown    (HEAP* heap, int root) {
    int leftChild, rightChild;
    void *leftData, *rightData, *rootData;
    int (*thisComp) (void*, void*);
    
    rootData      = *(heap->heapAry+root);
    thisComp      = heap->compare;
    leftChild     = _getLeftChild(root);
    rightChild    = _getRightChild(root);
    if (root >= heap->last || leftChild > heap->last) {   // 没有孩子
        return;
    } else if (rightChild > heap->last) { // 没有右孩子
        if (thisComp(rootData,  *(heap->heapAry+leftChild)) <= 0) {  // OK
            return;
        } else {
            _swap(heap->heapAry, root, leftChild);
            _reheapDown(heap, leftChild);
        }
    } else {
        leftData    = *(heap->heapAry+leftChild);
        rightData   = *(heap->heapAry+rightChild);
        if (thisComp(leftData, rightData) <= 0) {   // 左孩子小
            if (thisComp(rootData, leftData) > 0) {
                _swap(heap->heapAry, root, leftChild);
                _reheapDown(heap, leftChild);
            }
        } else {   // 右孩子小
            if (thisComp(rootData, rightData) > 0) {
                _swap(heap->heapAry, root, rightChild);
                _reheapDown(heap, rightChild);
            }
        }
    }
}

static int  _getLeftChild(int parent) {
    return parent * 2 + 1;
}

static int  _getRightChild(int parent) {
    return parent * 2 + 2;
}

static int  _getParent(int child) { // 必须有父节点
    if (child % 2 == 0) {
        return child / 2 - 1;
    }
    return child / 2;
}

static void _swap(void** dataArray, int loc1, int loc2) {
    void* dataHolder;
    dataHolder  = *(dataArray+loc1);
    *(dataArray+loc1)   = *(dataArray+loc2);
    *(dataArray+loc2)   = dataHolder;
}
