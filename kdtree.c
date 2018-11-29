//
//  kdtree.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/11/12.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//
/* reference https://rosettacode.org/wiki/K-d_tree */

#include "kdtree.h"

#define SQ(x)    ((x) * (x))

static int initRand = 0;

static void swap(KD_NODE *a, KD_NODE *y);

static KD_NODE* findHelper(KD_NODE *left, KD_NODE *right, int kth, int dim);

static KD_NODE* randPartition(KD_NODE *left, KD_NODE *right, int dim);

static KD_NODE* make_tree_rec(struct kd_node_t *t, int len, int i, int dim);

static KD_NODE* find_median(KD_NODE *start, KD_NODE *end, int idx);

static double dist(KD_NODE *a, KD_NODE *b);

/* data is a dynamic KD_NODE array idx is the n th element to split*/
static KD_NODE *find_median(KD_NODE *start, KD_NODE *end, int idx) {
    int num, kth;
    num = (int) (end - start) + 1;
    if (num % 2 == 0)
        kth  = num / 2;
    else
        kth  = num / 2 + 1;
    return findHelper(start, end, kth, idx);
}


static double dist(KD_NODE *a, KD_NODE *b) {
    double sum = 0.0;
    
    if (!a || !b)
        return - 1.0;
    // use Eucludien distance
    for (int i = 0; i < NUM_DIM; i++)
        sum += SQ(a->pos[i] - a->pos[i]);
    return sqrt(sum);
}

static void swap(KD_NODE *a, KD_NODE *b) {
    double tmp[NUM_DIM];
    memcpy(tmp, a->pos, sizeof(tmp));
    memcpy(a->pos, b->pos, sizeof(tmp));
    memcpy(b->pos, tmp, sizeof(tmp));
}

KD_NODE *make_tree(int len, double data[len][NUM_DIM], int dim) {
    KD_NODE *treeNodes;
    
    if (!(treeNodes = (KD_NODE *) malloc(sizeof(KD_NODE)*len)))
        return NULL;
    for (int i = 0; i < len; i++) {
        (treeNodes+i)->left   = NULL;
        (treeNodes+i)->right  = NULL;
        memcpy((treeNodes+i)->pos, data[i], sizeof(data[i]));
    }
    return make_tree_rec(treeNodes, len, 0, dim);
}

static KD_NODE* make_tree_rec(KD_NODE *t, int len, int i, int dim) {
    if (!t) return NULL;
    if (len == 1) return t;
    
    KD_NODE* median;
    int leftCnt, rightCnt;
    
    median          = find_median(t, t+len, i);
    leftCnt         = (int) (median - t);
    rightCnt        = len - leftCnt - 1;
    i = (i+1) % dim;  // 分到底
    median->left    = find_median(t, t+leftCnt, i);
    median->right   = find_median(median+1, t+len, <#int idx#>);
    return median;
}

void nearest(KD_NODE *root, KD_NODE *nd, int i, int dim, KD_NODE **best, double *best_dist) {
    if (!root) return;
    double dist_;
    int next_i;
    
    dist_ = dist(root, nd);
    if (dist_ < *best_dist) {
        *best_dist = dist_;
        *best      = root;
    }
    next_i  = (i+1) % dim;
    if (nd->pos[i] < root->pos[i])
        nearest(root->left, nd, next_i, dim, best, best_dist);
    else
        nearest(root->right, nd, next_i, dim, best, best_dist);
}

static KD_NODE* findHelper(KD_NODE *left, KD_NODE *right, int kth, int dim) {
    if (right - left + 1 < kth)
        return NULL;
    
    int leftCnt, rightCnt;
    KD_NODE *pPtr  = randPartition(left, right, dim);
    
    leftCnt   = (int) (pPtr - left);
    rightCnt  = (int) (right - pPtr);
    if (kth < leftCnt)
        return findHelper(left, left + leftCnt, kth, dim);
    else if (kth > leftCnt + 1)
        return findHelper(pPtr + 1, right, kth - leftCnt - 1, dim);
    return pPtr;
}

static KD_NODE* randPartition(KD_NODE *left, KD_NODE *right, int dim) {
    KD_NODE *l, *r;
    double pivotVal;
    
    if (left >= right)
        return left;
    if (!initRand) {
        srand((unsigned)time(0));
        initRand = 1;
    }
    
    int pivot   = rand() % (right - left);
    swap(left, left+pivot);
    l = left + 1;
    r = right;
    pivotVal  = left->pos[dim];
    
    while (1) {
        while (l <= r && l->pos[dim] <= pivotVal) l++;
        while (l <= r && r->pos[dim] >= pivotVal) r--;
        if (l > r) break;
        swap(l, r);
    }
    swap(left, r);
    return r;
}
