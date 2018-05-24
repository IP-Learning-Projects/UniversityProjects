///\file printMat.c
///\brief Function printMat is used to print to the screen the matrix
///Created by Preda Iulian
#include "functions.h"

///\fn void printMat(int mat[1001000][3])
///\brief print to the screen the matrix
///\param len the lengths of the matrix after compression
///\param mat represents the matrix
///\param resLen represents the length of the resulting matrix
///\param resMat represents the resulting matrix
///\param noRows represents the number of rows in the matrix
///\param noCols represents the number of columns in the matrix

void printMat(int mat[1001000][3]){
    int row,col;
        int resIt = 1;
        for( row = 1; row <= noRows1; row ++){
            for( col = 1; col <= noCols1; col ++){
                if( mat[resIt][0] == row && mat[resIt][1] == col ){
                    printf("%d ", mat[resIt][2]);
                    resIt ++;
                }
                else
                    printf("0 ");
            }
            printf("\n");
        }
    }
