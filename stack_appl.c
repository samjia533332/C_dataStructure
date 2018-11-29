//
//  stack_appl.c
//  C_notes_Stack
//
//  Created by Zhenyu Jia on 2018/9/6.
//  Copyright © 2018年 Zhenyu Jia. All rights reserved.
//

#include "stack_appl.h"

#define NUM_DIRS 8
#define NUM_DIMES 2
static const int DIRS[NUM_DIRS][NUM_DIMES] = {{1,0}, {0,1}, {-1,0}, {0, -1},
    {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

// 判断一个表达式的 括号是否合法
bool isValidParatheses(const char * expr) {
    STACK* stack;
    char token;
    char * dataPtr;
    
    stack = createStack();
    
    while ((token = *expr) != '\0') {
        if (token == '(') {
            dataPtr = (char *)malloc(sizeof(char));
            pushStack(stack, dataPtr);
        } else if (token == ')') {
            if (emptyStack(stack)) {
                break;  // 提前退出
            } else {
                dataPtr = popStack(stack);
                free(dataPtr);
            }
        }
        expr ++;
    }
    bool ret = emptyStack(stack) && *expr == '\0';
    destroyStack(stack);
    return ret;
}

char * infix2Postfix(char * expr) {
    // assume valid string
    STACK* stack;
    char token;
    char *dataPtr, *ret, *retCur;
    
    ret = (char *) malloc(sizeof(char) * (1+ strlen(expr))); // for '\0'
    retCur = ret;
    
    stack = createStack();
    while ((token = *expr) != '\0') {
        if (token == '(') {
            dataPtr = (char *) malloc(sizeof(char));
            *dataPtr = token;
            pushStack(stack, dataPtr);
        }
        else if (token == ')') {
            dataPtr = (char *)popStack(stack);
            while (*dataPtr != '(') {
                *retCur = *dataPtr;
                retCur++;
                free(dataPtr);
                dataPtr = (char*)popStack (stack);
            }
            free(dataPtr);
        }
        else if (isOperator(token)) {
            // * / 不能直接贴进去了 因为有括号
            dataPtr = (char *)peek(stack);
            while (!emptyStack(stack) &&
                   priority(token) <= priority(*dataPtr)) {
                dataPtr  = (char*)popStack (stack);
                *retCur  = *dataPtr;
                retCur++;
                free(dataPtr);
                dataPtr  = (char*)peek(stack);
            }
            dataPtr  = (char*) malloc (sizeof (char));
            *dataPtr = token;
            pushStack (stack , dataPtr);
        }
        else {
             // character is operand
            *retCur = token;
            retCur++;
        } // else
    }
    while (!emptyStack (stack)) {
        dataPtr = (char*)popStack (stack);
        *retCur = *dataPtr;
        retCur++;
        free(dataPtr);
    }
    *retCur = '\0'; // signal end of expression.
    destroyStack(stack);
    return ret;
}

int postExprEval(char * expr) {
    STACK* stack;
    int * dataPtr1, * dataPtr2;
    int ret = 0;
    
    stack = createStack();
    while (*expr != '\0') {
        if (isOperator(*expr)) {
            dataPtr2 = (int *) popStack(stack);
            dataPtr1 = (int *) popStack(stack);
            int * tmp = malloc(sizeof(int));
            *tmp = operate(*dataPtr1, *dataPtr2, *expr);
            free(dataPtr2);
            free(dataPtr1);
            pushStack(stack, tmp);
        }
        else {
            int * val = (int *) malloc(sizeof(int));
            *val = *expr - '0';
            pushStack(stack, val);
        }
        expr ++;
    }
    if (stackCount(stack) == 1) {
        dataPtr1 = (int *) peek(stack);
        ret = *dataPtr1;
    } else {
        printf("Stack size greater than 2, error occured.");
    }
    destroyStack(stack);
    return ret;
}

int priority (char token) {
    // Statements
    if (token == '*' || token == '/')
        return 2;
    if (token == '+' || token == '-')
        return 1;
    return 0;
} // priority
/* =================== isOperator ====================
 Determine if token is an operator.
 Pre  token is a valid operator
 Post return true if operator; false if not
 */
bool isOperator (char token) {
    // Statements
    if (token == '*'
        || token == '/'
        || token == '+'
        || token == '-')
        return true; return false;
} // isOperator


int operate(int op1, int op2, char operator) {
    switch (operator) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        default:
            return 0;
    }
}

int* seekGoal(int src, int tgt, Graph* g) {
    STACK* st;
    int numNodes = g -> numNodes;
    // trick here is if the nodeIdx >= numNodes then it's a backtrack point
    int* aNode;
    
    st = createStack();
    aNode = (int *)malloc(sizeof(int));
    *aNode = src;
    pushStack(st, aNode);
    
    while (!emptyStack(st)) {
        aNode = (int *)peek(st);
        int idx = *aNode % numNodes;
        *aNode = idx;
        
        if (idx == tgt) {
            break; // 找到了 结束了
        }
        if (getNeighboursByNode(idx, g)) {
            int * children = getNeighboursByNode(idx, g);
            int len = getNeighbourSizeByNode(idx, g);
            
            for (int i = len - 1; i > 0; i --) {
                int * backTrackNode = (int *)malloc(sizeof(int));
                *backTrackNode = *(children + i) + numNodes; // make it a backtrak node
                pushStack(st, backTrackNode);
            }
            int * nextVisitChild = (int *)malloc(sizeof(int));
            *nextVisitChild = *children;
            pushStack(st, nextVisitChild);
        } else {
            // 如果即不是 目标 有没有孩子的话 那么backtrack 到上一个 backtrack node 为止
            aNode = (int *)popStack(st); // 首先把之前看的那个节点 pop掉 以免后面的该节点是 bt 节点而无限循环
            free(aNode);
            while (*((int *)peek(st)) < numNodes && !emptyStack(st)) {
                aNode = popStack(st);
                free(aNode);
            }
        }
    }
    if (emptyStack(st))
        return NULL;
    int * restrict ret = (int *)malloc(sizeof(int) * (stackCount(st) + 1));
    int cur = 0;
    while (!emptyStack(st)) {
        aNode = (int *)popStack(st);
        if (*aNode < numNodes) {
            *(ret + cur) = *aNode;
            cur++;
        }
        free(aNode);
    }
    *(ret + cur) = -1;  // signal end of list
    destroyStack(st);
    return ret;
}

void eightQueens(STACK * stack, int boardSize) {
    int  row = 0, col = 0;
    int  board[9][9] = {0};  // 0 no queen: 1 queen
    // row 0 & col 0 !used
    POSITION* pPos;
    
    if (stackCount(stack) != 0 || boardSize > 8 || boardSize < 4) {
        printf("Invalid inputs. ");
        return;
    }
    
    while (row <= boardSize)
    {
        while (col <= boardSize && row <= boardSize)
        {
            col++;
            if (!guarded(board, row, col, boardSize))
            {
                board[row][col] = 1;
                pPos = (POSITION*)malloc(sizeof(POSITION));
                pPos->row = row;
                pPos->col = col;
                pushStack(stack, pPos);
                row++;
                col = 0;
            } // if
            while (col >= boardSize)
            {
                pPos = popStack(stack);
                row  = pPos->row;
                col  = pPos->col;
                board[row][col] = 0;
                free (pPos);
            } // while col
        } // while col
    } // while row
    return;
} // fillBoard

bool guarded (int board[][9], int chkRow, int chkCol, int boardSzie) {
    for (int i = 0; i < NUM_DIRS; i++) {
        if (guardedOne(board, boardSzie, DIRS[i][0], DIRS[i][1], chkRow, chkCol))
            return true;
    }
    return false;
}

bool guardedOne (int board[][9], int boardSize,
                 int dirRow, int dirCol, int rowCk, int colCk) {
    while (rowCk < boardSize && rowCk >= 0 &&
           colCk >= 0 && colCk < boardSize) {
        if (board[rowCk][colCk] == 1)
            return true;
        rowCk += dirRow;
        colCk += dirCol;
    }
    return false;
}

// define white to be 1, dark to be 0
STACK * countWhiteByBlocks(int width, const int board[width][width]) {
    STACK * ret;
    int count, val;
    int boardBk[width][width];
    ConnComp * pData;
    
    // copy
    for (int i =0; i < width; i++)
        for (int j = 0; j< width; j++)
            boardBk[i][j] = board[i][j];

    ret = createStack();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            count = 0;
            if (boardBk[i][j] > 0) {
                val = boardBk[i][j];
                dfsCount(width, boardBk, i, j, &count);
                pData = (ConnComp *)malloc(sizeof(ConnComp));
                pData->count = count;
                pData->value = val;
                pushStack(ret, pData);
            }
        }
    }
    return ret;
}

