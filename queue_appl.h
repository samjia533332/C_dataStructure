//
//  queue_appl.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/11.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef queue_appl_h
#define queue_appl_h

#include <stdio.h>
#include "queue.h"

#endif /* queue_appl_h */

typedef struct {
    int startTime;
} STATUS;

typedef struct {
    unsigned int totSvcTime;
    unsigned int numCust;
    unsigned int totWaitTime;
    unsigned int maxQueueSize;
    float avgSvcTime;
    float avgWaitTime;
} STATS;

void queueSimuDriver(void);

void newCustomer (QUEUE* , unsigned int, int);

void serverFree (QUEUE*, unsigned int, STATUS*, int);

void svcComplete (QUEUE*, unsigned int, STATUS*, int, int);

void printStats (STATS*);

