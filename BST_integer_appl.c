#include <stdio.h>
#include "BST.h"

int  compareInt (void* num1, void* num2);
void printBST   (void* num1);

int main(void) {
    // Local Definitions
    BST_TREE* BSTRoot;
    int*      dataPtr;
    int       dataIn = +1;
    
    // Statements
    printf("Begin BST Demonstation\n");
    BSTRoot    = BST_Create(compareInt);
    
    // Build Tree
    printf("Enter a list of positive integers;\n");
    printf("Enter a negative number to stop.\n");
    
    do
    {
        printf("Enter a number: ");
        scanf ("%d", &dataIn);
        if (dataIn > -1)
        {
            dataPtr = (int*) malloc (sizeof (int));
            if (!dataPtr)
            {
                printf("Memory Overflow in add\n");
                exit(100);
            } // if overflow
            *dataPtr = dataIn;
            BST_Insert (BSTRoot, dataPtr);
        } // valid data
    } while (dataIn > -1);
    
    printf("\nBST contains:\n");
    BST_Traverse (BSTRoot, printBST);
    printf("\nEnd BST Demonstration\n");
    return 0;
}

int  compareInt (void* num1, void* num2) {
    int* pNum1   = (int*) num1;
    int* pNum2   = (int*) num2;
    return *pNum1 - *pNum2;
}

void printBST (void* num1) {
    // Statements
    printf("%4d\n", *(int*)num1);
    return;
} // printBST
