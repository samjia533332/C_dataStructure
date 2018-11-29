//
//  graphs.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/9.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "graphs.h"
#include <stdlib.h>

Graph * buildGraph(int numNodes, int adj[numNodes][numNodes] ) {
    Graph * g;
    int ** neighbours;
    int * colSizes;
    
    // initialize
    colSizes = (int *)malloc(numNodes * sizeof(int));
    neighbours = (int **)malloc(numNodes * sizeof(int *));
    g = (Graph *)malloc(sizeof(Graph));
    
    for (int i = 0; i<numNodes; i++) {
        int count = 0;
        for (int j =0; j<numNodes; j++) {
            if (adj[i][j] > 0) count++;
        }
        *(colSizes + i) = count;
    }
    for (int i = 0; i<numNodes; i++) {
        int count = *(colSizes + i);
        if (count == 0) {
            *(neighbours + i) = NULL;
            continue;
        }
        *(neighbours + i) = (int *)malloc(count * sizeof(int));
        int * cur = *(neighbours + i);
        for (int j =0; j<numNodes; j++) {
            if (adj[i][j] == 1) {
                *cur = j;
                cur++;
            }
        }
    }
    g -> numNodes = numNodes;
    g -> graph = neighbours;
    g -> colSizes = colSizes;
    return g;
}

int* getNeighboursByNode(int nodeIdx, Graph * g) {
    int ** graph;
    int * ret;
    
    graph = g -> graph;
    ret = *(graph + nodeIdx);
    return ret;
}

int getNeighbourSizeByNode(int nodeIdx, Graph * g) {
    return  *((g -> colSizes) + nodeIdx);
}

void destroyGraph(Graph * g) {
    int** graph = g -> graph;
    int* colSizes = g -> colSizes;
    int numNodes = g -> numNodes;
    
    free(colSizes);
    for (int i = 0; i<numNodes; i++)
        free( *(graph+i));
    free(graph);
    free(g);
}
