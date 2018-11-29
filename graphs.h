//
//  graphs.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/9.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef graphs_h
#define graphs_h

#include <stdio.h>

#endif /* graphs_h */

typedef struct graph
{
    int numNodes;
    int ** graph;
    int * colSizes;
} Graph;

Graph * buildGraph(int numNodes, int[numNodes][numNodes]);

void destroyGraph(Graph *);

int* getNeighboursByNode(int, Graph *);

int getNeighbourSizeByNode(int, Graph *);
