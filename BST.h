//
//  BST.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/25.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include <stdbool.h>
#include <stdlib.h>

#endif /* BST_h */

typedef struct node {
    void* dataPtr;
    struct node *left;
    struct node *right;
} NODE;

typedef struct {
    int count;
    int (*compare) (void *argu1, void *argu2);
    NODE * root;
} BST_TREE;

BST_TREE* BST_Create    (int (*compare) (void* argu1, void* argu2));

BST_TREE* BST_Destroy   (BST_TREE* tree);

bool  BST_Insert        (BST_TREE* tree, void* dataPtr);

bool  BST_Delete        (BST_TREE* tree, void* dltKey);

void* BST_Retrieve      (BST_TREE* tree, void* keyPtr);

void BST_Traverse       (BST_TREE* tree, void (*process)(void* dataPtr));

bool BST_Empty          (BST_TREE* tree);

bool BST_Full           (BST_TREE* tree);

int  BST_Count          (BST_TREE* tree);

