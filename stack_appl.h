//
//  stack_appl.h
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/6.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#ifndef stack_appl_h
#define stack_appl_h

#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
#include <string.h>
#include "graphs.h"

#endif /* stack_appl_h */


bool isValidParatheses(const char *);

char * infix2Postfix(char *);

int postExprEval(char *);   

int priority (char);

/* =================== isOperator ====================
 Determine if token is an operator.
 Pre  token is a valid operator
 Post return true if operator; false if not
 */
bool isOperator (char);

int operate(int, int, char);

/* =================== seekGoal ====================
 Determine find the path from src to target.
 Pre  src and target are valid graph nodes, graph is valid DAG and no connection between tree graph. 
 Post a dynamic array of nodes, this array will end with -1;
 */
int* seekGoal(int, int, Graph*);

typedef struct
{
    int row;
    int col;
} POSITION;

/* =================== eightQueens ====================
 Determine find the eight queens solution modify the stack
 Pre  stack must be an empty stack, boardSize be valid int from 4 to 8
 Post modify and store solution in the stack.
 */
void eightQueens(STACK *, int);

/* ===================== guarded ==================
 Checks rows, columns, diagonals for guarding queens
 */
bool guarded (int[][9], int, int, int);

bool guardedOne (int[][9], int, int, int, int, int);

/*
     project 3-24 count white blocks
 */
typedef struct {
    int value;
    int count;
} ConnComp;

STACK * countWhiteByBlocks(int width, const int[width][width]);

void dfsCount(int width, int board[width][width], int rowI, int colI, int * count);

void printBoard(int width, const int board[width][width]);

/*
    solve the n queens problem
 */
char*** solveNQueens(int, int*);

bool nGuardedOne (int n , char[n][n], int, int, int, int);

bool nGuarded(int n, char[n][n], int, int);

void initBoard(int n, char[n][n]);

void dfsNQueens(int, int width, char[width][width], STACK*);

