///\file readMat.c
///\brief The function used to read the matrices
///Created by Preda Iulian
#include "functions.h"

///\fn readMatrix(int mat[1001000][3], int noRows, int noCols)
///\brief reads the matrix from the input and compreses it in 3 arrays
///\param len the lengths of the matrix after compression
///\param mat represents the matrix
///\param resLen represents the length of the resulting matrix
///\param resMat represents the resulting matrix
///\param noRows represents the number of rows in the matrix
///\param noCols represents the number of columns in the matrix


int readMatrix(int mat[1001000][3], int noRows, int noCols){
    ///first, we read the number of rows and columns of the current matrix
    ///now we go through the matrix
    printf("Insert the elements of the matrix:\n");
    int row,col,len=0;
    for( row = 1; row <= noRows; row ++){
        for( col = 1; col<= noCols; col ++){
            ///we read the current element \var e and if it is not 0, we store it
            int e;
            scanf("%d",&e);
            if( e != 0){
                len ++;
                mat[len][0] = row;
                mat[len][1] = col;
                mat[len][2] = e;
            }
        }
    }
    mat[len+1][0] = noRows + 1;
    mat[len+1][1] = noRows + 1;
    return len;
}

