//
//  graph.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/26.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef graph_h
#define graph_h

#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "stdbool.h"

#endif /* graph_h */

// =================== STRUCTURES ==================
typedef struct
{
    int            count;
    struct vertex* first;
    int (*compare) (void* argu1, void* argu2);
} GRAPH;

typedef struct vertex
{
    struct vertex*  pNextVertex;
    void* dataPtr;
    int inDegree;
    int outDegree;
    short processed;
    struct arc* pArc;
} VERTEX;

typedef struct arc
{
    struct vertex*  destination;
    struct arc*     pNextArc;
} ARC;

GRAPH* graphCreate     (int (*compare) (void* argu1, void* argu2));

GRAPH* graphDestroy    (GRAPH* graph);
