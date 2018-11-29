//
//  AVL_tree.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/25.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "AVL_tree.h"

AVL_TREE* AVL_Create      (int (*compare)(void* argu1, void* argu2)) {
    AVL_TREE* avl_tree;
    avl_tree     = (AVL_TREE*)malloc(sizeof(AVL_TREE));
    if (avl_tree) {
        avl_tree->compare   = compare;
        avl_tree->count     = 0;
        avl_tree->root      = NULL;
    }
    return avl_tree;
}

AVL_TREE* AVL_Destroy     (AVL_TREE* tree) {
    if (!tree)
        return NULL;
    _destroy(tree->root);
    free(tree);
    return NULL;
}

bool  AVL_Insert          (AVL_TREE* tree, void* dataInPtr) {
    NODE* newPtr;
    bool forTaller;
    
    if ((newPtr  = (NODE*)malloc(sizeof(NODE))) == NULL)
        return false;
    newPtr->bal     = EH;
    newPtr->right   = NULL;
    newPtr->left    = NULL;
    newPtr->dataPtr = dataInPtr;
    tree->root      = _insert(tree, tree->root, newPtr, &forTaller);
    (tree->count)++;
    return true;
}

bool  AVL_Delete          (AVL_TREE* tree, void* dltKey) {
    return true;
}

void AVL_Traverse (AVL_TREE* tree,
                   void (*process) (void* dataPtr))
{
    _traversal(tree->root, process);
    return;
}

void* AVL_Retrieve (AVL_TREE* tree, void* keyPtr) {
    // Statements
    if (tree->root)
        return _retrieve (tree, keyPtr, tree->root);
    else
        return NULL;
} // AVL_Retrieve

int  AVL_Count            (AVL_TREE* tree) {
    return tree->count;
}

bool AVL_Empty            (AVL_TREE* tree) {
    return tree->count == 0;
}

bool AVL_Full             (AVL_TREE* tree) {
    NODE* tmp;
    if ((tmp = (NODE*)malloc(sizeof(NODE))) != NULL) {
        free(tmp);
        return false;
    }
    return true;
}

static NODE* _insert      (AVL_TREE* tree, NODE* root, NODE* newPtr, bool* taller) {
    int compare_ret;
    
    if (!root) {
        *taller   = true;
        return newPtr;
    }
    compare_ret  = (* tree->compare) (root->dataPtr, newPtr->dataPtr);
    if (compare_ret < 0) {  // need to go left
        root->left   = _insert(tree, root->left, newPtr, taller);
        if (*taller)
            switch (root->bal) {
                case LH:   // was left high need to rotate
                    root   = insLeftBal(root, taller);
                    break;
                case EH:
                    root->bal = LH;
                    break;
                case RH:
                    root->bal = EH;
                    break;
            }
        return root;
    }
    else {
        root->right   = _insert(tree, root->right, newPtr, taller);
        if (*taller)
            switch (root->bal) {
                case LH:
                    root->bal   = EH;
                    break;
                case EH:
                    root->bal   = RH;
                    break;
                case RH:
                    root = insRightBal(root, taller);
                    break;
            }
        return root;
    }
}

static void _traversal   (NODE* root, void (*process)(void* dataPtr)) {
    if (root) {
        _traversal(root->left, process);
        process(root->dataPtr);
        _traversal(root->right, process);
    }
    return;
}

static NODE* insLeftBal (NODE* root, bool* taller) {   // 这个会有多种情况处理
    NODE* rightTree;
    NODE* leftTree;

    leftTree = root->left;
    switch (leftTree->bal) {
        case LH:
            root->bal       = EH;
            leftTree->bal   = EH;
            
            root     = rotateRight (root);
            *taller  = false;
            break;
        case EH:
            printf ("\n\aError in insLeftBal\n");
            exit (100);
        case RH:
            rightTree   = leftTree->right;
            switch (rightTree->bal) {
                case LH: root->bal     = RH;
                    leftTree->bal = EH;
                    break;
                case EH: root->bal     = EH;
                    leftTree->bal = LH;
                case RH: root->bal     = EH;
                    leftTree->bal = LH;
                    break;
            } // switch rightTree
            rightTree->bal = EH;
            // Rotate Left
            root->left = rotateLeft (leftTree);
            // Rotate Right
            root     = rotateRight (root);
            *taller  = false;
    } // switch
    return root;
}

static NODE* insRightBal  (NODE* root, bool* taller) {
    return NULL;   // todo
}

static NODE* _delete      (AVL_TREE* tree, NODE* root,
                           void* dltKey, bool* shorter, bool* success) {
    return NULL;  // todo
}

static void* _retrieve    (AVL_TREE* tree, void* keyPtr, NODE* root) {
    int compare_ret;
    
    if (root) {
        compare_ret = (* tree->compare) (keyPtr, root->dataPtr);
        if (compare_ret < 0) {
            return _retrieve(tree, keyPtr, root->left);
        } else if (compare_ret >0) {
            return _retrieve(tree, keyPtr, root->right);
        } else {
            return root->dataPtr;
        }
    }
    return NULL;
}

static void _destroy      (NODE* root) {
    if (!root) {
        _destroy(root->left);
        _destroy(root->right);
        free(root->dataPtr);
        free(root);
    }
}

NODE* rotateLeft (NODE* root) {
    // Local Definitions
    NODE* tempPtr;
    // Statements
    tempPtr        = root->right;
    root->right    = tempPtr->left;
    tempPtr->left  = root;
    return tempPtr;
} // rotateLeft

NODE* rotateRight (NODE* root) {
    NODE* tempPtr;
    tempPtr        = root->left;
    root->left     = tempPtr->right;
    tempPtr->right = root;
    return tempPtr;
}
