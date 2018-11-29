//
//  BST.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/25.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "BST.h"

static NODE* _insert    (BST_TREE* tree, NODE* root, NODE* newPtr);

static NODE* _delete    (BST_TREE* tree, NODE* root, void* dataPtr, bool* success);

static void* _retrieve  (BST_TREE* tree, void* dataPtr, NODE* root);

static void _traverse   (NODE* root, void (*process) (void* dataPtr));

static void _destroy    (NODE* root);

BST_TREE* BST_Create    (int (*compare) (void* argu1, void* argu2)) {
    BST_TREE* bstRet;
    
    bstRet   = (BST_TREE*)malloc(sizeof(BST_TREE));
    if (bstRet != NULL) {
        bstRet->count   = 0;
        bstRet->root    = NULL;
        bstRet->compare = compare;
    }
    return bstRet;
}

BST_TREE* BST_Destroy   (BST_TREE* tree) {
    if (tree) {
        _destroy(tree->root);
        free(tree);
    }
    return NULL;
}

bool  BST_Insert        (BST_TREE* tree, void* dataPtr) {
    NODE* pNew;
    if (!tree)
        return false;
    if ((pNew = (NODE*)malloc(sizeof(NODE))) == NULL)
        return false;
    
    pNew->dataPtr   = dataPtr;
    pNew->left      = NULL;
    pNew->right     = NULL;
    tree->root      = _insert(tree, tree->root, pNew);
    (tree->count)++;
    return true;
}

bool  BST_Delete        (BST_TREE* tree, void* dltKey) {
    bool success;
    if (tree == NULL)
        return false;
    tree->root   = _delete(tree, tree->root, dltKey, &success);
    if (success) {
        (tree->count)--;
        if (tree->count == 0)
            // 因为释放了以后 仍然持有那个地址 但是那个地址已经释放，因此要制为 NULL
            tree->root  = NULL;
    }
    return success;
}

void* BST_Retrieve      (BST_TREE* tree, void* keyPtr) {
    if (tree) {
        return _retrieve(tree, keyPtr, tree->root);
    }
    return NULL;
}

void  BST_Traverse      (BST_TREE* tree, void (*process)(void* dataPtr)) {
    if (tree)
        _traverse(tree->root, process);
    return;
}

bool BST_Empty          (BST_TREE* tree) {
    return tree->count == 0;
}

bool BST_Full           (BST_TREE* tree) {
    NODE* tmp;
    if ((tmp = (NODE*)malloc(sizeof(NODE))) != NULL) {
        free(tmp);
        return false;
    }
    return true;
}

int  BST_Count          (BST_TREE* tree) {
    return tree->count;
}

static NODE* _insert    (BST_TREE* tree, NODE* root, NODE* newPtr) {
    if (!root) {
        return newPtr;
    }
    if ((* tree->compare)(root->dataPtr, newPtr->dataPtr) < 0) {
        root->left   = _insert(tree, root->left, newPtr);
        return root;
    } else {
        root->right   = _insert(tree, root->right, newPtr);
        return root;
    }
}

static NODE* _delete    (BST_TREE* tree, NODE* root, void* dataPtr, bool* success) {
    NODE* leftTreeLargest;
    NODE* leftRightParent;
    NODE* ret;
    void* dataHolder;
    
    if (!root)  { // dataPtr not found
        *success  = false;
        return NULL;
    }
    int compare_ret     = (* tree->compare)(root->dataPtr, dataPtr);
    if (compare_ret < 0) {
        root->left   = _delete(tree, root->left, dataPtr, success);
        return root;
    } else if (compare_ret > 0) {
        root->right  = _delete(tree, root->right, dataPtr, success);
        return root;
    }
    if (root->left->right == NULL) {
        root->left->right  = root->right;
        ret   = root->left;
        free(root->dataPtr);
        free(root);
        return ret;
    }
    leftRightParent  = root->left;
    leftTreeLargest  = root->left->right;
    while (leftTreeLargest->right) {
        leftRightParent = leftTreeLargest;
        leftTreeLargest = leftTreeLargest->right;
    }
    leftRightParent -> right = leftTreeLargest->left;
    leftTreeLargest->left    = NULL;
    dataHolder               = root->dataPtr;
    root->dataPtr            = leftTreeLargest->dataPtr;
    free(dataHolder);
    free(leftTreeLargest);
    return root;
}

static void* _retrieve  (BST_TREE* tree, void* dataPtr, NODE* root) {
    int compare_ret;
    
    if (root) {
        compare_ret = (* tree->compare) (root->dataPtr, dataPtr);
        if (compare_ret < 0)
            return _retrieve(tree, dataPtr, root->left);
        else if (compare_ret > 0)
            return _retrieve(tree, dataPtr, root->right);
        return root->dataPtr;
    }
    return NULL;
}

static void _traverse   (NODE* root, void (*process) (void* dataPtr)) {
    if (!root)
        return;
    _traverse(root->left, process);
    process(root->dataPtr);
    _traverse(root->right, process);
}

static void _destroy    (NODE* root) {
    if (root) {
        _destroy(root->left);
        _destroy(root->right);
        free(root->dataPtr);
        free(root);
    }
    return;
}
