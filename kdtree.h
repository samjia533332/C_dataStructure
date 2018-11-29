//
//  kdtree.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/11/12.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef kdtree_h
#define kdtree_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_DIM 24

typedef struct kd_node_t {
    double pos[NUM_DIM];
    struct kd_node_t *left, *right;
} KD_NODE;


KD_NODE *make_tree(int len, double[len][NUM_DIM], int dim);

void nearest(KD_NODE *root, KD_NODE *nd, int i, int dim, KD_NODE **best, double *best_dist);


#endif /* kdtree_h */
