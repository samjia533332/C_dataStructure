//
//  utils.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/6.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "utils.h"

int convertChars2Int(const char * str, unsigned int len) {
    int ret = 0, cur = 1;
    int sign = 1, bit = 1;
    const char* start = str + len - 1;
    
    if (*str == '-') {
        sign = -1;
        str ++;
    }
    while (start >= str) {
        cur = (*start - '0');
        ret += bit * cur;
        bit *= 10;
        start --;
    }
    return sign * ret;
}
