////
////  main.c
////  C_notes_Stack
////
////  Created by Zhenyu Jia on 2018/9/4.
////  Copyright © 2018年 Zhenyu Jia. All rights reserved.
////
//
///* This program reads a source program and parses it to make sure all opening-closing parentheses are paired.
// Written by:
// Date: */
//#include <stdio.h>
////#include "stack.h"  // include twice caused re-definition
//#include <stdbool.h>
//#include <string.h>
//#include "utils.h"
//#include "stack_appl.h"
//// Error Messages
//
//void testIsValidParatheses(void);
//void testConvertStr2Int(void);
//void testCountConnection(void);
//
//int main (void)
//{
//    testCountConnection();
//    return 0;
//}
//
//
//void testCountConnection(void) {
//    const int wid = 7;
//    int board[wid][wid] = {0};
//    STACK * ret;
//    board[0][0] = 1;
//    board[0][1] = 1;
//    board[2][3] = 2;
//    board[2][4] = 2;
//    board[3][3] = 2;
//    board[4][2] = 3;
//    printBoard(wid, board);
//
//    ret = countWhiteByBlocks(wid, board);
//    printf("ret size %d \n", stackCount(ret));
//    while (!emptyStack(ret)) {
//        ConnComp * tmp = (ConnComp *)popStack(ret);
//        printf("value %d count %d \n", tmp -> value, tmp -> count);
//        free(tmp);
//    }
//    destroyStack(ret);
//}
//
//void testIsValidParatheses(void) {
//    // test 1
//    char test1[] = ")()";
//    char test2[] = "(0)";
//    char test3[] = "()()";
//    char test4[] = "((0 + (8 -0)))(";
//    char test5[] = "((0 + (8 -0)))";
//
//    printf("test 1 result 0 %d \n", isValidParatheses(test1));
//    printf("test 2 result 1 %d \n", isValidParatheses(test2));
//    printf("test 3 result 1 %d \n", isValidParatheses(test3));
//    printf("test 4 result 0 %d \n", isValidParatheses(test4));
//    printf("test 5 result 1 %d \n", isValidParatheses(test5));
//}
//
//void testConvertStr2Int(void) {
//    char * num1 = "-0";
//    char * num2 = "12902";
//    char * num3 = "-129";
//    char * num4 = "-0000";
//    char * num5 = "0000";
//    printf("num1 0 %d \n", convertChars2Int(num1, strlen(num1)));
//    printf("num2 12902 %d \n", convertChars2Int(num2, strlen(num2)));
//    printf("num3 -129 %d \n", convertChars2Int(num3, strlen(num3)));
//    printf("num2 0 %d \n", convertChars2Int(num4, strlen(num4)));
//    printf("num2 0 %d \n", convertChars2Int(num5, strlen(num5)));
//}


//
//  BST_integer_appl.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/10/25.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//