void dfsCount(int width, int board[width][width], int rowI, int colI, int * count) {
    if (board[rowI][colI] == 0)
        return;
    (*count)++;
    board[rowI][colI] = 0;
    if (rowI+1 < width)
        dfsCount(width, board, rowI+1, colI, count);
    if (rowI-1 >= 0)
        dfsCount(width, board, rowI-1, colI, count);
    if (colI+1 < width)
        dfsCount(width, board, rowI, colI+1, count);
    if (colI-1 >= 0)
        dfsCount(width, board, rowI, colI-1, count);
}

void printBoard(int width, const int board[width][width]) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j ++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

char*** solveNQueens(int n, int* returnSize) {
    STACK* stack = createStack();
    char gameBoard[n][n];
    char*** ret;
    
    initBoard(n, gameBoard);
    dfsNQueens(0, n, gameBoard, stack);
    *returnSize = stack -> count;
    
    ret = (char ***) malloc((*returnSize) * sizeof(char **));
    for (int i =0; i<*returnSize; i++) {
        char *** tmp = (char ***)popStack(stack);  // tmp 的数据将会被拿去使用 因此不要free
        *(ret+i) = *tmp;
    }
    destroyStack(stack);
    return ret;
}

void dfsNQueens(int row, int width, char board[width][width], STACK* stack) {
    // termination condition
    if (row == width) {
        char ** solution;
        solution = (char **)malloc(width * sizeof(char *));
        for (int i = 0; i<width; i++) {
            *(solution+i) = (char *)malloc(width * sizeof(char));
            for (int j = 0; j<width; j++) {
                *(*(solution+i) + j) = board[i][j];
            }
        }
        pushStack(stack, &solution);
        return;   // 找到一个解以后把解放进去结束了
    }
    for (int col = 0; col < width; col ++) {
        if (!nGuarded(width, board, row + 1, col)) {
            board[row+1][col] = 'Q';
            dfsNQueens(row + 1, width, board, stack);
            board[row+1][col] = '.';
        }
    }
}

void initBoard(int n, char board[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j =0; j<n; j++) {
            board[i][j] = '.';
        }
    }
}

bool nGuarded(int n, char board[n][n], int chkRow, int chkCol) {
    for (int i = 0; i < NUM_DIRS; i++) {
        if (nGuardedOne(n, board, DIRS[i][0], DIRS[i][1], chkRow, chkCol))
            return true;
    }
    return false;
}

bool nGuardedOne (int n, char board[n][n], int dirRow,
                  int dirCol, int rowCk, int colCk) {
    while (rowCk < n && rowCk >= 0 && colCk >= 0 && colCk < n) {
        if (board[rowCk][colCk] == 'Q')
            return true;
        rowCk += dirRow;
        colCk += dirCol;
    }
    return false;
}
